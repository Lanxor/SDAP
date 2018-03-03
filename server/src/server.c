/*******************************************************************************
 * Autheurs : OLIVIER Thomas - RDSV Guillaume - STRMSEK Nicolas
 * Projet Annuaire Partagée - STRI
 * Fichier : SOURCE SERVER
 * Date : Janvier 2018
 * Etat : Terminé
 ******************************************************************************/

#include "../header/server.h"

/**************************************
 *
 * Partie serveur (connexion client)
 *
 *************************************/

/*
 * Initialisation.
 * Creation du serveur.
 */
int Initialisation()
{
  return InitialisationAvecService("6666");
}

/*
 * Initialisation.
 * Creation du serveur en précisant le service ou numéro de port.
 * renvoie 1 si ça c'est bien passé 0 sinon
 */
int InitialisationAvecService(char *service)
{
  int n;
  const int on = 1;
  struct addrinfo	hints, *res, *ressave;

  #ifdef WIN32
    WSADATA	wsaData;
    if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR)
    {
      printf("WSAStartup() n'a pas fonctionne, erreur : %d\n", WSAGetLastError()) ;
      WSACleanup();
      exit(1);
    }
    memset(&hints, 0, sizeof(struct addrinfo));
  #else
    bzero(&hints, sizeof(struct addrinfo));
  #endif

  hints.ai_flags = AI_PASSIVE;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if ( (n = getaddrinfo(NULL, service, &hints, &res)) != 0 ) {
    printf("Initialisation, erreur de getaddrinfo : %s", gai_strerror(n));
    return 0;
  }
  ressave = res;

  do {
    socketEcoute = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if( socketEcoute < 0 )
      continue;		/* error, try next one */
    setsockopt(socketEcoute, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
    #ifdef BSD
        setsockopt(socketEcoute, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));
    #endif
    if (bind(socketEcoute, res->ai_addr, res->ai_addrlen) == 0)
      break;			/* success */
    close(socketEcoute);	/* bind error, close and try next one */
  } while( (res = res->ai_next) != NULL );

  if( res == NULL ) {
    perror("Initialisation, erreur de bind.");
    return 0;
  }

  /* conserve la longueur de l'addresse */
  longeurAdr = res->ai_addrlen;

  freeaddrinfo(ressave);
  /* attends au max 4 clients */
  listen(socketEcoute, 4);
  printf("Creation du serveur reussie sur %s.\n", service);
  return 1;
}

/*
 * Attends qu'un client se connecte.
 */
int AttenteClient()
{
  struct sockaddr *clientAddr;
  char machine[NI_MAXHOST];

  clientAddr = (struct sockaddr*) malloc(longeurAdr);
  socketService = accept(socketEcoute, clientAddr, &longeurAdr);
  if (socketService == -1) {
    perror("AttenteClient, erreur de accept.");
    return 0;
  }
  if( getnameinfo(clientAddr, longeurAdr, machine, NI_MAXHOST, NULL, 0, 0) == 0 ) {
    //printf("Client sur la machine d'adresse %s connecte.\n", machine);
  }
  else {
    printf("Client anonyme connecte.\n");
  }
  free(clientAddr);

  /*
   * Reinit buffer
   */
  debutTampon = 0;
  finTampon = 0;
  return 1;
}

/*
 * Recoit un message envoye par le serveur.
 */
char *Reception()
{
  char message[LONGUEUR_TAMPON];
  int index = 0;
  int fini = FALSE;
  int retour = 0;

  while( !fini ) {
    /* on cherche dans le tampon courant */
    while( (finTampon > debutTampon) &&
        (tamponClient[debutTampon]!='\n') ) {
      message[index++] = tamponClient[debutTampon++];
    }
    /* on a trouve ? */
    if( (index > 0) && (tamponClient[debutTampon]=='\n') ) {
      message[index++] = '\n';
      message[index] = '\0';
      debutTampon++;
      fini = TRUE;
      #ifdef WIN32
        return _strdup(message);
      #else
        return strdup(message);
      #endif
    }
    else {
      /* il faut en lire plus */
      debutTampon = 0;
      retour = recv(socketService, tamponClient, LONGUEUR_TAMPON, 0);
      if( retour < 0 ) {
        perror("Reception, erreur de recv.");
        return NULL;
      }
      else if( retour == 0 ) {
        //fprintf(stderr, "Reception, le client a ferme la connexion.\n");
        return NULL;
      }
      else {
        /*
         * on a recu "retour" octets
         */
        finTampon = retour;
      }
    }
  }
  return NULL;
}

/*
 * Envoie un message au client.
 * Attention, le message doit etre termine par \n
 */
int Emission(char *message)
{
  int taille;
  if( strstr(message, "\n") == NULL ) {
    fprintf(stderr, "Emission, Le message n'est pas termine par \\n.\n");
    return 0;
  }
  taille = strlen(message);
  if( send(socketService, message, taille,0) == -1 ) {
    perror("Emission, probleme lors du send.");
    return 0;
  }
  //printf("Emission de %d caracteres.\n", taille+1);
  return 1;
}


/*
 * Recoit des donnees envoyees par le client.
 */
int ReceptionBinaire(char *donnees, size_t tailleMax)
{
  size_t dejaRecu = 0;
  int retour = 0;

  /*
   * on commence par recopier tout ce qui reste dans le tampon
   */
  while( (finTampon > debutTampon) && (dejaRecu < tailleMax) ) {
    donnees[dejaRecu] = tamponClient[debutTampon];
    dejaRecu++;
    debutTampon++;
  }

  /*
   * si on n'est pas arrive au max
   * on essaie de recevoir plus de donnees
   */
  if( dejaRecu < tailleMax ) {
    retour = recv(socketService, donnees + dejaRecu, tailleMax - dejaRecu, 0);
    if( retour < 0 ) {
      perror("ReceptionBinaire, erreur de recv.");
      return -1;
    }
    else if( retour == 0 ) {
      fprintf(stderr, "ReceptionBinaire, le client a ferme la connexion.\n");
      return 0;
    }
    else {
      /*
       * on a recu "retour" octets en plus
       */
      return dejaRecu + retour;
    }
  }
  else {
    return dejaRecu;
  }
}

/*
 * Envoie des données au client en précisant leur taille.
 */
int EmissionBinaire(char *donnees, size_t taille)
{
  int retour = 0;
  retour = send(socketService, donnees, taille, 100);
  if( retour == -1 ) {
    perror("Emission, probleme lors du send.");
    return -1;
  }
  else {
    return retour;
  }
}

/*
 * Ferme la connexion avec le client.
 */
void TerminaisonClient()
{
  close(socketService);
}

/*
 * Arrete le serveur.
 */
void Terminaison()
{
  close(socketEcoute);
}

/**************************************
 *
 * Partie serveur (traitement requête)
 *
 *************************************/

 /*
  * Permet de traiter l'action d'une requête demander
  * Envoie au client les différents messages Error ou résultats
  */
void action_request_trait(Request request)
{
  int idSession;

  idSession = request_get_idsession(request);

  if ( request_is_connection(request) ) { /******************************** C */
    action_connection(request);
  }
/******** DOIT ETRE CONNECTER ********/
  else if ( session_is_open(idSession) ) {

    if ( request_is_deconnection(request) ) { /**************************** D */
      action_deconnection(request);
    }
    else if ( request_is_search_repertory(request) ) { /****************** SR */
      if ( request_get_number_data(request) == 1 ) {
        action_search_repertory(request);
      }
      else { response_send_code(400, ""); }
    }
    else if ( request_is_search_contact(request) ) { /******************** SC */
      if ( request_get_number_data(request) == 2 ) {
        action_search_contact(request);
      }
      else { response_send_code(400, ""); }
    }
    else if ( request_is_add_account(request) ) { /*********************** AA */
      if ( request_get_number_data(request) == 2 ) {
        action_add_account(request);
      }
      else { response_send_code(400, ""); }
    }

/***** DOIT ETRE NON ANNONYME *****/
    else if ( !session_is_annonyme(idSession) ) {

  /** ANNONYME ET UN PARAMETRE **/
      if ( request_get_number_data(request) == 1 ) {
        if ( request_is_delete_account(request) ) { /********************* DA */
          action_delete_account(request);
        }
        else if ( request_is_add_repertory(request) ) { /***************** AR */
          action_add_repertory(request);
        }
        else if ( request_is_delete_repertory(request) ) { /************** DR */
          action_delete_repertory(request);
        }
        else { response_send_code(400, ""); }
      }
  /** ANNONYME ET DEUX PARAMETRE **/
      else if ( request_get_number_data(request) == 2 ) {
        if ( request_is_modify_account(request) ) { /********************* MA */
          action_modify_account(request);
        }
        else if ( request_is_modify_repertory(request) ) { /************** MR */
          action_modify_repertory(request);
        }
        else if ( request_is_add_contact(request) ) { /******************* AC */
          action_add_contact(request);
        }
        else if ( request_is_delete_contact(request) ) { /**************** DC */
          action_delete_contact(request);
        }
        else { response_send_code(400, ""); }
      }
  /** ANNONYME ET TROIS PARAMETRE **/
      else if ( request_get_number_data(request) == 3 ) {
        if ( request_is_modify_contact(request) ) { /********************* MC */
          action_modify_contact(request);
        }
        else { response_send_code(400, ""); }
      }
  /** ANNONYME ET PLUS DE TROIS PARAMETRE **/
      else { response_send_code(400, ""); }
    }
/***** N'EST PAS IDENTIFIER *****/
    else { response_send_code(401, ""); }
  }
/***** N'EST PAS CONNECTER *****/
  else { response_send_code(401, ""); }
}

/*
 * Effectue l'action de se connecter
 * Renvoie 1 si l'action c'est correctement déroulé, 0 sinon
 */
void action_connection(Request request)
{
  Account account;
  int idSession;

  idSession = 0;
/**** Connexion annonyme ****/
  if ( strcmp(request_get_data(request,1), "") == 0 ) {
    idSession = session_open(0);
    response_send_identifiant(idSession);
  }
/**** Connection avec identifiant ****/
  else {
    account = account_create();
    account_set_name(account, request_get_data(request, 1));
    account_set_password(account, request_get_data(request, 2));
    if ( account_file_exist(account) ) {
      idSession = session_open(account_get_identifier(account));
      /* Envoie d'identifiant */
      response_send_identifiant(idSession);
    }
    else {
      response_send_code(401, "Mauvais mot de passe ou compte inexistant");
    }
  }
}

/*
 * Effectue l'action de déconnection
 * Renvoie 1 si l'action c'est correctement déroulé, 0 sinon
 */
void action_deconnection(Request request)
{
  session_close(request_get_idsession(request));
  response_send_code(200, "");
}

/*
 * Effectue l'action de crée un nouveau compte utilisateur
 */
void action_add_account(Request request)
{
  Account account;

  account = account_create();
  account_set_name(account, request_get_data(request, 1));
  account_set_password(account, request_get_data(request, 2));
  if ( !account_file_exist(account) ) {
    account_set_identifier(account, account_get_next_identifier());
    if ( account_file_create(account) ) {
      response_send_code(200, "");
    }
    else { response_send_code(500, ""); }
  }
  else {
    response_send_code(401, "Un compte utilisateur du même nom est déjà enregistré");
  }
}

/*
 * Effectue l'action de modifier le mot de passe utilisateur
 * On vérifie que le mot de passe entrer soit le bon et on le modifie.
 * Format des données de la requête : <CurrentPassword><TAB><NewPassword>
 */
void action_modify_account(Request request)
{
  Account account;

  account = account_file_load(
                   session_get_identifier(request_get_idsession(request)));

  if ( account_is_same_password(account, request_get_data(request, 1)) ) {
    account_set_password(account, request_get_data(request, 2));
    if ( account_file_modify(account) ) {
      response_send_code(200, "");
    }
    else { response_send_code(500, ""); }
  }
  else {
    response_send_code(401, "Mot de passe incorrect.");
  }
  account_delete(account);
}

/*
 * Effectue l'action de supprimer le compte utilisateur.
 * Déconnecte aussi la session en cours.
 * Format des données de la requête : <CurrentPassword>
 */
void action_delete_account(Request request)
{
  Account account;

  account = account_file_load(
                   session_get_identifier(request_get_idsession(request)));

  if ( account_is_same_password(account, request_get_data(request, 1)) ) {
    if ( account_file_delete(account) ) {
      action_deconnection(request);
      response_send_code(200, "");
    }
    else { response_send_code(500, ""); }
  }
  else {
    response_send_code(401, "Mot de passe incorrect.");
  }
  account_delete(account);
}

/*
 * Effectue l'action de crée un nouveau annuaire pour l'utilisateur
 */
void action_add_repertory(Request request)
{
  Repertory repertory;

  repertory = repertory_create();
  repertory_set_owneridentifier(repertory,
    session_get_identifier(request_get_idsession(request)
  ));
  repertory_set_name(repertory, request_get_data(request,1));

  if ( repertory_file_create(repertory) ) {
    response_send_code(200, "");
  }
  else { response_send_code(500, ""); }

  repertory_delete(repertory);
}

/*
 * Effectue l'action de modifier le nom de l'annuaire d'un utilisateur
 * seul le propriétaire peut effectuer ce changement.
 */
void action_modify_repertory(Request request)
{
  Repertory oldRepertory;
  Repertory newRepertory;

  oldRepertory = repertory_create();
  newRepertory = repertory_create();

  repertory_set_owneridentifier(oldRepertory,
    session_get_identifier(request_get_idsession(request)
  ));
  repertory_set_name(oldRepertory, request_get_data(request,1));
  repertory_set_name(newRepertory, request_get_data(request,2));

  repertory_print(oldRepertory);
  repertory_print(newRepertory);


  if ( repertory_file_exist(oldRepertory) ) {
    if ( !repertory_file_exist(newRepertory) ) {
      if ( repertory_is_owner(oldRepertory) ) {
        if ( repertory_file_modify(oldRepertory, newRepertory) ) {
          response_send_code(200, "");
        }
        else { response_send_code(500, ""); }
      }
      else { response_send_code(401, "Vous n'êtes pas le propriétaire de l'annuaire."); }
    }
    else { response_send_code(404, "L'annuaire existe déjà."); }
  }
  else { response_send_code(404, "L'annuaire demandé n'existe pas."); }

  repertory_delete(oldRepertory);
  repertory_delete(newRepertory);
}

/*
 * Effectue l'action de supprimer un annuaire de l'utilisateur
 */
void action_delete_repertory(Request request)
{
  Repertory repertory;

  repertory = repertory_create();
  repertory_set_owneridentifier(repertory, session_get_identifier(request_get_idsession(request) ));
  repertory_set_name(repertory, request_get_data(request,1));

  if ( repertory_file_exist(repertory) ) {
    if ( repertory_is_owner(repertory) ) {
      if ( repertory_file_delete(repertory) ) {
        response_send_code(200, "");
      }
      else { response_send_code(500, ""); }
    }
    else { response_send_code(401, "Vous n'êtes pas le propriétaire de l'annuaire."); }
  }
  else { response_send_code(404, "L'annuaire demandé n'existe pas."); }

  repertory_delete(repertory);
}

/*
 * Effectue l'action d'ajouter un nouveau contact dans un annuaire.
 */
void action_add_contact(Request request)
{
  Repertory repertory;
  Contact contact;

  repertory = repertory_create();
  repertory_set_owneridentifier(repertory,
    session_get_identifier(request_get_idsession(request)
  ));
  repertory_set_name(repertory, request_get_data(request,1));

  if ( repertory_file_exist(repertory) ) {
    if ( repertory_is_owner(repertory) ) {

      contact = contact_transform(request_get_data(request, 2));

      if ( contact_is_valid(contact) ) {
        if ( !contact_file_exist(repertory, contact) ) {
          if ( contact_file_create(repertory, contact) ) {
            response_send_code(200, "");
          }
          else { response_send_code(500, ""); }
        }
        else {
          response_send_code(401, "Le contact existe déjà dans l'annuaire.");
        }
      }
      else {
        response_send_code(400, "Contact non valide, il manque des élèments.");
      }

      contact_delete(contact);
    }
    else { response_send_code(401, "Vous n'êtes pas le propriétaire de l'annuaire."); }
  }
  else { response_send_code(404, "L'annuaire demander n'existe pas."); }

  repertory_delete(repertory);
}

/*
 * Effectue l'action de modifier un contact par un autre dans un annuaire.
 */
void action_modify_contact(Request request)
{
  Repertory repertory;
  Contact oldContact;
  Contact newContact;

  repertory = repertory_create();
  repertory_set_owneridentifier(repertory,
    session_get_identifier(request_get_idsession(request)
  ));
  repertory_set_name(repertory, request_get_data(request,1));

  if ( repertory_file_exist(repertory) ) {
    if ( repertory_is_owner(repertory) ) {

      oldContact = contact_transform(request_get_data(request, 2));
      newContact = contact_transform(request_get_data(request, 3));

      if ( contact_is_valid(oldContact) && contact_is_valid(newContact) ) {
        if ( contact_file_exist(repertory, oldContact) ) {
          if ( !contact_file_exist(repertory, newContact) ) {
            if ( contact_file_modify(repertory, oldContact, newContact) ) {
              response_send_code(200, "");
            }
            else {
              response_send_code(500, "");
            }
          }
          else {
            response_send_code(401, "Le contact existe déjà dans l'annuaire.");
          }
        }
        else {
          response_send_code(401, "Le contact n'existe pas dans l'annuaire.");
        }
      }
      else {
        response_send_code(400, "Contact non valide, il manque des élèments.");
      }

      contact_delete(oldContact);
      contact_delete(newContact);

    }
    else { response_send_code(401, "Vous n'êtes pas le propriétaire de l'annuaire."); }
  }
  else { response_send_code(404, "L'annuaire demander n'existe pas."); }

  repertory_delete(repertory);
}

/*
 * Effectue l'action de suppression d'un contact dans un annuaire.
 */
void action_delete_contact(Request request)
{
  Repertory repertory;
  Contact contact;

  repertory = repertory_create();
  repertory_set_owneridentifier(repertory,
    session_get_identifier(request_get_idsession(request)
  ));
  repertory_set_name(repertory, request_get_data(request,1));

  if ( repertory_file_exist(repertory) ) {
    if ( repertory_is_owner(repertory) ) {

      contact = contact_transform(request_get_data(request, 2));

      if ( contact_is_valid(contact) ) {
        if ( contact_file_exist(repertory, contact) ) {
          if ( contact_file_delete(repertory, contact) ) {
            response_send_code(200, "");
          }
          else { response_send_code(500, ""); }
        }
        else { response_send_code(400, "Le contact n'existe pas."); }
      }
      else {
        response_send_code(400, "Contact non valide, il manque des élèments.");
      }

      contact_delete(contact);
    }
    else { response_send_code(401, "Vous n'êtes pas le propriétaire de l'annuaire."); }
  }
  else { response_send_code(404, "L'annuaire demander n'existe pas."); }

  repertory_delete(repertory);
}

/*
 * Effectue l'action de recherche d'annuaire.
 */
void action_search_repertory(Request request)
{
  char* search;
  char* data;

  data = request_get_data(request, 1);
  search = repertory_file_search(data);
  response_send_code(200, search);
  free(search);

}

/*
 * Effectue l'action de recherche de contacts dans un annuaire.
 */
void action_search_contact(Request request)
{
  Repertory repertory;
  char* search;
  char* data;


  repertory = repertory_create();
  repertory_set_name(repertory, request_get_data(request, 1));

  if ( repertory_file_exist(repertory) ) {
    data = request_get_data(request, 2);
    search = contact_file_search(repertory, data);
    response_send_code(200, search);
    free(search);
  }
  else { response_send_code(404, "L'annuaire demander n'existe pas."); }

  repertory_delete(repertory);
}
