#include <stdio.h>
#include <stdint.h>
#include "solution.h"

int main(void) {
  double eps, s;
  int32_t n, m;
  printf("Input s, max number for definition sum and max available prime number: ");
  scanf("%lf %d %d", &s, &m, &n);
  printf("\nDzeta(s) via definition: %.16lf\n", dzeta_def(s, m));
  vec_int *primes = Eratosphene(n);
  printf("Dzeta(s) via Euler's multiplication: %.16lf\n", dzeta_Euler(s, primes));
  vec_int_destroy(primes);
  return 0;
}
