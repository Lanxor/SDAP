/*******************************************************************************
 * Autheurs : OLIVIER Thomas - RDSV Guillaume - STRMSEK Nicolas
 * Projet Annuaire Partagée - STRI
 * Fichier : HEADER SESSION
 * Date : Janvier 2018
 * Etat : Terminé
 ******************************************************************************/

#ifndef __SESSION_H__
#define __SESSION_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define SESSION_MAX 50

int sessionTab[SESSION_MAX];

/*
 * Initialise le tableau de session
 */
void session_init(void);

/*
 * Affiche toutes les sessions ouvertes
 */
void session_print(void);

/*
 * Récupère l'identifiant du compte utilisateur associé à l'identifiant de
 * la session passé en paramètre.
 * Un identifiant 0 sinifie qu'il est annonyme, ou que la session n'est pas
 * ouverte, ou que l'identifiant dépasse la limite SESSION_MAX.
 * Un nombre positif est l'identifiant du compte utilisateur.
 * Renvoie l'identifiant associé à l'identifiant de session.
 */
int session_get_identifier(int idSession);

/*
 * Ouvre une session pour un identifiant utilisateur
 * Un identifiant : 0 indique une connection annonyme
 * Renvoie l'identifiant de session : 0 < id < SESSION_MAX
 */
int session_open(int identifier);

/*
 * Ferme une session pour un identifiant session
 */
void session_close(int idSession);

/*
 * Vérifie si pour un identifiant session si une session est ouverte
 * Renvoie 1 si la session est ouverte, 0 sinon.
 */
int session_is_open(int idSession);

/*
 * Vérifie si la session passé en paramètre est une session annonyme
 * ou si c'est un compte utilisateur.
 * Renvoie 1 si l'identifiant session est annonyme, 0 sinon.
 */
int session_is_annonyme(int idSession);

#endif
