#include "dynamic_array_iterator.h"

#include "stddef.h"

void defaultInitArrayIter(ArrayIterator* it) {
    __checkPointerValidity(it);

    it->_p = NULL;
    it->_darr = NULL;
}

void bindTo(ArrayIterator* it, DynamicArray* darr) {
    __checkPointerValidity(it);
    __checkPointerValidity(darr);

    it->_p = darr->_ptr;
    it->_darr = darr;
}

int next(ArrayIterator* it) {
    __checkPointerValidity(it);

    int val = *it->_p;
    ++(it->_p);

    return val;
}

void reset(ArrayIterator* it) {
    __checkPointerValidity(it);
    __checkPointerValidity(it->_darr);
    __checkPointerValidity(it->_darr->_ptr);

    it->_p = it->_darr->_ptr;
}
