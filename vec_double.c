#include "vec_double.h"
#include <stdint.h>
#include <stdlib.h>

vec_double *vec_double_init(int32_t size, double value) {
  if (size < 0) {
    return NULL;
  }
  vec_double *vec = (vec_double *)malloc(sizeof(vec_double));
  if (!vec) {
    return NULL;
  }
  vec->size = size;
  if (size == 0) {
    vec->capacity = 8;
  } else {
    vec->capacity = size;
  }
  vec->ptr = (double *)malloc(sizeof(double) * vec->capacity);
  if (!vec->ptr) {
    free(vec);
    return NULL;
  }
  for (int32_t i = 0; i < vec->capacity; ++i) {
    vec->ptr[i] = value;
  }
  return vec;
}

int vec_double_destroy(vec_double *vec) {
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

int vec_double_set_size(vec_double *vec, int32_t size) {
  if (!vec || size < 0) {
    return -1;
  }
  if (size <= vec->capacity) {
    vec->size = size;
    return 0;
  }
  double *tmp = (double *)realloc(vec->ptr, sizeof(double) * size);
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

int32_t vec_double_get_size(vec_double *vec) {
  if (!vec) {
    return 0;
  }
  return vec->size;
}

int vec_double_set(vec_double *vec, int32_t index, double value) {
  if (!vec || !vec->ptr || index < 0 || index >= vec->size) {
    return -1;
  }
  vec->ptr[index] = value;
  return 0;
}

int vec_double_get(vec_double *vec, int32_t index, double *value) {
  if (!vec || !vec->ptr || index < 0 || index >= vec->size) {
    return 1;
  }
  *value = vec->ptr[index];
  return 0;
}

int vec_double_push_back(vec_double *vec, double value) {
  if (!vec || !vec->ptr) {
    return -1;
  }
  if (vec->capacity > vec->size) {
    if  (vec_double_set_size(vec, vec->size + 1) || vec_double_set(vec, vec->size - 1, value)) {
      return -1;
    }
    return 0;
  }
  double *tmp = (double *)realloc(vec->ptr, 2 * sizeof(double) * vec->capacity);
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
