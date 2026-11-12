#include "vec_byte.h"
#include <stdint.h>
#include <stdlib.h>

vec_byte *vec_byte_init(int32_t size, int8_t value) {
  vec_byte *vec = (vec_byte *)malloc(sizeof(vec_byte));
  if (!vec || size < 0) {
    return NULL;
  }
  vec->size = size;
  if (size == 0) {
    vec->capacity = 8;
  } else {
    vec->capacity = size;
  }
  vec->ptr = (int8_t *)malloc(vec->capacity);
  if (!vec->ptr) {
    free(vec);
    return NULL;
  }
  for (int32_t i = 0; i < vec->capacity; ++i) {
    vec->ptr[i] = value;
  }
  return vec;
}

int vec_byte_destroy(vec_byte *vec) {
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

int vec_byte_set_size(vec_byte *vec, int32_t size) {
  if (!vec || size < 0) {
    return -1;
  }
  if (size <= vec->capacity) {
    vec->size = size;
    return 0;
  }
  int8_t *tmp = (int8_t *)realloc(vec->ptr, size);
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

int32_t vec_byte_get_size(vec_byte *vec) {
  if (!vec) {
    return 0;
  }
  return vec->size;
}

int vec_byte_set(vec_byte *vec, int32_t index, int8_t value) {
  if (!vec || !vec->ptr || index < 0 || index >= vec->size) {
    return -1;
  }
  vec->ptr[index] = value;
  return 0;
}

int8_t *vec_byte_get(vec_byte *vec, int32_t index) {
  if (!vec || !vec->ptr || index < 0 || index >= vec->size) {
    return NULL;
  }
  return &vec->ptr[index];
}

int vec_byte_push(vec_byte *vec, int8_t value) {
  if (!vec || !vec->ptr) {
    return -1;
  }
  if (vec->capacity > vec->size) {
    if  (vec_byte_set_size(vec, vec->size + 1) || vec_byte_set(vec, vec->size - 1, value)) {
      return -1;
    }
    return 0;
  }
  int8_t *tmp = (int8_t *)realloc(vec->ptr, 2 * vec->capacity);
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
