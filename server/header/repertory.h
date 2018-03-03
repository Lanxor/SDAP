/*******************************************************************************
 * Autheurs : OLIVIER Thomas - RDSV Guillaume - STRMSEK Nicolas
 * Projet Annuaire Partagée - STRI
 * Fichier : HEADER REPERTORY
 * Date : Janvier 2018
 * Etat : Terminé
 ******************************************************************************/

#ifndef __REPERTORY_H__
#define __REPERTORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

/*
 * Définition de la structure logique d'un annuaire
 */
typedef struct s_repertory
{
  int     ownerIdentifier;
  char*   pathName;
} t_repertory;

/*
 * Définition du pointeur vers la structure
 */
typedef struct s_repertory *Repertory;

/*
 * Crée et initialise une nouvelle structure annuaire
 * Renvoie le pointeur vers la structure.
 */
Repertory repertory_create();

/*
 * Debug : Affiche les données de la structure annuaire.
 */
void repertory_print(Repertory repertory);

/*
 * Définit l'identifiant d'un compte utilisateur pour un annuaire.
 */
void repertory_set_owneridentifier(Repertory repertory, int ownerIdentifier);

/*
 * Définit le chemin d'accés à l'annuaire.
 * on lui passe le nom de l'annuaire "{nom}" et il crée le chemin de
 * l'annuaire "./repertory/{nom}"
 * Le nom est récupéré par une structure {nom}<TAB> ou {nom}<CR> ou jusqu'à
 * la fin de la chaine de caractère passé en argument.
 */
void repertory_set_name(Repertory repertory, char* name);

/*
 * Renvoie le chemin du répertoire passé en paramètre.
 */
char* repertory_get_path(Repertory repertory);

/*
 * Libére la mémoire de la structure annuaire
 */
void repertory_delete(Repertory repertory);

/*
 * Vérifie si le fichier annuaire existe ou pas.
 * Renvoie 1 s'il existe, 0 sinon.
 */
int repertory_file_exist(Repertory repertory);

/*
 * Vérifie si l'identifiant définit dans l'annuaire passé en paramètre
 * correspond à celui inscrit dans le fichier annuaire.
 * Renvoie 1 si il est le propriétaire, 0 sinon.
 */
int repertory_is_owner(Repertory repertory);

/*
 * Crée le fichier annuaire, ne le crée pas s'il existe déjà
 * inscrit en plus l'identifiant utilisateur dans le fichier
 * Renvoie 1 si le fichier est crée, 0 sinon.
 */
int repertory_file_create(Repertory repertory);

/*
 * Change le nom de l'annuaire. On admet que l'utilisateur est le propriétaire
 * Vérifie si l'ancien répertoire existe et si le nouveau n'existe pas.
 * Renvoie 1 si le nom est modifié, 0 sinon.
 */
int repertory_file_modify(Repertory oldRepertory, Repertory newRepertory);

/*
 * Supprime l'annuaire en entier. On admet que l'utilisateur est le propriétaire
 * Vérifie si le l'annuaire existe.
 * Renvoie 1 si il est supprimer, 0 sinon.
 */
int repertory_file_delete(Repertory repertory);

/*
 * Alloue en mémoire une chaine de caractère.
 * On concatène ensuite dans cette chaine de caractère les noms des annuaires
 * dont une occurence de la donnée en paramètre ce trouve dans le nom de
 * l'annuaire.
 * La chaine est structuré de la manière suivante :
 * <TAB>{nom}<TAB>{nom} etc...
 * Renvoie un pointeur vers cette chaine de caractère.
 */
char* repertory_file_search(char* data);

#endif
