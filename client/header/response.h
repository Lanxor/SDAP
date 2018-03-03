/*******************************************************************************
 * Autheurs : RDSV Guillaume - STRMSEK Nicolas
 * Projet Annuaire Partagée - STRI
 * Fichier : HEADER RESPONSE
 * Date : Janvier 2018
 * Etat : Terminé
 ******************************************************************************/
#ifndef __RESPONSE_H__
#define __RESPONSE_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "client.h"

/*
 * Définition de la structure logique d'une réponse.
 */
typedef struct s_response
{
  int     code;
  char*   data;
} t_response;

/*
 * Définition du pointeur vers la structure.
 */
typedef struct s_response *Response;

/*
 * Crée et initialise une nouvelle structure réponse.
 * Renvoie le pointeur vers la structure.
 */
Response response_create();

/*
 * Debug : Affiche les données de la structure réponse.
 */
void response_print(Response response);

/*
 * Définit le code de la réponse.
 */
void response_set_code(Response response, int code);

/*
 * Définit la donnée de la réponse.
 * La donnée peut donnée une indication sur l'erreur rencontré.
 * Mais aussi les informations demander (un contact)
 */
void response_set_data(Response response, char* data);

/*
 * Rajoute aux données de la réponse les données passé en paramètre.
 * Permet ainsi de crée une liste d'argument.
 * Chaque argument est séparé par une tabulation, <TAB>, '\t'.
 */
void response_add_data(Response response, char* data);

int response_get_code(Response response);

char* response_get_data(Response response, int number);

Response response_transform(char* message);

/*
 * Libére la mémoire de la structure d'une réponse.
 */
void response_delete(Response response);


#endif
