/*******************************************************************************
 * Autheurs : OLIVIER Thomas - RDSV Guillaume - STRMSEK Nicolas
 * Projet Annuaire Partagée - STRI
 * Fichier : HEADER SERVER
 * Date : Janvier 2018
 * Etat : Terminé
 ******************************************************************************/

#ifndef __SERVER_H__
#define __SERVER_H__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>

#include "session.h"
#include "account.h"
#include "request.h"
#include "repertory.h"
#include "contact.h"
#include "response.h"

/**************************************
 *
 * Partie serveur (connexion client)
 *
 *************************************/

#ifdef WIN32
  #include <winsock2.h>
  #include <ws2tcpip.h>
#else
  #include <unistd.h>
  #include <netdb.h>
  #include <sys/socket.h>
  #include <sys/select.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
#endif

#include <errno.h>

#define TRUE 1
#define FALSE 0
#define LONGUEUR_TAMPON 4096

#ifdef WIN32
  #define perror(x) printf("%s : code d'erreur : %d\n", (x), WSAGetLastError())
  #define close closesocket
  #define socklen_t int
#endif

/* Variables cachees */

/* le socket d'ecoute */
int socketEcoute;
/* longueur de l'adresse */
socklen_t longeurAdr;
/* le socket de service */
int socketService;
/* le tampon de reception */
char tamponClient[LONGUEUR_TAMPON];
int debutTampon;
int finTampon;


/*
 * Initialisation.
 * Creation du serveur.
 * renvoie 1 si ça c'est bien passé 0 sinon
 */
int Initialisation();

/*
 * Initialisation.
 * Creation du serveur en précisant le service ou numéro de port.
 * renvoie 1 si ça c'est bien passé 0 sinon
 */
int InitialisationAvecService(char *service);


/*
 * Attends qu'un client se connecte.
 * renvoie 1 si éa c'est bien passé 0 sinon
 */
int AttenteClient();

/*
 * Recoit un message envoye par le client.
 * retourne le message ou NULL en cas d'erreur.
 * Note : il faut liberer la memoire apres traitement.
 */
char *Reception();

/*
 * Envoie un message au client.
 * Attention, le message doit etre termine par \n
 * renvoie 1 si ça c'est bien passé 0 sinon
 */
int Emission(char *message);

/*
 * Recoit des donnees envoyees par le client.
 * renvoie le nombre d'octets reçus, 0 si la connexion est fermée,
 * un nombre négatif en cas d'erreur
 */
int ReceptionBinaire(char *donnees, size_t tailleMax);

/*
 * Envoie des données au client en précisant leur taille.
 * renvoie le nombre d'octets envoyés, 0 si la connexion est fermée,
 * un nombre négatif en cas d'erreur
 */
int EmissionBinaire(char *donnees, size_t taille);


/*
 * Ferme la connexion avec le client.
 */
void TerminaisonClient();

/*
 * Arrete le serveur.
 */
void Terminaison();

/**************************************
 *
 * Partie serveur (traitement requête)
 *
 *************************************/

/*
 * Permet de traiter l'action d'une requête demander
 * Envoie au client les différents messages Error ou résultats
 */
void action_request_trait(Request request);

/*
 * Effectue l'action de se connecter
 * Renvoie 1 si l'action c'est correctement déroulé, 0 sinon
 */
void action_connection(Request request);

/*
 * Effectue l'action de déconnection
 * Renvoie 1 si l'action c'est correctement déroulé, 0 sinon
 */
void action_deconnection(Request request);

/*
 * Effectue l'action de crée un nouveau compte utilisateur
 */
void action_add_account(Request request);

/*
 * Effectue l'action de modifier le mot de passe utilisateur
 * On vérifie que le mot de passe entrer soit le bon et on le modifie.
 * Format des données de la requête : <CurrentPassword><TAB><NewPassword>
 */
void action_modify_account(Request request);

/*
 * Effectue l'action de supprimer le compte utilisateur.
 * Déconnecte aussi la session en cours.
 * Format des données de la requête : <CurrentPassword>
 */
void action_delete_account(Request request);

/*
 * Effectue l'action de crée un nouveau annuaire pour l'utilisateur
 */
void action_add_repertory(Request request);

/*
 * Effectue l'action de modifier le nom de l'annuaire d'un utilisateur
 * seul le propriétaire peut effectuer ce changement.
 */
void action_modify_repertory(Request request);

/*
 * Effectue l'action de supprimer un annuaire de l'utilisateur
 */
void action_delete_repertory(Request request);

/*
 * Effectue l'action d'ajouter un nouveau contact dans un annuaire.
 */
void action_add_contact(Request request);

/*
 * Effectue l'action de modifier un contact par un autre dans un annuaire.
 */
void action_modify_contact(Request request);

/*
 * Effectue l'action de suppression d'un contact dans un annuaire.
 */
void action_delete_contact(Request request);

/*
 * Effectue l'action de recherche d'annuaire.
 */
void action_search_repertory(Request request);

/*
 * Effectue l'action de recherche de contacts dans un annuaire.
 */
void action_search_contact(Request request);

#endif
