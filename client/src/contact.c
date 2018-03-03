/*******************************************************************************
 * Autheurs : RDSV Guillaume - STRMSEK Nicolas
 * Projet Annuaire Partagée - STRI
 * Fichier : SOURCE CONTACT
 * Date : Janvier 2018
 * Etat : Terminé
 ******************************************************************************/
#include "../header/contact.h"

/*
 * Crée et initialise une nouvelle structre d'un contact.
 * Renvoie le pointeur vers cette structure.
 */
Contact contact_create()
{
  Contact contact;
  int counter;

  contact = malloc(sizeof(t_contact));
  assert( contact != NULL );
  for ( counter = 0; counter < CONTACT_CHAR_MAX_NAME+1; counter++ )
    contact->name[counter] = '\0';
  for ( counter = 0; counter < CONTACT_CHAR_MAX_SURNAME+1; counter++ )
    contact->surname[counter] = '\0';
  for ( counter = 0; counter < CONTACT_CHAR_MAX_MAIL+1; counter++ )
    contact->mail[counter] = '\0';
  for ( counter = 0; counter < CONTACT_CHAR_MAX_PHONE+1; counter++ )
    contact->phone[counter] = '\0';
  for ( counter = 0; counter < CONTACT_CHAR_MAX_PHONE+1; counter++ )
    contact->proPhone[counter] = '\0';
  for ( counter = 0; counter < CONTACT_CHAR_MAX_ADDRESS+1; counter++ )
    contact->address[counter] = '\0';
  for ( counter = 0; counter < CONTACT_CHAR_MAX_BIRTHDAY+1; counter++ )
    contact->birthday[counter] = '\0';
  for ( counter = 0; counter < CONTACT_CHAR_MAX_NOTES+1; counter++ )
    contact->notes[counter] = '\0';

  return contact;
}

/*
 * Debug : Affiche les données de la structure contact.
 */
void contact_print(Contact contact)
{
  printf("Contact information :\n");
  printf("Nom : %s\nPrénom : %s\n", contact->name, contact->surname);
  printf("Mail : %s\n", contact->mail);
  printf("Phone : %s - %s\n", contact->phone, contact->proPhone);
  printf("Adresse : %s\n", contact->address);
  printf("Naissance : %s\n", contact->birthday);
  printf("Notes : %s\n", contact->notes);
}

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
void contact_setter(char* pointer, char* data, int sizeCharMax)
{
  int counter;

  counter = 0;
  while ( data[counter] != ':' && data[counter] != '\t' && data[counter] != '\n'
          && data[counter] != '\0' && counter < sizeCharMax ) {
    pointer[counter] = data[counter];
    ++counter;
  }
  pointer[counter] = '\0';
}

/*
 * Définit le nom d'un contact passé en paramètre à l'aide de la donnée passé
 * en paramètre et qui sera traiter par la fonction "contact_setter".
 */
void contact_set_name(Contact contact, char* data)
{
  contact_setter(contact->name, data, CONTACT_CHAR_MAX_NAME);
}

/*
 * Définit le prénom d'un contact passé en paramètre à l'aide de la donnée passé
 * en paramètre et qui sera traiter par la fonction "contact_setter".
 */
void contact_set_surname(Contact contact, char* data)
{
  contact_setter(contact->surname, data, CONTACT_CHAR_MAX_SURNAME);
}

/*
 * Définit le mail d'un contact passé en paramètre à l'aide de la donnée passé
 * en paramètre et qui sera traiter par la fonction "contact_setter".
 */
void contact_set_mail(Contact contact, char* data)
{
  contact_setter(contact->mail, data, CONTACT_CHAR_MAX_MAIL);
}

/*
 * Définit le numéro de téléphone personnel d'un contact passé en paramètre à
 * l'aide de la donnée passé en paramètre et qui sera traiter par la fonction
 * "contact_setter".
 */
void contact_set_phone(Contact contact, char* data)
{
  contact_setter(contact->phone, data, CONTACT_CHAR_MAX_PHONE);
}

/*
 * Définit le numéro de téléphone professionnel d'un contact passé en paramètre
 * à l'aide de la donnée passé en paramètre et qui sera traiter par la fonction
 * "contact_setter".
 */
void contact_set_prophone(Contact contact, char* data)
{
  contact_setter(contact->proPhone, data, CONTACT_CHAR_MAX_PHONE);
}

/*
 * Définit l'addresse d'un contact passé en paramètre à l'aide de la donnée
 * passé en paramètre et qui sera traiter par la fonction "contact_setter".
 */
void contact_set_address(Contact contact, char* data)
{
  contact_setter(contact->address, data, CONTACT_CHAR_MAX_ADDRESS);
}

/*
 * Définit la date d'anniversaire d'un contact passé en paramètre à l'aide de
 * la donnée passé en paramètre et qui sera traiter par la fonction
 * "contact_setter".
 */
void contact_set_birthday(Contact contact, char* data)
{
  contact_setter(contact->birthday, data, CONTACT_CHAR_MAX_BIRTHDAY);
}

/*
 * Définit les remarques d'un contact passé en paramètre à l'aide de la donnée
 * passé en paramètre et qui sera traiter par la fonction "contact_setter".
 */
void contact_set_notes(Contact contact, char* data)
{
  contact_setter(contact->notes, data, CONTACT_CHAR_MAX_NOTES);
}

/*
 * Libére la mémoire de la structure contact d'un annuaire.
 */
void contact_delete(Contact contact)
{
  if ( contact != NULL )
    free(contact);
}

/*
 * Vérifie le contact passé en paramètre est valide.
 * Pour qu'un contact soit valide, il faut que son nom, son prénom et son
 * mail ne soit pas vide.
 * Renvoie 1 si le contact est valide, 0 sinon.
 */
int contact_is_valid(Contact contact)
{
  return strcmp(contact->name, "") != 0 && strcmp(contact->surname, "") != 0
         && strcmp(contact->mail, "") != 0;
}

/*
 * Transforme un contact en une chaine de caractère
 */
char* contact_transform(Contact contact)
{
  char* message;
  int size;

  size = strlen(contact->name) + strlen(contact->surname)
         + strlen(contact->mail) + strlen(contact->phone)
         + strlen(contact->proPhone) + strlen(contact->address)
         + strlen(contact->birthday) + strlen(contact->notes);
  message = malloc((size+8)*sizeof(char));
  assert( message != NULL );
  strcpy(message, contact->name);
  strcat(message, ":");
  strcat(message, contact->surname);
  strcat(message, ":");
  strcat(message, contact->mail);
  strcat(message, ":");
  if ( strcmp(contact->phone, "") != 0 ) {
    strcat(message, contact->phone);
  }
  strcat(message, ":");
  if ( strcmp(contact->proPhone, "") != 0 ) {
    strcat(message, contact->proPhone);
  }
  strcat(message, ":");
  if ( strcmp(contact->address, "") != 0 ) {
    strcat(message, contact->address);
  }
  strcat(message, ":");
  if ( strcmp(contact->birthday, "") != 0 ) {
    strcat(message, contact->birthday);
  }
  strcat(message, ":");
  if ( strcmp(contact->notes, "") != 0 ) {
    strcat(message, contact->notes);
  }

  return message;
}
