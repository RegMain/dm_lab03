#include "functions.h"
#include <stdint.h>

int32_t divisors_cnt(int32_t n, int32_t k) {
  return k + 1;
}

int32_t Euler(int32_t n, int32_t k) {
  int32_t res = 1;
  for (int32_t i = 1; i < k; ++i) {
    res *= n;
  }
  return res * (n - 1);
}

int32_t Moebius(int32_t n, int32_t k) {
    if (k == 0) {
        return 1;
    } else if (k == 1) {
        return -1;
    }
    return 0;
}
