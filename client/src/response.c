/*******************************************************************************
 * Autheurs : RDSV Guillaume - STRMSEK Nicolas
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
    response->data = malloc((strlen(data)+1)*sizeof(char));
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

int response_get_code(Response response)
{
  return response->code;
}

char* response_get_data(Response response, int number)
{
 int counter;
 int counterNumber;
 char* data;

 data = response->data;
 if ( response->data != NULL ) {
   for ( counterNumber = 0; counterNumber < number-1; counterNumber++ ) {
     counter = 0;
     while ( data[counter] != '\t' && counter < strlen(data) ) {
       ++counter;
     }
     data = data+counter+1;
   }
 }

 return data;
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

Response response_transform(char* message)
{
 Response response;
 int code;
 int counterMessage;

 response = response_create();
 code = 0;
 counterMessage = 0;
 while ( message[counterMessage] != ' ' && message[counterMessage] != '\n'
         && counterMessage < strlen(message) ) {
   code *= 10;
   code += (message[counterMessage] - 48);
   ++counterMessage;
 }
 response->code = code;

 while ( message[counterMessage] != ' ' && counterMessage < strlen(message) ) {
   ++counterMessage;
 }
 if ( message+counterMessage != '\0' ) {
   response_set_data(response, message+counterMessage+1);
 }

 return response;
}
