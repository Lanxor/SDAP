/*******************************************************************************
 * Autheurs : OLIVIER Thomas - RDSV Guillaume - STRMSEK Nicolas
 * Projet Annuaire Partagée - STRI
 * Fichier : SOURCE ACCOUNT
 * Date : Janvier 2018
 * Etat : Terminé
 ******************************************************************************/

 #include "../header/account.h"

/*
 * Crée et initialise une nouvelle structure compte utilisateur
 * Renvoie le pointeur vers la structure.
 */
Account account_create(void)
{
  Account account;
  int counter;

  account = malloc(sizeof(t_account));
  assert( account != NULL );
  account->identifier = 0;
  counter = 0;
  for ( counter = 0; counter < ACCOUNT_CHAR_MAX_NAME+1; counter++ )
    account->name[counter] = '\0';
  for ( counter = 0; counter < ACCOUNT_CHAR_MAX_PASSWORD+1; counter++ )
    account->password[counter] = '\0';
  return account;
}

/*
 * Debug : Affiche les données de la structure annuaire.
 */
void account_print(Account account)
{
  printf("[%d] %s %s\n", account->identifier, account->name, account->password);
}

/*
 * Définit l'identifiant d'un compte utilisateur
 */
void account_set_identifier(Account account, int identifier)
{
  account->identifier = identifier;
}

/*
 * Définit le nom d'utilisateur du compte utilisateur passé en paramètre.
 * On récupère le nom à partir des données passé en paramètre,
 * le message doit avoir la structure suivante : {nom}<TAB> ou {nom}<CR>
 */
void account_set_name(Account account, char* data)
{
  int counter;

  counter = 0;
  while ( data[counter] != '\t' && data[counter] != '\n'
          && data[counter] != '\0' && counter < ACCOUNT_CHAR_MAX_NAME ) {
    account->name[counter] = data[counter];
    ++counter;
  }
  account->name[counter] = '\0';
}

/*
 * Définit le mot de passe du compte utilisateur passé en paramètre.
 * On récupère le mot de passe à partir des données passé en paramètre,
 * le message doit avoir la structure suivante : {mdp}<TAB> ou {mdp}<CR>
 */
void account_set_password(Account account, char* data)
{
  int counter;

  counter = 0;
  while ( data[counter] != '\t' && data[counter] != '\n'
          && data[counter] != '\0' && counter < ACCOUNT_CHAR_MAX_PASSWORD ) {
    account->password[counter] = data[counter];
    ++counter;
  }
  account->password[counter] = '\0';
}

/*
 * Récupère et renvoie la valeur "identifiant" de la structure logique d'un
 * compte utilisateur passé en paramètre.
 */
int account_get_identifier(Account account)
{
  return account->identifier;
}

/*
 * Récupère le mot de passe d'une structure logique d'un compte utilisateur
 * passé en paramètre.
 * Renvoie le pointeur vers cette chaine de caractères.
 */
char* account_get_password(Account account)
{
  return account->password;
}

/*
 * Libére la mémoire de la structure compte utilisateur.
 */
void account_delete(Account account)
{
  if ( account != NULL )
    free(account);
}

/*
 * Vérifie caractére par caractére si le mot de passe du compte et celui de
 * la donnée passé en paramètre sont identique.
 * Compare la donnée jusqu'à arriver à la fin de la chaine ou s'il rencontre
 * tabulation "<TAB>".
 * Renvoie 1 si les deux mot de passe sont identique, 0 sinon.
 */
int account_is_same_password(Account account, char* data)
{
  int counter;

  counter = 0;
  while ( counter < strlen(account->password) ) {
    if ( account->password[counter] != data[counter] ) {
      return 0;
    }
    ++counter;
  }
  if ( data[counter] != '\t' && data[counter] != '\n'
       && data[counter] != '\0' ) {
    return 0;
  }

  return 1;
}

/*
 * Récupère le prochain identifier utilisateur
 * Renvoie l'identifiant.
 * Si aucun compte utilisateur n'est enregistré renvoie la valeur 1
 * pour le premier compte utilisateur.
 */
int account_get_next_identifier()
{
  Account currentAccount;
  FILE* fileAccount;
  int nextIdentifier;

  nextIdentifier = 0;
  fileAccount = fopen("registre.account", "rb");
  if ( fileAccount != NULL ) {
    currentAccount = account_create();
    while ( feof(fileAccount) == 0 ) {
      fread(currentAccount, sizeof(t_account), 1, fileAccount);
    }
    nextIdentifier = currentAccount->identifier;
    fclose(fileAccount);
    account_delete(currentAccount);
  }
  return nextIdentifier+1;
}

/*
 * Vérifie si le compte utilisateur est inscrit dans le fichier utilisateur.
 * Renvoie 1 si le compte utilisateur est inscrit, 0 sinon.
 */
int account_file_exist(Account account)
{
  Account currentAccount;
  FILE* fileAccount;
  int exist;

  exist = 0;
  fileAccount = fopen("registre.account", "rb");
  if ( fileAccount != NULL ) {
    currentAccount = account_create();
    while ( !exist && feof(fileAccount) == 0 ) {
      fread(currentAccount, sizeof(t_account), 1, fileAccount);
      if ( strcmp(account->name, currentAccount->name) == 0
           && strcmp(account->password, currentAccount->password) == 0 ) {
        account->identifier = currentAccount->identifier;
        exist = 1;
      }
    }
    fclose(fileAccount);
    account_delete(currentAccount);
  }

  return exist;
}

/*
 * Enregistre dans un fichier la structure du compte utilisateur.
 * Si le fichier n'existe pas, il est crée.
 * Renvoie 1 si l'enregistrement du compte à été effectué, 0 sinon.
 */
int account_file_create(Account account)
{
  FILE* fileAccount;
  int created;

  created = 0;
  fileAccount = fopen("registre.account", "a+b");
  if ( fileAccount != NULL ) {
    fwrite(account, sizeof(t_account), 1, fileAccount);
    fclose(fileAccount);
    created = 1;
  }

  return created;
}

/*
 * Récupère les informations d'un compte utilisateur dans une structure
 * logique d'un compte utilisateur en fonction de l'identifiant de compte
 * utilisateur.
 * On admet que le compte est déjà enregistré.
 * Renvoie une structure de compte utilisateur.
 */
Account account_file_load(int identifier)
{
  Account account;
  Account currentAccount;
  FILE* fileAccount;

  account = NULL;
  fileAccount = fopen("registre.account", "rb");
  if ( fileAccount != NULL ) {
    currentAccount = account_create();
    while ( feof(fileAccount) == 0 ) {
      fread(currentAccount, sizeof(t_account), 1, fileAccount);
      if ( currentAccount->identifier == identifier ) {
        account = account_create();
        account->identifier = currentAccount->identifier;
        account_set_name(account, currentAccount->name);
        account_set_password(account, currentAccount->password);
      }
    }
    fclose(fileAccount);
    account_delete(currentAccount);
  }
  return account;
}

/*
 * Fonction qui modifie seulement le mot de passe d'un compte utilisateur.
 * L'identifiant de compte utilisateur ne doit pas changer.
 * Renvoie 1 si la modification à été éffectuer, 0 sinon.
 */
int account_file_modify(Account account)
{
  Account currentAccount;
  FILE* fileAccount;
  int modified;

  modified = 0;
  fileAccount = fopen("registre.account", "r+b");
  if ( fileAccount != NULL ) {
    currentAccount = account_create();
    while ( !modified && feof(fileAccount) == 0 ) {
      fread(currentAccount, sizeof(t_account), 1, fileAccount);
      if ( strcmp(account->name, currentAccount->name) == 0 ) {
        fseek(fileAccount, -sizeof(t_account), SEEK_CUR);
        fwrite(account, sizeof(t_account), 1, fileAccount);
        modified = 1;
      }
    }
    fclose(fileAccount);
    account_delete(currentAccount);
  }

  return modified;
}

/*
 * Supprime un compte utilisateur enregistré.
 * Parcours le fichier "registre.account" en lecture et écrit dans un nouveau
 * fichier "registre.account.tmp" tous les comptes utilisateur sauf celui
 * passé en paramètre.
 * renomme ensuite le fichier temporaire en "registre.account" (écrasement)
 * Renvoie 1 si la suppression est effectuer, 0 sinon.
 */
int account_file_delete(Account account)
{
  Account currentAccount;
  FILE* oldFile;
  FILE* newFile;
  int deleted;

  deleted = 0;
  oldFile = fopen("registre.account", "r+b");
  newFile = fopen("registre.account.tmp", "a+b");
  if ( oldFile != NULL && newFile != NULL ) {
    currentAccount = account_create();
    while( feof(oldFile) == 0 ) {
      fread(currentAccount, sizeof(t_account), 1, oldFile);
      if ( !feof(oldFile) && strcmp(currentAccount->name, account->name) != 0 ) {
        fwrite(currentAccount, sizeof(t_account), 1, newFile);
      }
    }
    fclose(oldFile);
    fclose(newFile);
    if ( rename("registre.account.tmp", "registre.account") == 0 ) {
      deleted = 1;
    }
    account_delete(currentAccount);
  }

  return deleted;
}
