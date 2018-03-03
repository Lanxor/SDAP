/*******************************************************************************
 * Autheurs : OLIVIER Thomas - RDSV Guillaume - STRMSEK Nicolas
 * Projet Annuaire Partagée - STRI
 * Fichier : SOURCE SESSION
 * Date : Janvier 2018
 * Etat : Terminé
 ******************************************************************************/

#include "../header/session.h"

/*
 * Initialise le tableau de session
 */
void session_init(void)
{
  int counter;

  counter = 0;
  while ( counter < SESSION_MAX ) {
    sessionTab[counter] = -1;
    ++counter;
  }
}

/*
 * Affiche toutes les sessions ouvertes
 */
void session_print(void)
{
  int counter;

  counter = 0;
  while ( counter < SESSION_MAX ) {
    if ( sessionTab[counter] >= 0 ) {
      printf("Session [%d] ouverte, identifiant : %d\n", counter+1, sessionTab[counter]);
    }
      ++counter;
  }
}

/*
 * Récupère l'identifiant du compte utilisateur associé à l'identifiant de
 * la session passé en paramètre.
 * Un identifiant 0 sinifie qu'il est annonyme, ou que la session n'est pas
 * ouverte, ou que l'identifiant dépasse la limite SESSION_MAX.
 * Un nombre positif est l'identifiant du compte utilisateur.
 * Renvoie l'identifiant associé à l'identifiant de session.
 */
int session_get_identifier(int idSession)
{
  if ( idSession > 0 && idSession < SESSION_MAX )
    return sessionTab[idSession-1];
  return 0;
}

/*
 * Ouvre une session pour un identifiant utilisateur
 * Un identifiant : 0 indique une connection annonyme
 * Renvoie l'identifiant de session : 0 < id < SESSION_MAX
 */
int session_open(int identifier)
{
  int counter;

  counter = 0;
  while ( sessionTab[counter] >= 0 && counter < SESSION_MAX ) {
    ++counter;
  }
  sessionTab[counter] = identifier;
  return counter+1;
}

/*
 * Ferme une session pour un identifiant session
 */
void session_close(int idSession)
{
  if ( idSession > 0 && idSession < SESSION_MAX )
    sessionTab[idSession-1] = -1;
}

/*
 * Vérifie si pour un identifiant session si une session est ouverte
 * Renvoie 1 si la session est ouverte, 0 sinon.
 */
int session_is_open(int idSession)
{
  if ( idSession == 0 || idSession > SESSION_MAX )
    return 0;
  return sessionTab[idSession-1] != -1;
}

/*
 * Vérifie si la session passé en paramètre est une session annonyme
 * ou si c'est un compte utilisateur.
 * Renvoie 1 si l'identifiant session est annonyme, 0 sinon.
 */
int session_is_annonyme(int idSession)
{
  if ( idSession > 0 && idSession < SESSION_MAX )
    return sessionTab[idSession-1] == 0;
  return 0;
}
