#pragma once
#include "vec_int.h"
#include <stdint.h>

vec_int *Eratosphene(int32_t n);

double dzeta_def(double s, double eps);

double dzeta_Euler(double s, vec_int *primes, double eps);

int sieve(uint32_t n, vec_int **result, int32_t (*f)(int32_t x, int32_t k));

int factorize(int32_t x, vec_int **result);

int sieve_compute(vec_int *sieve, int32_t x, int32_t *value);
