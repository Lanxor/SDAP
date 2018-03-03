/*******************************************************************************
 * Autheurs : OLIVIER Thomas - RDSV Guillaume - STRMSEK Nicolas
 * Projet Annuaire Partagée - STRI
 * Fichier : HEADER ACCOUNT
 * Date : Janvier 2018
 * Etat : Terminé
 ******************************************************************************/

#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*
 * Constante qui définie la taille maximum d'un nom de compte.
 */
#define ACCOUNT_CHAR_MAX_NAME 25
/*
 * Constante qui définie la taille maximum d'un mot de passe d'un compte.
 */
#define ACCOUNT_CHAR_MAX_PASSWORD 25

/*
 * Définition de la structure logique d'un compte utilisateur.
 */
typedef struct s_account
{
  int     identifier;
  char    name[ACCOUNT_CHAR_MAX_NAME+1];
  char    password[ACCOUNT_CHAR_MAX_PASSWORD+1];
} t_account;

/*
 * Définition du pointeur vers la structure.
 */
typedef struct s_account *Account;

/*
 * Crée et initialise une nouvelle structure compte utilisateur.
 * Renvoie le pointeur vers la structure.
 */
Account account_create(void);

/*
 * Debug : Affiche les données de la structure annuaire.
 */
void account_print(Account account);

/*
 * Définit l'identifiant d'un compte utilisateur
 */
void account_set_identifier(Account account, int identifier);

/*
 * Définit le nom d'utilisateur du compte utilisateur passé en paramètre.
 * On récupère le nom à partir des données passé en paramètre,
 * le message doit avoir la structure suivante : {nom}<TAB> ou {nom}<CR>
 */
void account_set_name(Account account, char* data);

/*
 * Définit le mot de passe du compte utilisateur passé en paramètre.
 * On récupère le mot de passe à partir des données passé en paramètre,
 * le message doit avoir la structure suivante : {mdp}<TAB> ou {mdp}<CR>
 */
void account_set_password(Account account, char* data);

/*
 * Récupère et renvoie la valeur "identifiant" de la structure logique d'un
 * compte utilisateur passé en paramètre.
 */
int account_get_identifier(Account account);

/*
 * Récupère le mot de passe d'une structure logique d'un compte utilisateur
 * passé en paramètre.
 * Renvoie le pointeur vers cette chaine de caractères.
 */
char* account_get_password(Account account);

/*
 * Libére la mémoire de la structure compte utilisateur.
 */
void account_delete(Account account);

/*
 * Vérifie caractére par caractére si le mot de passe du compte et celui de
 * la donnée passé en paramètre sont identique.
 * Compare la donnée jusqu'à arriver à la fin de la chaine ou s'il rencontre
 * tabulation "<TAB>".
 * Renvoie 1 si les deux mot de passe sont identique, 0 sinon.
 */
int account_is_same_password(Account account, char* data);

/*
 * Récupère le prochain identifier utilisateur
 * Renvoie l'identifiant.
 * Si aucun compte utilisateur n'est enregistré renvoie la valeur 1
 * pour le premier compte utilisateur.
 */
int account_get_next_identifier();

/*
 * Vérifie si le compte utilisateur est inscrit dans le fichier utilisateur.
 * Renvoie 1 si le compte utilisateur est inscrit, 0 sinon.
 */
int account_exist(Account account);

/*
 * Vérifie si le compte utilisateur est enregistré dans la base de donnée
 * Vérifie le nom et le mot de passe si ils sont identique aux nom et mot de
 * passe du compte passé en paramètre.
 * Renvoie 1 si le compte correspond, 0 sinon.
 */
int account_file_exist(Account account);

/*
 * Enregistre dans un fichier la structure du compte utilisateur.
 * Si le fichier n'existe pas, il est crée.
 * Renvoie 1 si l'enregistrement du compte à été effectué, 0 sinon.
 */
int account_file_create(Account account);

/*
 * Récupère les informations d'un compte utilisateur dans une structure
 * logique d'un compte utilisateur en fonction de l'identifiant de compte
 * utilisateur.
 * On admet que le compte est déjà enregistré.
 * Renvoie une structure de compte utilisateur.
 */
Account account_file_load(int identifier);

/*
 * Fonction qui modifie seulement le mot de passe d'un compte utilisateur.
 * L'identifiant de compte utilisateur ne doit pas changer.
 * Renvoie 1 si la modification à été éffectuer, 0 sinon.
 */
int account_file_modify(Account account);

/*
 * Supprime un compte utilisateur enregistré.
 * Parcours le fichier "registre.account" en lecture et écrit dans un nouveau
 * fichier "registre.account.tmp" tous les comptes utilisateur sauf celui
 * passé en paramètre.
 * renomme ensuite le fichier temporaire en "registre.account" (écrasement)
 * Renvoie 1 si la suppression est effectuer, 0 sinon.
 */
int account_file_delete(Account account);

#endif
