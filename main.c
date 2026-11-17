#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "solution.h"
#include "functions.h"

int main(void) {
  int opcode;
  printf("Input number of task (48 or 49): ");
  if (scanf("%d", &opcode) == 1) {
      if (opcode == 48) {
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
      } else if (opcode == 49) {
          int32_t x, result;
          int32_t size = 10000000;
          printf("Input natural x: ");
          scanf("%d", &x);
          vec_int *sieve_res = NULL;
          printf("Euler(x): ");
          if (sieve(size, &sieve_res, Euler) || sieve_compute(sieve_res, x, &result)) {
              printf("Error!\n");
          } else {
              printf("%d\n", result);
          }
          vec_int_destroy(sieve_res);
          printf("Moebius(x): ");
          if (sieve(size, &sieve_res, Moebius) || sieve_compute(sieve_res, x, &result)) {
              printf("Error!\n");
          } else {
              printf("%d\n", result);
          }
          vec_int_destroy(sieve_res);
          printf("Count of divisors: ");
          if (sieve(size, &sieve_res, divisors_cnt) || sieve_compute(sieve_res, x, &result)) {
              printf("Error!\n");
          } else {
              printf("%d\n", result);
          }
          vec_int_destroy(sieve_res);
      }
  }
}
