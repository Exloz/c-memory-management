#include "snekstack.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

void stack_free(stack_t *stack) {
  if(stack == NULL){
    return;
  }
  if(stack->data != NULL){
    free(stack->data);
  }
  free(stack);
}

void *stack_pop(stack_t *stack) {
  if(stack->count == 0) {
    return NULL;
  }
  stack->count--;
  return stack->data[stack->count];
} 

void stack_push(stack_t *stack, void *obj) {

  if (stack->count == stack->capacity) {
    size_t original_capacity = stack->capacity;
    stack->capacity = stack->capacity * 2;
    int *new_stack = realloc(stack->data, stack->capacity * sizeof(void *));
    if (new_stack == NULL) { 
      stack->capacity = original_capacity;
      return;
    }
  }
  stack->data[stack->count] = obj;
  stack->count++; 
}

stack_t *stack_new(size_t capacity) {
  stack_t *stack = malloc(sizeof(stack_t));
  if (stack == NULL) {
    return NULL;
  }

  stack->count = 0;
  stack->capacity = capacity;
  stack->data = malloc(stack->capacity * sizeof(void *));
  if (stack->data == NULL) {
    free(stack);
    return NULL;
  }

  return stack;
}

