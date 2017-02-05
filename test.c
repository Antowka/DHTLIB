#include <stdio.h>
#include <stdlib.h>
#include "dht.h"

int main(void) {

  char result[36]; 
  read_dht22(result); 
  printf("%s \n", result);
  return 0;
}
