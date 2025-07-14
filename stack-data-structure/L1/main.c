#include "snekstack.h"
#include <stdlib.h>

stack_t *stack_new(size_t capacity) {

  stack_t *stack_ptr = malloc(sizeof(stack_t));
  if (stack_ptr==NULL) {
    return NULL;
  }
  stack_ptr->count = 0;
  stack_ptr->capacity = capacity;
  stack_ptr->data = malloc(capacity * sizeof(void *));
  if (stack_ptr->data == NULL) {
    free(stack_ptr);
    return NULL;
  }

  return stack_ptr;
}

