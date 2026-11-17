#include "solution.h"
#include "vec_int.h"
#include "vec_byte.h"
#include "vec_double.h"
#include "math.h"
#include <stdint.h>
#include <stdlib.h>

vec_int *Eratosphene(int32_t n) {
  vec_byte *vec = vec_byte_init(n + 1, 1);
  if (!vec) {
    return NULL;
  }
  for (int64_t i = 2; i*i <= n; ++i) {
    int8_t vec_i;
    if (!vec_byte_get(vec, i, &vec_i) && vec_i) {
      for (int64_t j = i*i; j <= n; j += i) {
        vec_byte_set(vec, j, 0);
      }
    }
  }
  vec_int *res = vec_int_init(0,0);
  for (int32_t i = 2; i <= n; ++i) {
    int8_t vec_i;
    if (!vec_byte_get(vec, i, &vec_i) && vec_i) {
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
    int32_t x;
    if (!vec_int_get(primes, i, &x)) {
      res *= 1.0 / (1.0 - 1.0/pow(x, s));
    }
  }
  return res;
}

int sieve(uint32_t n, vec_double **result, double (*f)(int32_t x)) {
    if (!result) {
        return 1;
    }
    *result = vec_double_init(n + 1, 0);
    if (!*result) {
        return 2;
    }
    vec_int *primes = Eratosphene(n);
    if (!primes) {
        return 3;
    }
    for (uint32_t i = 0; i < n + 1; ++i) {
        int32_t prime;
        if (!vec_int_get(primes, i, &prime)) {
            double f_value = f(prime);
            vec_double_set(*result, prime, f_value);
            int32_t prev = prime;
            for (int32_t j = prime * prime; j < n; j *= prime) {
                vec_double_set(*result, j, prev * f_value);
                prev = j;
            }
        } else {
            vec_int_destroy(primes);
            return 4;
        }
    }
    vec_int_destroy(primes);
    return 0;
}

int factorize(int32_t x, vec_int **result) {
    if (!result) {
        return 1;
    }
    *result = vec_int_init(0, 0);
    if (!*result) {
        return 2;
    }
    for (int i = 2; i*i <= x; ++i) {
        if (x % i == 0) {
            int32_t div = 1;
            while (x % i == 0) {
                x /= i;
                div *= i;
            }
            if (vec_int_push(*result, div)) {
                return 3;
            }
        }
    }
    return 0;
}

int sieve_compute(vec_double *sieve, int32_t x, double *value) {
    if (!sieve) {
        return 1;
    }
    vec_int *divs;
    factorize(x, &divs);
    double result = 1.0;
    for (uint32_t i = 0; i < vec_int_get_size(divs); ++i) {
        int32_t div;
        if (!vec_int_get(divs, i, &div)) {
            double div_value;
            if (!vec_double_get(sieve, div, &div_value)) {
                result *= div_value;
            } else {
                free(divs);
                return 3;
            }
        } else {
            free(divs);
            return 2;
        }
    }
    *value = result;
    free(divs);
    return 0;
}
