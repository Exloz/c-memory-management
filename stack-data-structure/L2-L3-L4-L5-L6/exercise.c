#include "snekstack.h"
#include <stdlib.h>
#include <string.h>

void scary_double_push(stack_t *s) {
  stack_push(s, (void *)1337);
  int *new_int = malloc(sizeof(int));
  *new_int = 1024;
  stack_push(s, (void *)new_int);
}

void stack_push_multiple_types(stack_t *s){
  float *float_ptr = malloc(sizeof(float));
  *float_ptr = 3.14;

  stack_push(s, (void *)float_ptr);

  char *string_original = "Sneklang is blazingly slow!";
  size_t len = strlen(string_original) + 1;
  char *string_ptr = malloc(len * sizeof(char));
  strcpy(string_ptr, string_original);

  stack_push(s, (void *)string_ptr);


}
