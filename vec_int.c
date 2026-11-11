#include "vec_int.h"
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

vec_int *vec_int_init(int32_t size, int32_t value) {
  vec_int *vec = (vec_int *)malloc(sizeof(vec_int));
  if (!vec) {
    return NULL;
  }
  vec->size = size;
  if (size == 0) {
    vec->capacity = 1;
  } else {
    vec->capacity = size;
  }
  vec->ptr = (int32_t *)malloc(sizeof(int32_t) * vec->capacity);
  if (!vec->ptr) {
    free(vec);
    return NULL;
  }
  for (int32_t i = 0; i < vec->capacity; ++i) {
    vec->ptr[i] = value;
  }
  return vec;
}

int vec_int_destroy(vec_int *vec) {
  if (!vec) {
    return -1;
  }
  if (!vec->ptr) {
    free(vec);
    return 0;
  }
  free(vec->ptr);
  free(vec);
  return 0;
}

int vec_int_set_size(vec_int *vec, int32_t size) {
  if (!vec || size < 0) {
    return -1;
  }
  if (size < vec->capacity) {
    vec->size = size;
    return 0;
  }
  int32_t *tmp = (int32_t *)realloc(vec->ptr, sizeof(int32_t) * size);
  if (!tmp) {
    return -1;
  }
  vec->ptr = tmp;
  for (int32_t i = vec->size; i < size; ++i) {
    vec->ptr[i] = 0;
  }
  vec->size = size;
  vec->capacity = size;
  return 0;
}

int32_t vec_int_get_size(vec_int *vec) {
  if (!vec) {
    return 0;
  }
  return vec->size;
}

int vec_int_set(vec_int *vec, int32_t index, int32_t value) {
  if (!vec || !vec->ptr || index < 0 || index >= vec->size) {
    return -1;
  }
  vec->ptr[index] = value;
  return 0;
}

int32_t *vec_int_get(vec_int *vec, int32_t index) {
  if (!vec || !vec->ptr || index < 0 || index >= vec->size) {
    return NULL;
  }
  return &vec->ptr[index];
}

int vec_int_push(vec_int *vec, int32_t value) {
  if (!vec || !vec->ptr) {
    return -1;
  }
  if (vec->capacity > vec->size) {
    if  (vec_int_set_size(vec, vec->size + 1) || vec_int_set(vec, vec->size - 1, value)) {
      return -1;
    }
    return 0;
  }
  int32_t *tmp = (int32_t *)realloc(vec->ptr, 2 * sizeof(int32_t) * vec->capacity);
  if (!tmp) {
    return -1;
  }
  vec->ptr = tmp;
  vec->ptr[vec->size] = value;
  for (int32_t i = vec->size + 1; i < 2 * vec->capacity; ++i) {
    vec->ptr[i] = 0;
  }
  ++vec->size;
  vec->capacity = 2 * vec->capacity;
  return 0;
} 
