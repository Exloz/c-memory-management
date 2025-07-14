#include <stdlib.h>
void allocate_int(int **pointer_pointer, int value){

  int *integer = malloc(sizeof(int));
  *integer = value;

  *pointer_pointer = integer;

}
