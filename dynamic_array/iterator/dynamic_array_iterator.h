#ifndef DYNAMIC_ARRAY_ITERATOR_H
#define DYNAMIC_ARRAY_ITERATOR_H

#include "../dynamic_array.h"

typedef struct _dynamicArrayIterator {
    int* _p;
    DynamicArray* _darr;
} ArrayIterator;

void defaultInitArrayIter(ArrayIterator* it);

void bindTo(ArrayIterator* it, DynamicArray* darr);

int next(ArrayIterator* it);

void reset(ArrayIterator* it);

#endif /* DYNAMIC_ARRAY_ITERATOR_H */
