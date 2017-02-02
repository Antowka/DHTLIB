#include <stdio.h>
#include <stdlib.h>
#include "dht.h"

int main(void) {

  char* result = read_dht11(); 

  printf("%s \n", result);

  free(result);

  return 0;
}
