#include <stdio.h>
#include <stdlib.h>
#include "dht.h"

int main(void) {

  char *result; 

  for(int i = 5; i > 0; i--) {
     read_dht22(&result); 
     printf("%s \n", result);
  }

  cleanup(result);
  return 0;
}
