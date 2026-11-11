#pragma once
#include "vec_int.h"
#include <stdint.h>

vec_int *Eratosphene(int32_t n);

double dzeta_def(double s, int32_t n);

double dzeta_Euler(double s, vec_int *primes);
