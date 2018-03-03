#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../header/client.h"

int main( int argc, char *argv[] ) {
  int counter;
  char message[500];

  if ( argc > 1 ) {
    if ( InitialisationAvecService("localhost","6666") != 1 ) {
      printf("Erreur d'initialisation\n");
      return 1;
    }
    strcpy(message, argv[1]);
    for ( counter = 2; counter < argc; counter++ ) {
      if ( counter < 3 ) {
        strcat(message, " ");
        strcat(message, argv[counter]);
      }
      else {
        strcat(message, "\t");
        strcat(message, argv[counter]);
      }
    }
    printf("%s\n", message);

    if ( Emission(strcat(message,"\n")) == -1 ) {
      printf("Erreur d'émission\n");
      return 1;
    }

    strcpy(message, Reception());
    if ( message != NULL ) {
      printf("Message : %s", message);
    }
  }
  Terminaison();

  return 0;
}
