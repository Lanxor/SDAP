/*******************************************************************************
 * Autheurs : RDSV Guillaume - STRMSEK Nicolas
 * Projet Annuaire Partagée - STRI
 * Fichier : HEADER REQUEST
 * Date : Janvier 2018
 * Etat : Terminé
 ******************************************************************************/
#ifndef __REQUEST_H__
#define __REQUEST_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "client.h"
#include "response.h"
#include "contact.h"
/*
 * Définition de la structure logique d'une requête.
 */
typedef struct s_request
{
  int     idSession;
  char    command[3];
  char*   data;
} t_request;

/*
 * Définition du pointeur vers la structure.
 */
typedef struct s_request *Request;

/*
 * Crée et initialise une nouvelle structure requête.
 * Renvoie le pointeur vers la structure.
 */
Request request_create();

/*
 * Debug : Affiche les données de la structure requête.
 */
void request_print(Request request);

/*
 * Assigne l'identifiant de session à une requête.
 */
void request_set_idsession(Request request, int idSession);

/*
 * Assigne les deux premier caractères au maximum pour la commande
 */
void request_set_command(Request request, char* message);

/*
 * Assigne le message en paramètre au données d'une requête
 */
void request_set_data(Request request, char* message);

/*
 * Ajoute des données en plus dans une requête
 * Séparé par des tabulation <TAB>
 */
void request_add_data(Request request, char* message);

/*
 * Renvoie l'identifiant de session utilisé par la requête.
 */
int request_get_idsession(Request request);

/*
 * Renvoie le pointeur sur la comande de la requête
 */
char* request_get_command(Request request);

/*
 * Renvoie le nombre de paramètre d'une requête.
 */
int request_get_number_data(Request request);

/*
 * Renvoie le pointeur des données de la requête en fonction du numéro de
 * paramètre demandé.
 */
char* request_get_data(Request request, int number);

/*
 * Libére la mémoire de la structure requête.
 */
void request_delete(Request request);

/*
 * Vérifie si la requête n'a pas de donnée.
 * Renvoie 1 si les données sont vide, 0 sinon.
 */
int request_is_data_empty(Request request);

/*
 * Envoie au serveur une requête passé en paramètre.
 */
int request_send(Request request);

/*
 * Effectue l'action dont l'utilisateur à choisi via le menu.
 */
void action_choix(Request request, int choix);

/*
 * Met a jour la requête avec les bons paramètres
 * demande à l'utilisateur de saisir ces identifiants
 * (vide si annonyme)
 * et envoie la requêtes
 * et récupère l'identifiant de la réponse du serveur
 */
void action_connection(Request request);

/*
 * Crée un nouveau compte utilisateur
 * on demande à l'utilisateur un nom et un mot de passe
 * on envoie la requête
 * on affiche la réponse
 */
void action_add_account(Request request);

/*
 * Envoie une requête au serveur pour se déconnecter de la session
 */
void action_deconnection(Request request);

/*
 * Envoie une requête pour supprimer le compte courant (connecté)
 * demande à l'utilisateur son mot de passe
 * envoie la requête et affiche la réponse
 */
void action_delete_account(Request request);

/*
 * Envoie une requête au serveur pour modifier le mot de passe du compte
 * utilisateur courant
 * demande le mot de passe actuelle
 * demande le nouveau mot de passe
 * envoie la requête et affiche la réponse
 */
void action_modify_account(Request request);

/*
 * Envoie une requête pour supprimer un annuaire
 * demande le nom de l'annuaire a supprimer
 * envoie la requête et affiche la réponse du serveur
 */
void action_delete_repertory(Request request);

/*
 * Envoie une requête pour modifier le nom d'un répertoire
 * demande le nom du répertoire à modifier et le nouveau nom
 * envoie la requête et affiche la réponse
 */
void action_modify_repertory(Request request);

/*
 * Envoie une requête pour ajouter un nouveau annuaire
 * demande le nom de l'annuaire
 * envoie la requête et affiche la réponse
 */
void action_add_repertory(Request request);

/*
 * Demande à l'utilisateur de saisir différents champs d'un contact
 * et retourne une structure Contact
 */
Contact contact_saisi();

/*
 * Envoie une requête pour ajouter un nouveau contact
 * demande à l'utilisateur de saisir un nouveau contact
 * envoie la requête et affiche la réponse
 */
void action_add_contact(Request request);

/*
 * Envoie une requête pour modifier un contact
 * demande à l'utilisateur de saisir les nom, prénom et email d'un contact
 * (obligatoirement)
 * et demande de saisir les nouveau champs de l'utilisateur
 * envoie la requête et affiche la réponse
 */
void action_modify_contact(Request request);

/*
 * Envoie une requête pour supprimer un contact
 * demande à l'utilisateur de saisir les champs nom, prénom, email d'un contact
 * pour l'identifier
 * envoie la requête et affiche la réponse
 */
void action_delete_contact(Request request);

/*
 * Envoie une requête au serveur pour récupéré le nom de tout les annuaire
 * dont une occurance de la chaine de caractères saisie par l'utilisateur
 * correspond.
 * envoie la requête et affiche la réponse et le nom des annuaires trouvé.
 */
void action_search_repertory(Request request);

/*
 * Envoie une requête pour récupéré la liste des contacts d'un annuaire
 * spécifié par l'utilisateur et dont la chaine de caractère saisie trouve une
 * occurence dans un des champs, au minimum, nom, prénom, mail d'un contact
 * envoie la requête et affiche le résultats
 */
void action_search_contact(Request request);

#endif
