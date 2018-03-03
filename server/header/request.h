/******************************************************************************
 * Autheurs : OLIVIER Thomas - RDSV Guillaume - STRMSEK Nicolas
 * Projet Annuaire Partagée - STRI
 * Fichier : HEADER REQUEST
 * Date : Janvier 2018
 * Etat : Terminé
 *****************************************************************************/

#ifndef __REQUEST_H__
#define __REQUEST_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

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
 * Transforme un message en une requête.
 * le message doit être formaté de la manière suivante :
 * {numero} {caractères}[caractères]<TAB>{donnée1}<TAB>{donnée2}<CR>
 * le premier caractère doit être obligatoire, le second est optionnel,
 * mais les caractère doivent être précédé d'un espace, et suivit d'une
 * tabulation si il y a des données.
 * Chaque donnée doit être séparé par une tabulation '\t'.
 * Renvoie une requête structurée.
 */
Request request_transform(char* message);

/*
 * Vérifie si la requête n'a pas de donnée.
 * Renvoie 1 si les données sont vide, 0 sinon.
 */
int request_is_data_empty(Request request);

/*
 * Vérifie si la requête est de type C (connexion).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_connection(Request request);

/*
 * Vérifie si la requête est de type D (déconnexion).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_deconnection(Request request);

/*
 * Vérifie si la requête est de type AA (ajout d'un compte).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_add_account(Request request);

/*
 * Vérifie si la requête est de type AR (ajout d'un annuaire).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_add_repertory(Request request);

/*
 * Vérifie si la requête est de type AC (ajout d'un contact).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_add_contact(Request request);

/*
 * Vérifie si la requête est de type MA (modification de compte).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_modify_account(Request request);

/*
 * Vérifie si la requête est de type MR (modification d'annuaire).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_modify_repertory(Request request);

/*
 * Vérifie si la requête est de type MC (modification de contact).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_modify_contact(Request request);

/*
 * Vérifie si la requête est de type DA (suppression de compte).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_delete_account(Request request);

/*
 * Vérifie si la requête est de type DR (suppression d'annuaire).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_delete_repertory(Request request);

/*
 * Vérifie si la requête est de type DC (suppression de contact).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_delete_contact(Request request);

/*
 * Vérifie si la requête est de type SR (recherche d'annuaire).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_search_repertory(Request request);

/*
 * Vérifie si la requête est de type SC (recherche de contact).
 * Renvoie 1 si c'est le cas, 0 sinon.
 */
int request_is_search_contact(Request request);

#endif
