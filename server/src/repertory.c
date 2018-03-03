/*******************************************************************************
 * Autheurs : OLIVIER Thomas - RDSV Guillaume - STRMSEK Nicolas
 * Projet Annuaire Partagée - STRI
 * Fichier : SOURCE REPERTORY
 * Date : Janvier 2018
 * Etat : Terminé
 ******************************************************************************/

#include "../header/repertory.h"

/*
 * Crée et initialise une nouvelle structure annuaire
 * Renvoie le pointeur vers la structure.
 */
Repertory repertory_create()
{
  Repertory repertory;


  repertory = malloc(sizeof(t_repertory));
  assert( repertory != NULL );
  repertory->ownerIdentifier = 0;
  repertory->pathName = NULL;
  return repertory;
}

/*
 * Debug : Affiche les données de la structure annuaire.
 */
void repertory_print(Repertory repertory)
{
  printf("Owner [%d], %s\n", repertory->ownerIdentifier,
         repertory->pathName);
}

/*
 * Définit l'identifiant utilisateur pour un annuaire.
 */
void repertory_set_owneridentifier(Repertory repertory, int ownerIdentifier)
{
  repertory->ownerIdentifier = ownerIdentifier;
}

/*
 * Définit le chemin d'accés à l'annuaire.
 * on lui passe le nom de l'annuaire "{nom}" et il crée le chemin de
 * l'annuaire "./repertory/{nom}"
 * Le nom est récupéré par une structure {nom}<TAB> ou {nom}<CR> ou jusqu'à
 * la fin de la chaine de caractère passé en argument.
 */
void repertory_set_name(Repertory repertory, char* name)
{
  int counter;
  int counterName;

  if ( repertory->pathName != NULL ) {
    free(repertory->pathName);
  }

  counterName = 0;
  while ( counterName < strlen(name) && name[counterName] != '\t' )
    ++counterName;

  repertory->pathName = malloc((12 + counterName + 1)*sizeof(char));
  strcpy(repertory->pathName, "./repertory/");
  strncat(repertory->pathName, name, counterName);
  repertory->pathName[strlen(repertory->pathName)] = '\0';
  printf("%s\n", repertory->pathName);
}

/*
 * Renvoie le chemin du répertoire passé en paramètre.
 */
char* repertory_get_path(Repertory repertory)
{
  return repertory->pathName;
}

/*
 * Libére la mémoire de la structure annuaire
 */
void repertory_delete(Repertory repertory)
{
  if ( repertory->pathName != NULL )
    free(repertory->pathName);
  if ( repertory != NULL )
    free(repertory);
}

/*
 * Vérifie si le fichier annuaire existe ou pas.
 * Renvoie 1 s'il existe, 0 sinon.
 */
int repertory_file_exist(Repertory repertory)
{
  FILE* fileRepertory;

  fileRepertory = fopen(repertory->pathName, "rb");
  if ( fileRepertory != NULL ) {
    fclose(fileRepertory);
    return 1;
  }
  return 0;
}

/*
 * Vérifie si l'identifiant définit dans l'annuaire passé en paramètre
 * correspond à celui inscrit dans le fichier annuaire.
 * Renvoie 1 si il est le propriétaire, 0 sinon.
 */
int repertory_is_owner(Repertory repertory)
{
  FILE* fileRepertory;
  int identifier;

  fileRepertory = fopen(repertory->pathName, "rb");
  if ( fileRepertory != NULL ) {
    fread(&identifier, sizeof(int), 1, fileRepertory);
    fclose(fileRepertory);
  }
  return repertory->ownerIdentifier == identifier;
}

/*
 * Crée le fichier annuaire, ne le crée pas s'il existe déjà
 * inscrit en plus l'identifiant utilisateur dans le fichier
 * Renvoie 1 si le fichier est crée, 0 sinon.
 */
int repertory_file_create(Repertory repertory)
{
  FILE* fileRepertory;

  if ( !repertory_file_exist(repertory) ) {
    fileRepertory = fopen(repertory->pathName, "w+b");
    if ( fileRepertory != NULL ) {
      fwrite(&repertory->ownerIdentifier, sizeof(int), 1, fileRepertory);
      fclose(fileRepertory);
      return 1;
    }
  }
  return 0;
}

/*
 * Change le nom de l'annuaire. On admet que l'utilisateur est le propriétaire
 * Vérifie si l'ancien répertoire existe et si le nouveau n'existe pas.
 * Renvoie 1 si le nom est modifié, 0 sinon.
 */
int repertory_file_modify(Repertory oldRepertory, Repertory newRepertory)
{
  if ( repertory_file_exist(oldRepertory) && !repertory_file_exist(newRepertory) ) {
    return rename(oldRepertory->pathName,
                  newRepertory->pathName) == 0;
  }
  return 0;
}

/*
 * Supprime l'annuaire en entier. On admet que l'utilisateur est le propriétaire
 * Vérifie si le l'annuaire existe.
 * Renvoie 1 si il est supprimer, 0 sinon.
 */
int repertory_file_delete(Repertory repertory)
{
  if ( repertory_file_exist(repertory) )
    return remove(repertory->pathName) == 0;
  return 0;
}

/*
 * Alloue en mémoire une chaine de caractère
 * On concatène ensuite dans cette chaine de caractère les noms des annuaires
 * dont une occurence de la donnée en paramètre ce trouve dans le nom de
 * l'annuaire.
 * La chaine est structuré de la manière suivante :
 * <TAB>{nom}<TAB>{nom} etc...
 * Renvoie un pointeur vers cette chaine de caractère.
 */
char* repertory_file_search(char* data)
{
  char* search;
  struct dirent *entry;
  DIR *dir;

  search = NULL;
  dir = opendir("./repertory/" );
  while ( (entry = readdir(dir)) ) {
    if ( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ) {
      if ( strcmp(data, "") == 0 ) {
        if ( search == NULL ) {
          search = malloc(strlen(entry->d_name)*sizeof(char));
          strcpy(search, entry->d_name);
        }
        else {
          search = realloc(search, (strlen(search) + 2 + strlen(entry->d_name))*sizeof(char));
          assert( search != NULL );
          strcat(search, "\t");
          strcat(search, entry->d_name);
        }
      }
      else if ( strstr(entry->d_name, data) != NULL ) {
        if ( search == NULL ) {
          search = malloc(strlen(entry->d_name)*sizeof(char));
          strcpy(search, entry->d_name);
        }
        else {
          search = realloc(search, (strlen(search) + 1 + strlen(entry->d_name))*sizeof(char));
          assert( search != NULL );
          strcat(search, "\t");
          strcat(search, entry->d_name);
        }
      }
    }
  }
  closedir(dir);

  return search;
}
