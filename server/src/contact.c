/*******************************************************************************
 * Autheurs : OLIVIER Thomas - RDSV Guillaume - STRMSEK Nicolas
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
 * Vérifie si les deux contact passé en paramètre sont identique.
 * Seul les champs nom, prénom et mail sont vérifié pour définir si un
 * contact ressemble à un autre.
 * Renvoie 1 si les deux contact sont identique, 0 sinon.
 */
int contact_is_same(Contact firstContact, Contact secondContact)
{
  return strcmp(firstContact->name, secondContact->name) == 0
       && strcmp(firstContact->surname, secondContact->surname) == 0
       && strcmp(firstContact->mail, secondContact->mail) == 0;
}

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
Contact contact_transform(char* data)
{
  Contact contact;
  int numberElement;
  int counter;

  contact = contact_create();
  counter = 0;
  numberElement = 0;
  while ( numberElement < 8 && counter < strlen(data) && data[counter] != '\t'
          && data[counter] != '\n' && data[counter] != '\0' ) {
    switch (numberElement) {
      case 0:
        contact_set_name(contact, data+counter);
        break;
      case 1:
        contact_set_surname(contact, data+counter);
        break;
      case 2:
        contact_set_mail(contact, data+counter);
        break;
      case 3:
        contact_set_phone(contact, data+counter);
        break;
      case 4:
        contact_set_prophone(contact, data+counter);
        break;
      case 5:
        contact_set_address(contact, data+counter);
        break;
      case 6:
        contact_set_birthday(contact, data+counter);
        break;
      case 7:
        contact_set_notes(contact, data+counter);
        break;
    }
    while ( data[counter] != ':' && data[counter] != '\t'
            && data[counter] != '\n' && data[counter] != '\0' ) {
      ++counter;
    }
    ++counter;
    ++numberElement;
  }
  return contact;
}

/*
 * Vérifie si le contact passé en paramètre existe dans l'annuaire passé en
 * paramètre.
 * Vérifie le nom, le prénom et le mail.
 * Renvoie 1 si le contact existe dans l'annuaire, 0 sinon.
 */
int contact_file_exist(Repertory repertory, Contact contact)
{
  Contact currentContact;
  FILE* fileRepertory;
  int exist;

  exist = 0;
  fileRepertory = fopen(repertory_get_path(repertory), "rb");
  if ( fileRepertory != NULL ) {
    fseek(fileRepertory, sizeof(int), SEEK_SET);
    currentContact = contact_create();
    while ( !exist && feof(fileRepertory) == 0 ) {
      fread(currentContact, sizeof(t_contact), 1, fileRepertory);
      if ( strcmp(currentContact->name, contact->name) == 0
           && strcmp(currentContact->surname, contact->surname) == 0
           && strcmp(currentContact->mail, contact->mail) == 0 ) {
        exist = 1;
      }
   }
   fclose(fileRepertory);
   contact_delete(currentContact);
  }

  return exist;
}

/*
 * Enregistre dans un fichier répertoire le contact passé en paramètre.
 * Il faut que l'annuaire existe.
 * Ajoute à la fin du fichier annuaire.
 * Renvoie 1 si le contact à été enregistré, 0 sinon.
 */
int contact_file_create(Repertory repertory, Contact contact)
{
  FILE* fileRepertory;
  int created;

  created = 0;
  fileRepertory = fopen(repertory_get_path(repertory), "a+b");
  if ( fileRepertory != NULL ) {
    fwrite(contact, sizeof(t_contact), 1, fileRepertory);
    fclose(fileRepertory);
    created = 1;
  }

  return created;
}

/*
 * Fonction qui modifie un contact par un autre dans une annuaire passé en
 * paramètre.
 * L'ancien contact est utilisé pour retrouver la position dans l'annaire,
 * ainsi seul les champs essentiels sont nécessaire : nom, prénom, mail.
 * Renvoie 1 si la modification à été éffectué, 0 sinon.
 */
int contact_file_modify(Repertory repertory, Contact oldContact,
                        Contact newContact)
{
  Contact currentContact;
  FILE* fileRepertory;
  int modified;

  modified = 0;
  fileRepertory = fopen(repertory_get_path(repertory), "r+b");
  if ( fileRepertory != NULL ) {
    currentContact = contact_create();
    fseek(fileRepertory, sizeof(int), SEEK_SET);
    while ( !modified && !feof(fileRepertory) ) {
      fread(currentContact, sizeof(t_contact), 1, fileRepertory);
      if ( strcmp(oldContact->name, currentContact->name) == 0
           && strcmp(oldContact->surname, currentContact->surname) == 0
           && strcmp(oldContact->mail, currentContact->mail) == 0 ) {
        fseek(fileRepertory, -sizeof(t_contact), SEEK_CUR);
        fwrite(newContact, sizeof(t_contact), 1, fileRepertory);
        modified = 1;
      }
    }
    fclose(fileRepertory);
    contact_delete(currentContact);
  }

  return modified;
}

/*
 * Supprime un contact dans un annuaire.
 * Copie dans un fichier temporaire le contenu de tout l'annuaire excepté
 * le contact passé en paramètre.
 * Le fichier temporaire est ensuite renommé par le nom de l'annuaire passé
 * en paramètre.
 * Renvoie 1 si la suppression du contact à été éffectué, 0 sinon.
 */
int contact_file_delete(Repertory repertory, Contact contact)
{
  Contact currentContact;
  FILE* oldFile;
  FILE* newFile;
  int ownerIdentifier;
  int deleted;

  deleted = 0;
  oldFile = fopen(repertory_get_path(repertory), "r+b");
  newFile = fopen("repertory.tmp", "w+b");
  if ( oldFile != NULL && newFile != NULL ) {
    fread(&ownerIdentifier, sizeof(int), 1, oldFile);
    fwrite(&ownerIdentifier, sizeof(int), 1, newFile);
    currentContact = contact_create();
    while( feof(oldFile) == 0 ) {
      fread(currentContact, sizeof(t_contact), 1, oldFile);
      if ( !feof(oldFile) ) {
        if ( !contact_is_same(currentContact, contact) ) {
        fwrite(currentContact, sizeof(t_contact), 1, newFile);
        }
        else {
          deleted = 1;
        }
      }
    }
    fclose(oldFile);
    fclose(newFile);
    rename("repertory.tmp", repertory_get_path(repertory));
    contact_delete(currentContact);
  }

  return deleted;
}

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
char* contact_file_search(Repertory repertory, char* data)
{
  Contact currentContact;
  FILE* fileRepertory;
  char* search;
  int sizeContact;

  search = NULL;
  fileRepertory = fopen(repertory_get_path(repertory), "r+b");
  if ( fileRepertory != NULL ) {
    currentContact = contact_create();
    fseek(fileRepertory, sizeof(int), SEEK_SET);
    while ( !feof(fileRepertory) ) {
      fread(currentContact, sizeof(t_contact), 1, fileRepertory);
      if ( !feof(fileRepertory) && (strstr(currentContact->name, data) != NULL
           || strstr(currentContact->surname, data) != NULL
           || strstr(currentContact->mail, data) != NULL) ) {

        sizeContact = strlen(currentContact->name)
          + strlen(currentContact->surname) + strlen(currentContact->mail)
           + strlen(currentContact->phone)
          + strlen(currentContact->proPhone) + strlen(currentContact->address)
          + strlen(currentContact->birthday) + strlen(currentContact->notes);

        if ( strcmp(data, "") == 0 ) {
          if ( search == NULL ) {
            search = malloc((sizeContact+7)*sizeof(char));
            assert( search != NULL );
            strcpy(search, currentContact->name);
            strcat(search, ":");
            strcat(search, currentContact->surname);
            strcat(search, ":");
            strcat(search, currentContact->mail);
            if ( strcmp(currentContact->phone, "\0") != 0 ) {
              strcat(search, ":");
              strcat(search, currentContact->phone);
            }
            if ( strcmp(currentContact->proPhone, "\0") != 0 ) {
              strcat(search, ":");
              strcat(search, currentContact->proPhone);
            }
            if ( strcmp(currentContact->address, "\0") != 0 ) {
              strcat(search, ":");
              strcat(search, currentContact->address);
            }
            if ( strcmp(currentContact->birthday, "\0") != 0 ) {
              strcat(search, ":");
              strcat(search, currentContact->birthday);
            }
            if ( strcmp(currentContact->notes, "\0") != 0 ) {
              strcat(search, ":");
              strcat(search, currentContact->notes);
            }
          }
          else {
            search = realloc(search, (strlen(search)+sizeContact+7+1)*sizeof(char));
            assert( search != NULL );
            strcat(search, "\t");
            strcat(search, currentContact->name);
            strcat(search, ":");
            strcat(search, currentContact->surname);
            strcat(search, ":");
            strcat(search, currentContact->mail);
            if ( strcmp(currentContact->phone, "\0") != 0 ) {
              strcat(search, ":");
              strcat(search, currentContact->phone);
            }
            if ( strcmp(currentContact->proPhone, "\0") != 0 ) {
              strcat(search, ":");
              strcat(search, currentContact->proPhone);
            }
            if ( strcmp(currentContact->address, "\0") != 0 ) {
              strcat(search, ":");
              strcat(search, currentContact->address);
            }
            if ( strcmp(currentContact->birthday, "\0") != 0 ) {
              strcat(search, ":");
              strcat(search, currentContact->birthday);
            }
            if ( strcmp(currentContact->notes, "\0") != 0 ) {
              strcat(search, ":");
              strcat(search, currentContact->notes);
            }
          }
        }
        else {
          if ( search == NULL ) {
            search = malloc((sizeContact+7)*sizeof(char));
            assert( search != NULL );
            strcpy(search, currentContact->name);
            strcat(search, ":");
            strcat(search, currentContact->surname);
            strcat(search, ":");
            strcat(search, currentContact->mail);
            if ( strcmp(currentContact->phone, "\0") != 0 ) {
              strcat(search, ":");
              strcat(search, currentContact->phone);
            }
            if ( strcmp(currentContact->proPhone, "\0") != 0 ) {
              strcat(search, ":");
              strcat(search, currentContact->proPhone);
            }
            if ( strcmp(currentContact->address, "\0") != 0 ) {
              strcat(search, ":");
              strcat(search, currentContact->address);
            }
            if ( strcmp(currentContact->birthday, "\0") != 0 ) {
              strcat(search, ":");
              strcat(search, currentContact->birthday);
            }
            if ( strcmp(currentContact->notes, "\0") != 0 ) {
              strcat(search, ":");
              strcat(search, currentContact->notes);
            }
          }
          else {
            search = realloc(search, (strlen(search)+sizeContact+7+1)*sizeof(char));
            assert( search != NULL );
            strcat(search, "\t");
            strcat(search, currentContact->name);
            strcat(search, ":");
            strcat(search, currentContact->surname);
            strcat(search, ":");
            strcat(search, currentContact->mail);
            if ( strcmp(currentContact->phone, "\0") != 0 ) {
              strcat(search, ":");
              strcat(search, currentContact->phone);
            }
            if ( strcmp(currentContact->proPhone, "\0") != 0 ) {
              strcat(search, ":");
              strcat(search, currentContact->proPhone);
            }
            if ( strcmp(currentContact->address, "\0") != 0 ) {
              strcat(search, ":");
              strcat(search, currentContact->address);
            }
            if ( strcmp(currentContact->birthday, "\0") != 0 ) {
              strcat(search, ":");
              strcat(search, currentContact->birthday);
            }
            if ( strcmp(currentContact->notes, "\0") != 0 ) {
              strcat(search, ":");
              strcat(search, currentContact->notes);
            }
          }
        }
      }


    }
    fclose(fileRepertory);
    contact_delete(currentContact);
  }

  if ( search != NULL ) {
    search = realloc(search, (strlen(search)+1)*sizeof(char));
    search[strlen(search)] = '\0';
  }

  return search;
}
