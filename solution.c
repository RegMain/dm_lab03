#include "solution.h"
#include "vec_int.h"
#include "vec_byte.h"
#include "math.h"
#include <stdint.h>
#include <stdlib.h>

vec_int *Eratosphene(int32_t n) {
  vec_byte *vec = vec_byte_init(n + 1, 1);
  if (!vec) {
    return NULL;
  }
  for (int64_t i = 2; i*i <= n; ++i) {
    int8_t *vec_i = vec_byte_get(vec, i);
    if (vec_i && *vec_i) {
      for (int64_t j = i*i; j <= n; j += i) {
        vec_byte_set(vec, j, 0);
      }
    }
  }
  vec_int *res = vec_int_init(0,0);
  for (int32_t i = 2; i <= n; ++i) {
    int8_t *vec_i = vec_byte_get(vec, i);
    if (vec_i && *vec_i) {
      vec_int_push(res, i);
    }
  }
  vec_byte_destroy(vec);
  return res;
}

double dzeta_def(double s, double eps) {
  if (s <= 1.0) {
    return -1.0;
  }
  double res = 0.0;
  double k = 1.0;
  double n = round(pow(1/(eps * (s - 1)), 1/(s - 1))) + 1.0;
  while (k <= n) {
    res += pow(k, -s);
    ++k;
  }
  return res;
}

double dzeta_Euler(double s, vec_int *primes, double eps) {
  if (s <= 1.0) {
    return -1.0;
  }
  if (!primes) {
      return -1.0;
  }
  double res = 1.0;
  for (int32_t i = 0; i < vec_int_get_size(primes); ++i) {
    int32_t *x = vec_int_get(primes, i);
    if (x) {
      res *= 1.0 / (1.0 - 1.0/pow(*x, s));
    }
  }
  return res;
}
