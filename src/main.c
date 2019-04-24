#include "vector.h"

/* This entire file is solely for testing */
int main() {

  Vector v;
  initVector(&v);

  for (uint32_t i = 0; i < 100; i++) {
    *VEC_PUSH(&v, uint32_t) = i;
  }

  VEC_REM(&v, 5, uint32_t);

  freeVector(&v);
}
