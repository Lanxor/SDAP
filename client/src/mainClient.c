#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../header/client.h"

int main(void) {

  if(InitialisationAvecService("localhost","6666") != 1) {
    printf("Erreur d'initialisation\n");
    return 1;
  }

  action_menu();


  Terminaison();

  return 0;
}
