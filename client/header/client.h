/*******************************************************************************
 * Autheurs : RDSV Guillaume - STRMSEK Nicolas
 * Projet Annuaire Partagée - STRI
 * Fichier : HEADER CLIENT
 * Date : Janvier 2018
 * Etat : Terminé
 ******************************************************************************/
#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include "request.h"

#define TRUE 1
#define FALSE 0

/* Last value 4096 */
#define LONGUEUR_TAMPON 32768

/* Variables cachees */

/* le socket client */
int socketClient;
/* le tampon de reception */
char tamponClient[LONGUEUR_TAMPON];
int debutTampon;
int finTampon;

/*
 * Initialisation.
 * Connexion au serveur sur la machine donnee.
 * Utilisez localhost pour un fonctionnement local.
 * renvoie 1 si ça c'est bien passé 0 sinon
 */
int Initialisation(char *machine);

/*
 * Initialisation.
 * Connexion au serveur sur la machine donnee et au service donne.
 * Utilisez localhost pour un fonctionnement local.
 * renvoie 1 si ça c'est bien passé 0 sinon
 */
int InitialisationAvecService(char *machine, char *service);

/*
 * Recoit un message envoye par le serveur.
 * retourne le message ou NULL en cas d'erreur.
 * Note : il faut liberer la memoire apres traitement.
 */
char *Reception();

/*
 * Envoie un message au serveur.
 * Attention, le message doit etre termine par \n
 * renvoie 1 si ça c'est bien passé 0 sinon
 */
int Emission(char *message);

/*
 * Recoit des donnees envoyees par le serveur.
 * renvoie le nombre d'octets reçus, 0 si la connexion est fermée,
 * un nombre négatif en cas d'erreur
 */
int ReceptionBinaire(char *donnees, size_t tailleMax);

/*
 * Envoie des données au serveur en précisant leur taille.
 * renvoie le nombre d'octets envoyés, 0 si la connexion est fermée,
 * un nombre négatif en cas d'erreur
 */
int EmissionBinaire(char *donnees, size_t taille);

/*
 * Ferme la connexion.
 */
void Terminaison();

/******************************************************************************/

/*
 * Affiche le logo du protocole
 */
void logo();

/*
 * Affiche le menu courant à l'utilisateur
 */
void menu_print(int idSession);

/*
 * Affiche le menu à l'utilisateur, lui demande un choix
 * et effectue l'action associé
 */
void action_menu();

#endif
