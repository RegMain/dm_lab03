#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "solution.h"

int main(void) {
  double eps, s;
  printf("Input s and eps: ");
  scanf("%lf %lf", &s, &eps);
  printf("\nDzeta(s) via definition: %.16lf\n", dzeta_def(s, eps));
  vec_int *primes;
  if (eps >= 1e-9) {
      double A = s / ((s - 1) * (s - 1) * eps);
      primes = Eratosphene((int32_t)round((s - 1)*pow(A, 1/(s - 1))/log(A)));
  } else {
      primes = Eratosphene(INT32_MAX - 1);
  }
  printf("Dzeta(s) via Euler's multiplication: %.16lf\n", dzeta_Euler(s, primes, eps));
  vec_int_destroy(primes);
  return 0;
}
