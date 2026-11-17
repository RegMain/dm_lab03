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

int sieve(uint32_t n, vec_int **result, int32_t (*f)(int32_t x, int32_t k)) {
    if (!result) {
        return 1;
    }
    *result = vec_int_init(n + 1, 0);
    if (!*result) {
        return 2;
    }
    vec_int *primes = Eratosphene(n);
    if (!primes) {
        return 3;
    }
    for (uint32_t i = 0; i < vec_int_get_size(primes); ++i) {
        int32_t prime;
        if (!vec_int_get(primes, i, &prime)) {
            int32_t s = 1;
            for (int64_t j = prime; j <= n; j *= prime) {
                vec_int_set(*result, j, f(j, s));
                ++s;
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
    if (x > 1) {
        vec_int_push(*result, x);
    }
    return 0;
}

int sieve_compute(vec_int *sieve, int32_t x, int32_t *value) {
    if (!sieve) {
        return 1;
    }
    vec_int *divs;
    factorize(x, &divs);
    double result = 1.0;
    for (uint32_t i = 0; i < vec_int_get_size(divs); ++i) {
        int32_t div;
        if (!vec_int_get(divs, i, &div)) {
            int32_t div_value;
            if (!vec_int_get(sieve, div, &div_value)) {
                result *= div_value;
            } else {
                vec_int_destroy(divs);
                return 3;
            }
        } else {
            vec_int_destroy(divs);
            return 2;
        }
    }
    *value = result;
    vec_int_destroy(divs);
    return 0;
}
