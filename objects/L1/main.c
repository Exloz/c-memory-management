
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <time.h>
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
  if( array_ptr == NULL) {
    free(object_ptr);
    return NULL; 
  }

  object_ptr->kind = ARRAY;
  object_ptr->data.v_array.size = size;
  object_ptr->data.v_array.elements = array_ptr;

  return object_ptr;
}

bool snek_array_set(snek_object_t *snek_obj, size_t index, snek_object_t *value){
  if(value == NULL || snek_obj == NULL) return false;
  if(snek_obj->kind != ARRAY) return false;
  if(index >= snek_obj->data.v_array.size) return false;
  snek_obj->data.v_array.elements[index] = value;

  return true;
}

snek_object_t *snek_array_get(snek_object_t *snek_obj, size_t index){
  if(snek_obj == NULL) return false;
  if(snek_obj->kind != ARRAY) return false;
  if(index >= snek_obj->data.v_array.size) return false;
  return snek_obj->data.v_array.elements[index];
}

int snek_length(snek_object_t *obj){
  if(obj == NULL) return -1;
  if(obj->kind == INTEGER) return 1;
  if(obj->kind == FLOAT) return 1;
  if(obj->kind == STRING) return strlen(obj->data.v_string);
  if(obj->kind == VECTOR3) return 3;
  if(obj->kind == ARRAY) return obj->data.v_array.size;
  return -1;
}

snek_object_t *snek_add(snek_object_t *a, snek_object_t *b){ 
  if(a == NULL || b == NULL) return NULL;

  switch (a->kind) {
    case INTEGER:
      if(b->kind == INTEGER) return new_snek_integer(a->data.v_int + b->data.v_int);
      if(b->kind == FLOAT) return new_snek_float(a->data.v_int + b->data.v_float);
      return NULL;
    case FLOAT:
      if(b->kind == INTEGER) return new_snek_float(a->data.v_float + b->data.v_int);
      if(b->kind == FLOAT) return new_snek_float(a->data.v_float + b->data.v_float);
      return NULL;
    case STRING:
      if(b->kind != STRING) return NULL;

      int total_length = snek_length(a) + snek_length(b) + 1;
      char *temp_str_ptr = calloc(total_length, sizeof(char));

      strcat(temp_str_ptr, a->data.v_string);
      strcat(temp_str_ptr, b->data.v_string);
      snek_object_t *new_object = new_snek_string(temp_str_ptr);

      free(temp_str_ptr);
      return new_object;
    case VECTOR3:
      if(b->kind != VECTOR3) return NULL;
      return new_snek_vector3(snek_add(a, b), snek_add(a, b), snek_add(a, b));
    case ARRAY:
      if(b->kind != ARRAY) return NULL;
      snek_object_t *new_array = new_snek_array(a->data.v_array.size + b->data.v_array.size);

      for (int i = 0; i < snek_length(a); i++) {
        snek_array_set(new_array, i, snek_array_get(a, i));
      }
      for (int i = 0, j = snek_length(a) - 1; i < snek_length(b); i++, j++) {
        snek_array_set(new_array, j, snek_array_get(a, i));
      }
      return new_array;
    default:
      return NULL;
  }
}
