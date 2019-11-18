#include <stdio.h>

#include "vector.h"

/* This entire file is solely for testing */
int main() {

  Vector v;
  initVector(&v);

  for (uint32_t i = 0; i < 100; i++) {
    *VEC_PUSH(&v, uint32_t) = i;
  }

  for (uint32_t i = 0; i < 100; i++) {
    printf(" %zu\n", lengthVector(&v));
    VEC_REM(&v, 0, uint32_t);
  }

  freeVector(&v);
}

