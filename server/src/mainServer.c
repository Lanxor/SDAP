/*******************************************************************************
 * Autheurs : OLIVIER Thomas - RDSV Guillaume - STRMSEK Nicolas
 * Projet Annuaire Partagée - STRI
 * Fichier : SOURCE MAIN SERVER
 * Date : Janvier 2018
 * Etat : Terminé
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../header/server.h"

int main( void ) {
  Request request;
  char *message;
  int fini;
  int idSession;

  Initialisation();
  session_init();

  while( 1 ) {

    AttenteClient();

    fini = 0;
    while ( !fini ) {
      message = Reception();
      if ( message != NULL ) {
        request = request_transform(message);
        request_print(request);
        action_request_trait(request);
        request_delete(request);
      }
      else {
        fini = 1;
      }
    }
    TerminaisonClient();
  }

  return 0;
}
