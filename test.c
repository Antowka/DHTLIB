#include <stdio.h>
#include <stdlib.h>
#include "dht.h"

int main(void) {

  char *result; 
  read_dht22(&result); 
  printf("%s \n", result);
  cleanup(result);
  return 0;
}
