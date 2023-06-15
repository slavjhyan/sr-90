#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include "stdbool.h"

typedef struct _dynamicArray {
    int* _ptr;
    int _size;
    int _cap;
} DynamicArray;

void __checkPointerValidity(const void* p);

void __checkBounds(int ix, int size);

void __checkArrayBounds(const DynamicArray* darr, int ix);

void __shiftLeft(DynamicArray* darr, int startIx, int count);

void defaultInitArray(DynamicArray* darr);

void initArray(DynamicArray* darr, int* ptr, int size, int cap); // not tested

bool empty(const DynamicArray* darr);

int size(const DynamicArray* darr);

int capacity(const DynamicArray* darr);

void clear(DynamicArray* darr); // not tested

void pushBack(DynamicArray* darr, int elem);

void insert(DynamicArray* darr, int pos, int elem);

void removeIndex(DynamicArray* darr, int pos);

int* at(DynamicArray* darr, int ix);

void copy(DynamicArray* src, DynamicArray* dest); // not tested

bool equals(DynamicArray* lhs, DynamicArray* rhs); // not tested

void reallocate(DynamicArray* darr, int newCap);

void freeArray(DynamicArray* darr);

#endif /* DYNAMIC_ARRAY_H */
