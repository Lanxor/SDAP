/*******************************************************************************
 * Autheurs : OLIVIER Thomas - RDSV Guillaume - STRMSEK Nicolas
 * Projet Annuaire Partagée - STRI
 * Fichier : HEADER CONTACT
 * Date : Janvier 2018
 * Etat : Terminé
 ******************************************************************************/

#ifndef __CONTACT_H__
#define __CONTACT_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "repertory.h"

/*
 * Constante qui définie la taille maximum du nom du contact.
 */
#define CONTACT_CHAR_MAX_NAME 50

/*
 * Constante qui définie la taille maximum du prénom du contact.
 */
#define CONTACT_CHAR_MAX_SURNAME 50

/*
 * Constante qui définie la taille maximum l'adresse mail du contact.
 */
#define CONTACT_CHAR_MAX_MAIL 50

/*
 * Constante qui définie la taille maximum du numéro de téléphone du contact.
 */
#define CONTACT_CHAR_MAX_PHONE 10

/*
 * Constante qui définie la taille maximum de l'adresse postale du contact.
 */
#define CONTACT_CHAR_MAX_ADDRESS 100

/*
 * Constante qui définie la taille maximum de la date de naissance du contact.
 */
#define CONTACT_CHAR_MAX_BIRTHDAY 10

/*
 * Constante qui définie la taille maximum des remarques concernant le contact.
 */
#define CONTACT_CHAR_MAX_NOTES 200

/*
 * Définition de la structure logique d'un contact d'un annuaire.
 */
typedef struct s_contact
{
  char    name[CONTACT_CHAR_MAX_NAME+1];
  char    surname[CONTACT_CHAR_MAX_SURNAME+1];
  char    mail[CONTACT_CHAR_MAX_MAIL+1];
  char    phone[CONTACT_CHAR_MAX_PHONE+1];
  char    proPhone[CONTACT_CHAR_MAX_PHONE+1];
  char    address[CONTACT_CHAR_MAX_ADDRESS+1];
  char    birthday[CONTACT_CHAR_MAX_BIRTHDAY+1];
  char    notes[CONTACT_CHAR_MAX_NOTES+1];
} t_contact;

/*
 * Définition du pointeur vers la structure.
 */
typedef struct s_contact *Contact;

/*
 * Crée et initialise une nouvelle structre d'un contact.
 * Renvoie le pointeur vers cette structure.
 */
Contact contact_create();

/*
 * Debug : Affiche les données de la structure contact.
 */
void contact_print(Contact contact);

/*
 * Fonction pour les setters.
 * Permet à l'aide d'un pointeur vers un champ du contact, d'un pointeur sur
 * les données et la taille maximal du champ du contact, d'affecter la donnée
 * au champ voulu.
 * L'affectation s'arrête jusqu'à la fin de la donnée définit par un ":",
 * "<TAB>", "<CR>" ou "<NULL>".
 * Exemples : {text}:
 *            {text}\t
 *            {text}\n
 *            {text}\0
 */
void contact_setter(char* pointer, char* data, int sizeCharMax);

/*
 * Définit le nom d'un contact passé en paramètre à l'aide de la donnée passé
 * en paramètre et qui sera traiter par la fonction "contact_setter".
 */
void contact_set_name(Contact contact, char* data);

/*
 * Définit le prénom d'un contact passé en paramètre à l'aide de la donnée passé
 * en paramètre et qui sera traiter par la fonction "contact_setter".
 */
void contact_set_surname(Contact contact, char* data);

/*
 * Définit le mail d'un contact passé en paramètre à l'aide de la donnée passé
 * en paramètre et qui sera traiter par la fonction "contact_setter".
 */
void contact_set_mail(Contact contact, char* data);

/*
 * Définit le numéro de téléphone personnel d'un contact passé en paramètre à
 * l'aide de la donnée passé en paramètre et qui sera traiter par la fonction
 * "contact_setter".
 */
void contact_set_phone(Contact contact, char* data);

/*
 * Définit le numéro de téléphone professionnel d'un contact passé en paramètre
 * à l'aide de la donnée passé en paramètre et qui sera traiter par la fonction
 * "contact_setter".
 */
void contact_set_prophone(Contact contact, char* data);

/*
 * Définit l'addresse d'un contact passé en paramètre à l'aide de la donnée
 * passé en paramètre et qui sera traiter par la fonction "contact_setter".
 */
void contact_set_address(Contact contact, char* data);

/*
 * Définit la date d'anniversaire d'un contact passé en paramètre à l'aide de
 * la donnée passé en paramètre et qui sera traiter par la fonction
 * "contact_setter".
 */
void contact_set_birthday(Contact contact, char* data);

/*
 * Définit les remarques d'un contact passé en paramètre à l'aide de la donnée
 * passé en paramètre et qui sera traiter par la fonction "contact_setter".
 */
void contact_set_notes(Contact contact, char* data);

/*
 * Libére la mémoire de la structure contact d'un annuaire.
 */
void contact_delete(Contact contact);

/*
 * Vérifie le contact passé en paramètre est valide.
 * Pour qu'un contact soit valide, il faut que son nom, son prénom et son
 * mail ne soit pas vide.
 * Renvoie 1 si le contact est valide, 0 sinon.
 */
int contact_is_valid(Contact contact);

/*
 * Vérifie si les deux contact passé en paramètre sont identique.
 * Seul les champs nom, prénom et mail sont vérifié pour définir si un
 * contact ressemble à un autre.
 * Renvoie 1 si les deux contact sont identique, 0 sinon.
 */
int contact_is_same(Contact firstContact, Contact secondContact);

/*
 * Transforme une chaine de caractère passé en paramètre en un contact.
 * La chaine de caractère doit être du format suivant :
 * {nom}:{prenom}:{mail}:{téléphone}:{téléphonePro}:{addressePostale}
 * :{anniversaire}:{remarques}
 * On peut aussi ne pas rensaigner certains champs :
 * {name}:{prenom}:{mail}::{téléphonePro}::::
 * pour ne pas rensaigner les champs téléphone, addressePostale, anniversaire,
 * et remarques.
 * Renvoie le pointeur vers la structure logique d'un contact.
 */
Contact contact_transform(char* data);

/*
 * Vérifie si le contact passé en paramètre existe dans l'annuaire passé en
 * paramètre.
 * Vérifie le nom, le prénom et le mail.
 * Renvoie 1 si le contact existe dans l'annuaire, 0 sinon.
 */
int contact_file_exist(Repertory repertory, Contact contact);

/*
 * Enregistre dans un fichier répertoire le contact passé en paramètre.
 * Il faut que l'annuaire existe.
 * Ajoute à la fin du fichier annuaire.
 * Renvoie 1 si le contact à été enregistré, 0 sinon.
 */
int contact_file_create(Repertory repertory, Contact contact);

/*
 * Fonction qui modifie un contact par un autre dans une annuaire passé en
 * paramètre.
 * L'ancien contact est utilisé pour retrouver la position dans l'annaire,
 * ainsi seul les champs essentiels sont nécessaire : nom, prénom, mail.
 * Renvoie 1 si la modification à été éffectué, 0 sinon.
 */
int contact_file_modify(Repertory repertory, Contact oldContact,
                        Contact newContact);

/*
 * Supprime un contact dans un annuaire.
 * Copie dans un fichier temporaire le contenu de tout l'annuaire excepté
 * le contact passé en paramètre.
 * Le fichier temporaire est ensuite renommé par le nom de l'annuaire passé
 * en paramètre.
 * Renvoie 1 si la suppression du contact à été éffectué, 0 sinon.
 */
int contact_file_delete(Repertory repertory, Contact contact);

/*
 * Alloue en mémoire une chaine de caractère
 * On concatène ensuite dans cette chaine de caractère toutes les informations
 * des contacts dont la données est présente dans le nom, le prénom ou
 * l'addresse mail.
 * On cherche les contacts dans l'annuaire passé en paramètre.
 * La chaine est structuré de la manière suivante :
 * <TAB>{nom}:{prenom}:{email}::...:<TAB>{nom}:{prenom} etc...
 * Renvoie un pointeur vers cette chaine de caractère.
 */
char* contact_file_search(Repertory repertory, char* data);

#endif
