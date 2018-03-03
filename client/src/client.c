/*******************************************************************************
 * Autheurs : RDSV Guillaume - STRMSEK Nicolas
 * Projet Annuaire Partagée - STRI
 * Fichier : SOURCE CLIENT
 * Date : Janvier 2018
 * Etat : Terminé
 ******************************************************************************/
#include "../header/client.h"

/*
 * Initialisation.
 * Connexion au serveur sur la machine donnee.
 * Utilisez localhost pour un fonctionnement local.
 */
int Initialisation(char *machine) {
  return InitialisationAvecService(machine, "6666");
}

/*
 * Initialisation.
 * Connexion au serveur sur la machine donnee et au service donne.
 * Utilisez localhost pour un fonctionnement local.
 */
int InitialisationAvecService(char *machine, char *service) {
  int n;
  struct addrinfo	hints, *res, *ressave;

  bzero(&hints, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if( (n = getaddrinfo(machine, service, &hints, &res)) != 0 )  {
    fprintf(stderr, "Initialisation, erreur de getaddrinfo : %s", gai_strerror(n));
    return 0;
  }
  ressave = res;

  do{
	  socketClient = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (socketClient < 0)
      continue;	/* ignore this one */
    if (connect(socketClient, res->ai_addr, res->ai_addrlen) == 0)
      break;		/* success */
    close(socketClient);	/* ignore this one */
  } while( (res = res->ai_next) != NULL );

  if (res == NULL) {
    perror("Initialisation, erreur de connect.");
    return 0;
  }

  freeaddrinfo(ressave);
  printf("Connexion avec le serveur reussie.\n");

  return 1;
}

/*
 * Recoit un message envoye par le serveur.
 */
char *Reception() {
  char message[LONGUEUR_TAMPON];
  int index = 0;
  int fini = FALSE;
  int retour = 0;
  while(!fini) {
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
      return strdup(message);
    }
    else {
      /* il faut en lire plus */
      debutTampon = 0;
      retour = recv(socketClient, tamponClient, LONGUEUR_TAMPON, 0);
      if( retour < 0 ) {
        perror("Reception, erreur de recv.");
        return NULL;
      }
      else if( retour == 0 ) {
        fprintf(stderr, "Reception, le serveur a ferme la connexion.\n");
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
 * Envoie un message au serveur.
 * Attention, le message doit etre termine par \n
 */
int Emission(char *message) {
	if( strstr(message, "\n") == NULL ) {
		fprintf(stderr, "Emission, Le message n'est pas termine par \\n.\n");
	}
	int taille = strlen(message);
	if( send(socketClient, message, taille,0) == -1 ) {
    perror("Emission, probleme lors du send.");
    return 0;
	}
	return 1;
}

/*
 * Recoit des donnees envoyees par le serveur.
 */
int ReceptionBinaire(char *donnees, size_t tailleMax) {
  int dejaRecu = 0;
  int retour = 0;
  /* on commence par recopier tout ce qui reste dans le tampon
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
    retour = recv(socketClient, donnees + dejaRecu, tailleMax - dejaRecu, 0);
    if( retour < 0 ) {
      perror("ReceptionBinaire, erreur de recv.");
      return -1;
    }
    else if( retour == 0 ) {
      fprintf(stderr, "ReceptionBinaire, le serveur a ferme la connexion.\n");
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
 * Envoie des données au serveur en précisant leur taille.
 */
int EmissionBinaire(char *donnees, size_t taille) {
  int retour = 0;
  retour = send(socketClient, donnees, taille, 0);
if( retour == -1 ) {
    perror("Emission, probleme lors du send.");
    return -1;
	}
	else {
    return retour;
	}
}

/*
 * Ferme la connexion.
 */
void Terminaison() {
	close(socketClient);
}

/******************************************************************************/

/*
 * Affiche le logo du protocole
 */
void logo()
{
  printf("  _______  ______   _______  _______\n");
  printf(" (  ____ \\(  __  \\ (  ___  )(  ____ )\n");
  printf(" | (    \\/| (  \\  )| (   ) || (    )|\n");
  printf(" | (_____ | |   ) || (___) || (____)|\n");
  printf(" (_____  )| |   | ||  ___  ||  _____)\n");
  printf("       ) || |   ) || (   ) || (\n");
  printf(" /\\____) || (__/  )| )   ( || )\n");
  printf(" \\_______)(______/ |/     \\||/  \n\n");
  printf(" Simply Directory Access Protocol Client\n\n");
}

/*
 * Affiche le menu courant à l'utilisateur
 */
void menu_print(int idSession)
{
  printf("##### MENU #######################\n");
  printf("#                                #\n");
  if ( idSession == 0 ) {
    printf("# 1 . S'identifier/Se connecter  #\n");
    printf("# 2 . Quitter                    #\n");
  }
  else {
    printf("# 1  . Créer un compte           #\n");
    printf("# 2  . Supprimer compte          #\n");
    printf("# 3  . Modifier mot de passe     #\n");
    printf("# 4  . Supprimer annuaire        #\n");
    printf("# 5  . Modifier annuaire         #\n");
    printf("# 6  . Créer annuaire            #\n");
    printf("# 7  . Ajouter contact           #\n");
    printf("# 8  . Modifier contact          #\n");
    printf("# 9  . Supprimer contact         #\n");
    printf("# 10 . Chercher un annuaire      #\n");
    printf("# 11 . Chercher un contact       #\n");
    printf("# 12 . Se déconnecter            #\n");
    printf("# 13 . Quitter                   #\n");
  }
  printf("#                                #\n");
  printf("##################################\n\n");
}

/*
 * Affiche le menu à l'utilisateur, lui demande un choix
 * et effectue l'action associé
 */
void action_menu()
{
  Request request;
  int choix;

  request = request_create();

  system("clear");
  logo();
  do {
    menu_print(request_get_idsession(request));
    printf("Saisir votre choix : ");
    scanf("%d", &choix);
    clear_cache_stdin();

    system("clear");
    logo();
    action_choix(request, choix);
    printf("\n");
  } while( (request_get_idsession(request) == 0 && choix != 2)
           || (request_get_idsession(request) != 0 && choix != 13) );

  printf("Good bye !\n");

  request_delete(request);
}
