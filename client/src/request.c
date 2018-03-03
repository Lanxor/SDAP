/*******************************************************************************
 * Autheurs : RDSV Guillaume - STRMSEK Nicolas
 * Projet Annuaire Partagée - STRI
 * Fichier : SOURCE REQUEST
 * Date : Janvier 2018
 * Etat : Terminé
 ******************************************************************************/
#include "../header/request.h"

/*
 * Crée et initialise une nouvelle structure requête.
 * Renvoie le pointeur vers la structure.
 */
Request request_create()
{
  Request request;

  request = malloc(sizeof(t_request));
  assert( request != NULL );
  request->idSession = 0;
  request->command[0] = '\0';
  request->data = NULL;

  return request;
}

/*
 * Debug : Affiche les données de la structure requête.
 */
void request_print(Request request)
{
  int counter;

  printf("Requête : %d %s %s\n", request->idSession, request->command,
         request->data);
}

/*
 * Assigne l'identifiant de session à une requête.
 */
void request_set_idsession(Request request, int idSession)
{
  request->idSession = idSession;
}

/*
 * Assigne les deux premier caractères au maximum pour la commande
 */
void request_set_command(Request request, char* message)
{
  int counter;

  counter = 0;
  while ( message[counter] != '\t' && message[counter] != '\n'
          && counter < strlen(message) && counter < 2 ) {
    request->command[counter] = message[counter];
    ++counter;
  }
  request->command[counter] = '\0';
}

/*
 * Assigne le message en paramètre au données d'une requête
 */
void request_set_data(Request request, char* data)
{
  if ( request->data != NULL ) {
    free(request->data);
    request->data = NULL;
  }
  if ( data != NULL && strcmp(data, "") != 0 ) {
    request->data = malloc(strlen(data)*sizeof(char));
    assert( request->data != NULL );
    strcpy(request->data, data);
  }
}

/*
 * Ajoute des données en plus dans une requête
 * Séparé par des tabulation <TAB>
 */
void request_add_data(Request request, char* data)
{
  request->data = realloc(request->data,
                    (strlen(request->data) + 2 + strlen(data))*sizeof(char) );
  assert( request->data != NULL );
  strcat(request->data, "\t");
  strcat(request->data, data);
}

/*
 * Renvoie l'identifiant de session utilisé par la requête.
 */
int request_get_idsession(Request request)
{
  return request->idSession;
}

/*
 * Renvoie le pointeur sur la comande de la requête
 */
char* request_get_command(Request request)
{
  return request->command;
}

/*
 * Renvoie le nombre de paramètre d'une requête.
 */
int request_get_number_data(Request request)
{
  int number;
  int counter;

  if ( request->data == NULL )
    return 0;

  number = 1;
  counter = 0;
  while ( counter < strlen(request->data) && request->data[counter] != '\n'
          && request->data[counter] != '\0' ) {
    if ( request->data[counter] == '\t' ) {
      ++number;
    }
    ++counter;
  }

  return number;
}

/*
 * Renvoie le pointeur des données de la requête en fonction du numéro de
 * paramètre demandé.
 */
char* request_get_data(Request request, int number)
{
  int counter;
  int counterNumber;
  char* data;

  data = request->data;
  if ( !request_is_data_empty(request) ) {
    for ( counterNumber = 0; counterNumber < number-1; counterNumber++ ) {
      counter = 0;
      while ( data[counter] != '\t' && counter < strlen(data) ) {
        ++counter;
      }
      data = data+counter+1;
    }
  }

  return data;
}

/*
 * Libére la mémoire de la structure requête.
 */
void request_delete(Request request)
{
  if ( request->data != NULL ) {
    free(request->data);
    request->data = NULL;
  }
  if ( request != NULL ) {
    free(request);
    request = NULL;
  }
}

/*
 * Vérifie si la requête n'a pas de donnée.
 * Renvoie 1 si les données sont vide, 0 sinon.
 */
int request_is_data_empty(Request request)
{
  return request->data == NULL || strcmp(request->data, "") == 0;
}

/*
 * Efface le cache de l'utilisateur après une saisie
 */
void clear_cache_stdin()
{
  int c ;
  do {
    c = getchar();
  } while ((c != '\n') && (c != EOF)) ;
}

/*
 * Demande à l'utilisateur de saisir une chaine de caractères de taille
 * variable
 */
int saisir_text(char* chaine, int taille)
{
  char* position, resultat;
  if ( fgets(chaine, taille, stdin) == NULL ) {
    return -1;
  }
  position = strchr(chaine, '\n');
  if ( position != NULL )
    *position = '\0';
  else
    clear_cache_stdin();
  return 0;
}

/*
 * Envoie au serveur une requête passé en paramètre.
 */
int request_send(Request request)
{
  char* message;
  char nombre[11];

  sprintf(nombre, "%d", request->idSession);
  message = malloc((strlen(nombre)+1)*sizeof(char));
  strcpy(message, nombre);
  message[strlen(message)] = '\0';

  message = realloc(message, (strlen(message) + 2 + strlen(request->command))*sizeof(char));
  strcat(message, " ");
  strcat(message, request->command);

  if ( request->data != NULL ) {
    message = realloc(message, (strlen(message) + 2 + strlen(request->data))*sizeof(char));
    strcat(message, "\t");
    strcat(message, request->data);
  }

  if ( Emission(strcat(message,"\n")) == -1 ) {
    printf("Erreur d'émission\n");
    return 0;
  }

  return 1;
}

/*
 * Effectue l'action dont l'utilisateur à choisi via le menu.
 */
void action_choix(Request request, int choix)
{
  if ( request->idSession == 0 ) {
    switch ( choix ) {
      case 1:
        action_connection(request);
        break;
      case 2:
        break;
      default:
        printf("Mauvais option.\n");
    }
  }
  else {
    switch( choix ) {
      case 1:
        action_add_account(request);
        break;
      case 2:
        action_delete_account(request);
        break;
      case 3:
        action_modify_account(request);
        break;
      case 4:
        action_delete_repertory(request);
        break;
      case 5:
        action_modify_repertory(request);
        break;
      case 6:
        action_add_repertory(request);
        break;
      case 7:
        action_add_contact(request);
        break;
      case 8:
        action_modify_contact(request);
        break;
      case 9:
        action_delete_contact(request);
        break;
      case 10:
        action_search_repertory(request);
        break;
      case 11:
        action_search_contact(request);
        break;
      case 12:
        action_deconnection(request);
        break;
      case 13:
        action_deconnection(request);
        break;
      default:
        printf("Maivaise option\n");
    }
  }
}

/*
 * Met a jour la requête avec les bons paramètres
 * demande à l'utilisateur de saisir ces identifiants
 * (vide si annonyme)
 * et envoie la requêtes
 * et récupère l'identifiant de la réponse du serveur
 */
void action_connection(Request request)
{
  Response response;
  int idSession;
  int counterMessage;
  char idSessionChar[11];
  char nom[50+1];
  char password[50+1];
  char annonyme;
  char* message;

  request_set_command(request, "C");
  request_set_data(request, "");
  printf("Saisir un identifiant : ");
  saisir_text(nom, 50);
  if ( strcmp(nom, "") != 0 ) {
    request_set_data(request, nom);
    printf("Saisir un mot de passe : ");
    saisir_text(password, 50);
    request_add_data(request, password);
  }
  else {
    request_set_data(request, "");
  }
  request_send(request);

  message = Reception();
  response = response_transform(message);
  if ( response_get_code(response) == 200 ) {
    message = response_get_data(response, 2);
    idSession = 0;
    counterMessage = 0;
    while ( message[counterMessage] != ' ' && message[counterMessage] != '\t'
            && message[counterMessage] != '\n'
            && counterMessage < strlen(message) ) {
      idSession *= 10;
      idSession += (message[counterMessage] - 48);
      ++counterMessage;
    }
    request_set_idsession(request, idSession);
    printf("Session ouverte.\nVous avez l'identifiant n°%d\n", idSession);
  }
  else {
    response_print(response);
  }
  response_delete(response);
}

/*
 * Crée un nouveau compte utilisateur
 * on demande à l'utilisateur un nom et un mot de passe
 * on envoie la requête
 * on affiche la réponse
 */
void action_add_account(Request request)
{
  Response response;
  char* message;
  char nom[50+1];
  char password[50+1];

  request_set_command(request, "AA");
  request_set_data(request, "");
  printf("Saisir un identifiant : ");
  saisir_text(nom, 50);
  if ( strcmp(nom, "") != 0 ) {
    request_set_data(request, nom);
    printf("Saisir un mot de passe : ");
    saisir_text(password, 50);
    request_add_data(request, password);
  }
  else {
    request_set_data(request, "");
  }
  request_send(request);

  message = Reception();
  response = response_transform(message);
  if ( response_get_code(response) == 200 ) {
    printf("Compte crée.\n");
  }
  else { response_print(response); }
  response_delete(response);

}

/*
 * Envoie une requête au serveur pour se déconnecter de la session
 */
void action_deconnection(Request request)
{
  Response response;
  char* message;

  request_set_data(request, "");
  request_set_command(request, "D");
  request_send(request);

  message = Reception();
  response = response_transform(message);
  if ( response_get_code(response) == 200 ) {
    printf("Session déconnecté.\n");
    request_set_idsession(request, 0);
  }
  else { response_print(response); }
  response_delete(response);
}

/*
 * Envoie une requête pour supprimer le compte courant (connecté)
 * demande à l'utilisateur son mot de passe
 * envoie la requête et affiche la réponse
 */
void action_delete_account(Request request)
{
  Response response;
  char password[50+1];
  char* message;

  request_set_data(request, "");
  request_set_command(request, "DA");
  printf("Saisir votre mot de passe : ");
  saisir_text(password, 50);
  request_set_data(request, password);
  request_send(request);

  message = Reception();
  response = response_transform(message);
  if ( response_get_code(response) == 200 ) {
    printf("Déconnecté et compte supprimé.\n");
    request_set_idsession(request, 0);
  }
  else { response_print(response); }
  response_delete(response);
}

/*
 * Envoie une requête au serveur pour modifier le mot de passe du compte
 * utilisateur courant
 * demande le mot de passe actuelle
 * demande le nouveau mot de passe
 * envoie la requête et affiche la réponse
 */
void action_modify_account(Request request)
{
  Response response;
  char password[50+1];
  char newPassword[50+1];
  char* message;

  request_set_data(request, "");
  request_set_command(request, "MA");
  printf("Saisir votre mot de passe actuelle : ");
  saisir_text(password, 50);
  request_set_data(request, password);
  if ( strcmp(password, "") != 0 ) {
    printf("Saisir votre nouveau mot de passe : ");
    saisir_text(newPassword, 50);
    request_add_data(request, newPassword);
    request_send(request);

    message = Reception();
    response = response_transform(message);
    if ( response_get_code(response) == 200 ) {
      printf("Mot de passe changé.\n");
    }
    else { response_print(response); }
    response_delete(response);
  }
  else {
    printf("Saisie vide.\n");
  }
}

/*
 * Envoie une requête pour supprimer un annuaire
 * demande le nom de l'annuaire a supprimer
 * envoie la requête et affiche la réponse du serveur
 */
void action_delete_repertory(Request request)
{
  Response response;
  char name[50+1];
  char* message;

  request_set_data(request, "");
  request_set_command(request, "DR");
  printf("Saisir le nom de l'annuaire : ");
  saisir_text(name, 50);
  request_set_data(request, name);
  if ( strcmp(name, "") != 0 ) {
    request_send(request);

    message = Reception();
    response = response_transform(message);
    if ( response_get_code(response) == 200 ) {
      printf("Annuaire supprimer.\n");
    }
    else { response_print(response); }
    response_delete(response);
  }
  else {
    printf("Saisie vide.\n");
  }
}

/*
 * Envoie une requête pour modifier le nom d'un répertoire
 * demande le nom du répertoire à modifier et le nouveau nom
 * envoie la requête et affiche la réponse
 */
void action_modify_repertory(Request request)
{
  Response response;
  char nom[50+1];
  char newNom[50+1];
  char* message;

  request_set_data(request, "");
  request_set_command(request, "MR");
  printf("Saisir le nom du répertoire à changer : ");
  saisir_text(nom, 50);
  request_set_data(request, nom);
  if ( strcmp(nom, "") != 0 ) {
    printf("Saisir un nouveau nom : ");
    saisir_text(newNom, 50);
    request_add_data(request, newNom);
    request_send(request);

    message = Reception();
    response = response_transform(message);
    if ( response_get_code(response) == 200 ) {
      printf("Nom de l'annuaire changé.\n");
    }
    else { response_print(response); }
    response_delete(response);
  }
  else {
    printf("Saisie vide.\n");
  }
}

/*
 * Envoie une requête pour ajouter un nouveau annuaire
 * demande le nom de l'annuaire
 * envoie la requête et affiche la réponse
 */
void action_add_repertory(Request request)
{
  Response response;
  char name[50+1];
  char* message;

  request_set_data(request, "");
  request_set_command(request, "AR");
  printf("Saisir le nom de l'annuaire : ");
  saisir_text(name, 50);
  request_set_data(request, name);
  if ( strcmp(name, "") != 0 ) {
    request_send(request);

    message = Reception();
    response = response_transform(message);
    if ( response_get_code(response) == 200 ) {
      printf("Annuaire crée.\n");
    }
    else { response_print(response); }
    response_delete(response);
  }
  else {
    printf("Saisie vide.\n");
  }
}

/*
 * Demande à l'utilisateur de saisir différents champs d'un contact
 * et retourne une structure Contact
 */
Contact contact_saisi()
{
  Contact contact;
  char text[200+1];

  contact = contact_create();

  printf("Saisir un nom : ");
  saisir_text(text, 50);
  contact_set_name(contact, text);

  printf("Saisir un prénom : ");
  saisir_text(text, 50);
  contact_set_surname(contact, text);

  printf("Saisir une adresse mail : ");
  saisir_text(text, 50);
  contact_set_mail(contact, text);

  printf("Saisir un numéro de téléphone : ");
  saisir_text(text, 10);
  contact_set_phone(contact, text);

  printf("Saisir un numéro de téléphone : ");
  saisir_text(text, 10);
  contact_set_prophone(contact, text);

  printf("Saisir une adresse postale : ");
  saisir_text(text, 150);
  contact_set_address(contact, text);

  printf("Saisir une date de naissance (XX/XX/XXXX) : ");
  saisir_text(text, 10);
  contact_set_birthday(contact, text);

  printf("Saisir des notes : ");
  saisir_text(text, 200);
  contact_set_notes(contact, text);

  return contact;
}

/*
 * Envoie une requête pour ajouter un nouveau contact
 * demande à l'utilisateur de saisir un nouveau contact
 * envoie la requête et affiche la réponse
 */
void action_add_contact(Request request)
{
  Response response;
  Contact contact;
  char text[150];
  char* message;
  char* messageContact;

  request_set_data(request, "");
  request_set_command(request, "AC");
  printf("Saisir l'annuaire : ");
  saisir_text(text, 50);
  if ( strcmp(text, "") != 0 ) {
    printf("Saisir le contact à modifier (nom, prénom, mail suffisent) :\n");
    request_set_data(request, text);
    contact = contact_saisi();

    if ( contact_is_valid(contact) ) {
      messageContact = contact_transform(contact);
      request_add_data(request, messageContact);
      free(messageContact);
      request_send(request);

      message = Reception();
      response = response_transform(message);
      if ( response_get_code(response) == 200 ) {
        printf("Contact ajouté.\n");
      }
      else { response_print(response); }
      response_delete(response);
    }
    else {
      printf("Contact saisi non valide.\n");
    }
  }
  else {
    printf("Erreur saisie vide.\n");
  }
}

/*
 * Envoie une requête pour modifier un contact
 * demande à l'utilisateur de saisir les nom, prénom et email d'un contact
 * (obligatoirement)
 * et demande de saisir les nouveau champs de l'utilisateur
 * envoie la requête et affiche la réponse
 */
void action_modify_contact(Request request)
{
  Response response;
  Contact contact;
  Contact newContact;
  char text[150];
  char* message;
  char* messageContact;

  request_set_data(request, "");
  request_set_command(request, "MC");
  printf("Saisir l'annuaire : ");
  saisir_text(text, 50);
  if ( strcmp(text, "") != 0 ) {
    request_set_data(request, text);
    printf("Saisir le contact à modifier (nom, prénom, mail suffisent) :\n");
    contact = contact_saisi();
    printf("Saisir le contact à modifier :\n");
    newContact = contact_saisi();

    if ( contact_is_valid(contact) && contact_is_valid(newContact) ) {
      messageContact = contact_transform(contact);
      request_add_data(request, messageContact);
      free(messageContact);

      messageContact = contact_transform(newContact);
      request_add_data(request, messageContact);
      free(messageContact);

      request_send(request);

      message = Reception();
      response = response_transform(message);
      if ( response_get_code(response) == 200 ) {
        printf("Contact modifié.\n");
      }
      else { response_print(response); }
      response_delete(response);
    }
    else {
      printf("Contact saisi non valide.\n");
    }
  }
  else {
    printf("Erreur saisie vide.\n");
  }
}

/*
 * Envoie une requête pour supprimer un contact
 * demande à l'utilisateur de saisir les champs nom, prénom, email d'un contact
 * pour l'identifier
 * envoie la requête et affiche la réponse
 */
void action_delete_contact(Request request)
{
  Response response;
  Contact contact;
  char text[150];
  char* message;
  char* messageContact;

  request_set_data(request, "");
  request_set_command(request, "DC");
  printf("Saisir l'annuaire : ");
  saisir_text(text, 50);
  if ( strcmp(text, "") != 0 ) {
    request_set_data(request, text);
    contact = contact_saisi();

    if ( contact_is_valid(contact) ) {
      messageContact = contact_transform(contact);
      request_add_data(request, messageContact);
      free(messageContact);
      request_send(request);

      message = Reception();
      response = response_transform(message);
      if ( response_get_code(response) == 200 ) {
        printf("Contact supprimé.\n");
      }
      else { response_print(response); }
      response_delete(response);
    }
    else {
      printf("Contact saisi non valide.\n");
    }
  }
  else {
    printf("Erreur saisie vide.\n");
  }
}

/*
 * Envoie une requête au serveur pour récupéré le nom de tout les annuaire
 * dont une occurance de la chaine de caractères saisie par l'utilisateur
 * correspond.
 * envoie la requête et affiche la réponse et le nom des annuaires trouvé.
 */
void action_search_repertory(Request request)
{
  Response response;
  char text[50];
  char* message;

  request_set_data(request, "");
  request_set_command(request, "SR");
  printf("Recherche : ");
  saisir_text(text, 50);
  request_set_data(request, text);
  request_send(request);

  message = Reception();
  response = response_transform(message);
  if ( response_get_code(response) == 200 ) {
    printf("Liste :\n%s", response_get_data(response, 2));
  }
  else { response_print(response); }
  response_delete(response);
}

/*
 * Envoie une requête pour récupéré la liste des contacts d'un annuaire
 * spécifié par l'utilisateur et dont la chaine de caractère saisie trouve une
 * occurence dans un des champs, au minimum, nom, prénom, mail d'un contact
 * envoie la requête et affiche le résultats
 */
void action_search_contact(Request request)
{
  Response response;
  char text[50];
  char* message;

  request_set_data(request, "");
  request_set_command(request, "SC");
  printf("Saisir l'annuaire : ");
  saisir_text(text, 50);
  if ( strcmp(text, "") != 0 ) {
    request_set_data(request, text);
    printf("Recherche : ");
    saisir_text(text, 50);
    request_add_data(request, text);
    request_send(request);

    message = Reception();
    response = response_transform(message);
    if ( response_get_code(response) == 200 ) {
      printf("Liste :\n%s", response_get_data(response, 2));
    }
    else { response_print(response); }
    response_delete(response);
  }
  else {
    printf("Erreur saisie vide.\n");
  }
}
