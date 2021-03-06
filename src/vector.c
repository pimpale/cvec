#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

#define FATAL(x)                                                               \
  do {                                                                         \
    fprintf(stderr, x);                                                        \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

// The initial capacity of the vector
#define INITIAL_CAPACITY 1
// The percent it will increase when out of room MUST BE POSITIVE
// Ex. 1.5 -> 50% expansion each time the limit is hit

void setSizeVector(Vector *vector, size_t size);
void resizeVector(Vector *vector, size_t size);

/* Sets the size of the vector */
void setSizeVector(Vector *vector, size_t size) {
  vector->data = realloc(vector->data, size);
  vector->capacity = size;
}

/* Resizes the vector in order to fit an element of this size in */
void resizeVector(Vector *vector, size_t size) {
  /* This is the new size of the vector if we used the loadFactor */
  size_t newCapacity = (size_t)((vector->length + size) * vector->loadFactor);
  setSizeVector(vector, newCapacity);
}

void initVector(Vector *vector) {
  vector->data = NULL;
  vector->length = 0;
  vector->capacity = 0;
  vector->loadFactor = 1.5f;
  resizeVector(vector, INITIAL_CAPACITY);
}

void freeVector(Vector *vector) {
  free(vector->data);
  vector->data = NULL;
}

void *pushVector(Vector *vector, size_t len) {
  return insertVector(vector, vector->length, len);
}

void popVector(Vector *vector, void *data, size_t len) {
  if (len > vector->length) {
    FATAL("vector underflow");
  }
  if(data != NULL) {
    memmove(data, (uint8_t *)vector->data + vector->length - len, len);
  }
  removeVector(vector, vector->length - len, len);
}

// Insert a segment of empty data of len length at the specified position loc
void *insertVector(Vector *vector, size_t loc, size_t len) {
  if (vector->length + len >= vector->capacity) {
    resizeVector(vector, len);
  }
  vector->length += len;
  uint8_t *src = getVector(vector, loc);
  uint8_t *dest = getVector(vector, loc + len);
  // Move memory from end of allocation back
  memmove(dest, src, vector->length - (loc + len));
  // Zero out new memory
  memset(src, 0, len);
  return src;
}

void removeVector(Vector *vector, size_t loc, size_t len) {
  if (len > vector->length - loc) {
    FATAL("vector underflow");
  }

  uint8_t *src = getVector(vector, loc + len);
  uint8_t *dest = getVector(vector, loc);

  vector->length -= len;
  memmove(dest, src, vector->length - loc);
}

void *getVector(Vector *vector, size_t loc) {
  if (loc > vector->length) {
    FATAL("vector out of bounds");
  }
  uint8_t *data = vector->data;
  return data + loc;
}

size_t lengthVector(Vector *vector) { return vector->length; }

float getLoadFactorVector(Vector *vector) { return vector->loadFactor; }

void setLoadFactorVector(Vector *vector, float loadFactor) {
  vector->loadFactor = loadFactor;
  return;
}
