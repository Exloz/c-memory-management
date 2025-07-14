
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "snekobject.h"

snek_object_t *new_snek_float(float value){
  snek_object_t *ptr_obj_float = malloc(sizeof(snek_object_t));
  if (ptr_obj_float==NULL) return NULL;

  ptr_obj_float->kind = FLOAT;
  ptr_obj_float->data.v_float = value;

  return ptr_obj_float;
}

snek_object_t *new_snek_integer(int value){
  snek_object_t *ptr_obj = malloc(sizeof(snek_object_t));
  if (ptr_obj==NULL) return NULL;

  ptr_obj->kind = INTEGER;
  ptr_obj->data.v_int = value;

  return ptr_obj;
}

snek_object_t *new_snek_string(char *value){
  snek_object_t *ptr_obj = malloc(sizeof(snek_object_t));
  if(ptr_obj==NULL) return NULL;
  
  int string_length = strlen(value);
  char *ptr_string = malloc((string_length + 1)*sizeof(char));
  if(ptr_string==NULL) {
    free(ptr_obj);
    return NULL; 
  } 
  strcpy(ptr_string, value);
  
  ptr_obj->kind = STRING;
  ptr_obj->data.v_string = ptr_string;
  
  return ptr_obj;
}

snek_object_t *new_snek_vector3(snek_object_t *x, snek_object_t *y, snek_object_t *z){
  if (x == NULL || y == NULL || z == NULL) {
    return NULL;
  }
  
  snek_object_t *object_ptr = malloc(sizeof(snek_object_t));
  if (object_ptr==NULL) return NULL;

  object_ptr->kind = VECTOR3;
  snek_vector_t vector3 = {x,y,z};
  object_ptr->data.v_vector3 = vector3;

  return object_ptr;
}

snek_object_t *new_snek_array(size_t size){
  snek_object_t *object_ptr = malloc(sizeof(snek_object_t));
  if (object_ptr == NULL) return NULL;

  snek_object_t **array_ptr = calloc(size, sizeof(snek_object_t *));

  object_ptr->kind = ARRAY;
  object_ptr->data.v_array.size = size;
  object_ptr->data.v_array.elements = array_ptr;

  return object_ptr;
}
