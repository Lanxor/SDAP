/*******************************************************************************
 * Autheurs : OLIVIER Thomas - RDSV Guillaume - STRMSEK Nicolas
 * Projet Annuaire Partagée - STRI
 * Fichier : SOURCE RESPONSE
 * Date : Janvier 2018
 * Etat : Terminé
 ******************************************************************************/

#include "../header/response.h"

/*
 * Crée et initialise une nouvelle structure réponse.
 * Renvoie le pointeur vers la structure.
 */
Response response_create()
{
  Response response;

  response = malloc(sizeof(t_response));
  assert( response != NULL );

  response->code = 0;
  response->data = NULL;

  return response;
}

/*
 * Debug : Affiche les données de la structure réponse.
 */
void response_print(Response response)
{
  printf("Réponse : %d %s\n", response->code, response->data);
}

/*
 * Définit le code de la réponse.
 */
void response_set_code(Response response, int code)
{
  response->code = code;
}

/*
 * Définit la donnée de la réponse.
 * La donnée peut donnée une indication sur l'erreur rencontré.
 * Mais aussi les informations demander (un contact)
 */
void response_set_data(Response response, char* data)
{
  if ( response->data != NULL ) {
    free(response->data);
  }
  if ( data != NULL && strcmp(data, "") != 0 ) {
    response->data = malloc(strlen(data)*sizeof(char));
    assert( response->data != NULL );
    strcpy(response->data, data);
  }
}

/*
 * Rajoute aux données de la réponse les données passé en paramètre.
 * Permet ainsi de crée une liste d'argument.
 * Chaque argument est séparé par une tabulation, <TAB>, '\t'.
 */
void response_add_data(Response response, char* data)
{
  response->data = realloc(response->data,
                    (strlen(response->data) + 2 + strlen(data))*sizeof(char) );
  assert( response->data != NULL );
  strcat(response->data, "\t");
  strcat(response->data, data);
}

/*
 * Libére la mémoire de la structure d'une réponse.
 */
void response_delete(Response response)
{
  if ( response->data != NULL )
    free(response->data);
  if ( response != NULL )
    free(response);
}

/*
 * Envoie au client la réponse passé en paramètre
 * Si le client se déconnecte il ne recevra pas le message.
 * Renvoie 1 si le message à bien été envoyé, 0 sinon.
 */
int response_send(Response response)
{
  char* message;
  char nombre[11];

  sprintf(nombre, "%d", response->code);
  message = malloc((strlen(nombre)+1)*sizeof(char));
  strcpy(message, nombre);
  message[strlen(message)] = '\0';

  if ( response->data != NULL ) {
    message = realloc(message, (strlen(message) + 2 + strlen(response->data))*sizeof(char));
    strcat(message, " ");
    strcat(message, response->data);
  }
  response_print(response);
  if ( Emission(strcat(message,"\n")) == -1 ) {
    printf("Erreur d'émission\n");
    return 0;
  }

  return 1;
}

/*
 * Permet de crée une réponse personnalisé en spécifiant un code
 * et une donnée.
 * Envoie ensuite la réponse au client.
 * Renvoie 1 si le message à bien été envoyé, 0 sinon.
 */
int response_send_code(int code, char* data)
{
  Response response;
  int sended;

  response = response_create();
  response_set_code(response, code);
  switch( code ) {
    case 200 :
      response_set_data(response, "Ok ");
      break;
    case 400 :
      response_set_data(response, "Bad Request ");
      break;
    case 401 :
      response_set_data(response, "Unauthorized ");
      break;
    case 404 :
      response_set_data(response, "Not Found ");
      break;
    case 500 :
      response_set_data(response, "Server error ");
      break;
    default :
      response_set_data(response, "");
  }
  if ( data != NULL && strcmp(data, "") != 0 ) {
    response_add_data(response, data);
  }
  sended = response_send(response);
  response_delete(response);

  return sended;
}

/*
 * Envoie une réponse avec comme seul paramètre l'identifiant de connexion.
 * Cette réponse est uniquement utilisé lorsqu'un client souhaite ce
 * connecter. L'identifiant de session est ensuite envoyé au client.
 */
int response_send_identifiant(int idSession)
{
  char nombre[11];

  sprintf(nombre, "%d", idSession);
  return response_send_code(200, nombre);
}
