#include "dynamic_array.h"

#include "stdio.h"
#include "stdlib.h"

// TODO: Move private methods to the end of the file and declare them in header file

void __checkPointerValidity(const void* p) {
    if (p == NULL) {
        perror("NULL pointer passed\n");
        exit(1);
    }
}

void __checkBounds(int ix, int size) {
    if (ix < 0 || ix >= size) {
        perror("Index out of bounds\n");
        exit(1);
    }
}

void __checkArrayBounds(const DynamicArray* darr, int ix) {
    __checkPointerValidity(darr);
    __checkBounds(ix, size(darr));
}

void __changeCapacity(DynamicArray* darr, int newCap) {
    __checkPointerValidity(darr);
    if (newCap <= darr->_cap) {
        return;
    }

    int* tmp = malloc(newCap * sizeof(int));
    for (int i = 0; i < darr->_size; ++i) {
        tmp[i] = darr->_ptr[i];
    }
    free(darr->_ptr);

    darr->_ptr = tmp;
    darr->_cap = newCap;
}

void __ensureCapacityForNewElements(DynamicArray* darr, int elemCount) {
    __checkPointerValidity(darr);
    if (darr->_size + elemCount >= darr->_cap) {
        __changeCapacity(darr, 2 * darr->_cap + 1);
    }
}

void __shiftRight(DynamicArray* darr, int startIx, int count) {
    __checkPointerValidity(darr);
    __checkArrayBounds(darr, startIx + count);

    for (int i = darr->_size - 1; i > startIx ; --i) {
        darr->_ptr[i] = darr->_ptr[i - count];
    }
}

void __shiftLeft(DynamicArray* darr, int startIx, int count) {
    __checkPointerValidity(darr);
    __checkArrayBounds(darr, startIx + count);

    for (int i = startIx; i < darr->_size - count; ++i) {
        darr->_ptr[i] = darr->_ptr[i + count];
    }
}

void __removeStartingFrom(DynamicArray* darr, int startIx, int count) {
    __checkPointerValidity(darr);
    __checkArrayBounds(darr, startIx + count);

    __shiftLeft(darr, startIx, count);
    darr->_size -= count;
}

int* __ptrDeepCopy(DynamicArray* darr) {
    __checkPointerValidity(darr);
    __checkPointerValidity(darr->_ptr);

    int* tmp = (int*)malloc(darr->_cap * sizeof(int));
    for (int i = 0; i < darr->_size; ++i) {
        tmp[i] = darr->_ptr[i];
    }

    return tmp;
}

void defaultInitArray(DynamicArray* darr) {
    __checkPointerValidity(darr);
    darr->_ptr = NULL;
    darr->_size = 0;
    darr->_cap = 0;
}

void initArray(DynamicArray* darr, int* ptr, int size, int cap) {
    __checkPointerValidity(darr);

    if(size < 0 || cap < 0) {
        perror("Cannot initialize a dynamic array with size and/or capacity values less than 0\n");
        return;
    }

    if (size > cap) {
        perror("Cannot initialize a dynamic array with size greater than capacity\n");
        return;
    }

    darr->_ptr = ptr;
    darr->_size = size;
    darr->_cap = cap;
}

bool empty(const DynamicArray* darr) {
    __checkPointerValidity(darr);
    return !darr->_size;
}

int size(const DynamicArray* darr) {
    __checkPointerValidity(darr);
    return darr->_size;
}

int capacity(const DynamicArray* darr) {
    __checkPointerValidity(darr);
    return darr->_cap;
}

void clear(DynamicArray* darr) {
    __checkPointerValidity(darr);
    free(darr->_ptr);
    defaultInitArray(darr);
}

void pushBack(DynamicArray* darr, int elem) {
    __checkPointerValidity(darr);
    __ensureCapacityForNewElements(darr, 1);

    darr->_ptr[darr->_size] = elem;
    ++(darr->_size);
}

void insert(DynamicArray* darr, int pos, int elem) {
    __checkPointerValidity(darr);
    __checkArrayBounds(darr, pos);

    if (pos >= darr->_size || pos < 0) {
        perror("Invalid index");
        exit(1);
    }
    __ensureCapacityForNewElements(darr, 1);

    ++darr->_size;
    __shiftRight(darr, pos, 1);
    darr->_ptr[pos] = elem; 
}

void removeIndex(DynamicArray* darr, int pos) {
    __checkPointerValidity(darr);
    __checkArrayBounds(darr, pos);
    __removeStartingFrom(darr, pos, 1);
}

int* at(DynamicArray* darr, int ix) {
    __checkPointerValidity(darr);
    __checkArrayBounds(darr, ix);

    return darr->_ptr + ix;
}

// const int* at(const DynamicArray* darr, int ix) {
//     __checkPointerValidity(darr);
//     __checkArrayBounds(darr, ix);

//     return darr->_ptr + ix;
// }

void copy(DynamicArray* src, DynamicArray* dest) {
    __checkPointerValidity(src);

    if (dest != NULL) {
        free(dest->_ptr);
    }

    dest->_ptr = __ptrDeepCopy(src);
    dest->_cap = src->_cap;
    dest->_size = src->_size;
}

bool equals(DynamicArray* lhs, DynamicArray* rhs) {
    __checkPointerValidity(lhs);
    __checkPointerValidity(rhs);

    bool equal = true;
    if (lhs->_size != rhs->_size) {
        equal = false;
    } else {
        for (int i = 0; i < lhs->_size; ++i) {
            if (*at(lhs, i) != *at(rhs, i)) {
                equal = false;
                break;
            }
        }
    }

    return equal;
}

void reallocate(DynamicArray* darr, int newCap) {
    __checkPointerValidity(darr);
    return __changeCapacity(darr, newCap);
}

void freeArray(DynamicArray* darr) {
    __checkPointerValidity(darr);
    free(darr->_ptr);
    free(darr);
}
