#pragma once
#include <stdint.h>

typedef struct {
  int32_t capacity;
  int32_t size;
  int *ptr;
} vec_int;

vec_int *vec_int_init(int32_t size, int32_t value);

int vec_int_destroy(vec_int *vec);

int vec_int_set_size(vec_int *vec, int32_t size);

int32_t vec_int_get_size(vec_int *vec);

int vec_int_set(vec_int *vec, int32_t index, int32_t value);

int32_t *vec_int_get(vec_int *vec, int32_t index);

int vec_int_push(vec_int *vec, int32_t value);
