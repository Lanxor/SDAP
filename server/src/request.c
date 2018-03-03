/*******************************************************************************
 * Autheurs : OLIVIER Thomas - RDSV Guillaume - STRMSEK Nicolas
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
void request_set_data(Request request, char* message)
{
  int counter;

  if ( request->data != NULL )
    free(request->data);

  request->data = malloc((strlen(message)+2)*sizeof(char) );
  assert( request->data != NULL );
  strcpy(request->data, message);
  request->data[strlen(request->data)-1] = '\0';
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
  if ( request->data != NULL )
    free(request->data);
  if ( request != NULL )
    free(request);
}

/*
 * Transforme un message en une requête.
 * le message doit être formaté de la manière suivante :
 * {numero} {caractères}[caractères]<TAB>{donnée1}<TAB>{donnée2}<CR>
 * le premier caractère doit être obligatoire, le second est optionnel,
 * mais les caractère doivent être précédé d'un espace, et suivit d'une
 * tabulation si il y a des données.
 * Chaque donnée doit être séparé par une tabulation '\t'.
 * Renvoie une requête structurée.
 */
Request request_transform(char* message)
{
  Request request;
  int idSession;
  int counterMessage;

  request = request_create();
  idSession = 0;
  counterMessage = 0;
  while ( message[counterMessage] != ' ' && message[counterMessage] != '\n'
          && counterMessage < strlen(message) ) {
    idSession *= 10;
    idSession += (message[counterMessage] - 48);
    ++counterMessage;
  }
  request->idSession = idSession;

  ++counterMessage;
  request_set_command(request, message+counterMessage);
  while ( message[counterMessage] != '\t' && counterMessage < strlen(message) ) {
    ++counterMessage;
  }
  request_set_data(request, message+counterMessage+1);

  return request;
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
 * Vérifie si la requête est de type C (connexion).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_connection(Request request)
{
  return strcmp(request->command, "C") == 0;
}

/*
 * Vérifie si la requête est de type D (déconnexion).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_deconnection(Request request)
{
  return strcmp(request->command, "D") == 0;
}

/*
 * Vérifie si la requête est de type AA (ajout d'un compte).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_add_account(Request request)
{
  return strcmp(request->command, "AA") == 0;
}

/*
 * Vérifie si la requête est de type AR (ajout d'un annuaire).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_add_repertory(Request request)
{
  return strcmp(request->command, "AR") == 0;
}

/*
 * Vérifie si la requête est de type AC (ajout d'un contact).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_add_contact(Request request)
{
  return strcmp(request->command, "AC") == 0;
}

/*
 * Vérifie si la requête est de type MA (modification de compte).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_modify_account(Request request)
{
  return strcmp(request->command, "MA") == 0;
}

/*
 * Vérifie si la requête est de type MR (modification d'annuaire).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_modify_repertory(Request request)
{
  return strcmp(request->command, "MR") == 0;
}

/*
 * Vérifie si la requête est de type MC (modification de contact).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_modify_contact(Request request)
{
  return strcmp(request->command, "MC") == 0;
}

/*
 * Vérifie si la requête est de type DA (suppression de compte).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_delete_account(Request request)
{
  return strcmp(request->command, "DA") == 0;
}

/*
 * Vérifie si la requête est de type DR (suppression d'annuaire).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_delete_repertory(Request request)
{
  return strcmp(request->command, "DR") == 0;
}

/*
 * Vérifie si la requête est de type DC (suppression de contact).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_delete_contact(Request request)
{
  return strcmp(request->command, "DC") == 0;
}

/*
 * Vérifie si la requête est de type SR (recherche d'annuaire).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_search_repertory(Request request)
{
  return strcmp(request->command, "SR") == 0;
}

/*
 * Vérifie si la requête est de type SC (recherche de contact).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_search_contact(Request request)
{
  return strcmp(request->command, "SC") == 0;
}
