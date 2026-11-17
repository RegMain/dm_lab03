#pragma once
#include <stdint.h>

typedef struct {
  int32_t capacity;
  int32_t size;
  double *ptr;
} vec_double;

vec_double *vec_double_init(int32_t size, double value);

int vec_double_destroy(vec_double *vec);

int vec_double_set_size(vec_double *vec, int32_t size);

int32_t vec_double_get_size(vec_double *vec);

int vec_double_set(vec_double *vec, int32_t index, double value);

int vec_double_get(vec_double *vec, int32_t index, double *value);

int vec_double_push_back(vec_double *vec, double value);
