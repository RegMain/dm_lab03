#pragma once
#include <stdint.h>

typedef struct {
  int32_t capacity;
  int32_t size;
  int8_t *ptr;
} vec_byte;

vec_byte *vec_byte_init(int32_t size, int8_t value);

int vec_byte_destroy(vec_byte *vec);

int vec_byte_set_size(vec_byte *vec, int32_t size);

int32_t vec_byte_get_size(vec_byte *vec);

int vec_byte_set(vec_byte *vec, int32_t index, int8_t value);

int8_t *vec_byte_get(vec_byte *vec, int32_t index);

int vec_byte_push(vec_byte *vec, int8_t value);
