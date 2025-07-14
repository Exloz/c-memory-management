#include <stddef.h>
#include <stdlib.h>

#include "exercise.h"

token_t** create_token_pointer_array(token_t* tokens, size_t count) {
  token_t** token_pointers = malloc(count * sizeof(token_t*));
  if (token_pointers == NULL) {
    exit(1);
  }
  for (size_t i = 0; i < count; ++i) {
    token_t* heap_token_ptr = malloc(sizeof(token_t));
    *heap_token_ptr = tokens[i];

    token_pointers[i] = heap_token_ptr;
  }
  return token_pointers;
}
