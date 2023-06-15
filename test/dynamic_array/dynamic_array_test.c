#include "dynamic_array_test.h"

#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

#include "../../dynamic_array/dynamic_array.h"

void executeAllDynamicArrayTests() {
    __testArrayInit();
    __testArrayPublicInterface();
    printf("\033[0;34m");
    printf("\n\tArray Tests Have Passed\n");
    printf("\033[0m");
}

void __testArrayInit() {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    defaultInitArray(arr);

    assert(arr->_ptr == NULL);
    assert(arr->_size == 0);
    assert(arr->_cap == 0);

    freeArray(arr);

    printf("\nArrayInit passed.\n");
}

void __testArrayPublicInterface() {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    defaultInitArray(arr);

    assert(empty(arr));
    assert(size(arr) == 0);
    assert(capacity(arr) == 0);

    pushBack(arr, 10);
    assert(!empty(arr));
    assert(size(arr) == 1);
    assert(*at(arr, 0) == 10);

    pushBack(arr, 20);
    assert(!empty(arr));
    assert(size(arr) == 2);
    assert(*at(arr, 0) == 10);
    assert(*at(arr, 1) == 20);

    insert(arr, 1, 15);
    assert(!empty(arr));
    assert(size(arr) == 3);
    assert(*at(arr, 0) == 10);
    assert(*at(arr, 1) == 15);
    assert(*at(arr, 2) == 20);

    insert(arr, 0, 5);
    assert(!empty(arr));
    assert(size(arr) == 4);
    assert(*at(arr, 0) == 5);
    assert(*at(arr, 1) == 10);
    assert(*at(arr, 2) == 15);
    assert(*at(arr, 3) == 20);

    removeIndex(arr, 1);
    assert(!empty(arr));
    assert(size(arr) == 3);
    assert(*at(arr, 0) == 5);
    assert(*at(arr, 1) == 15);
    assert(*at(arr, 2) == 20);

    reallocate(arr, 1000);
    assert(!empty(arr));
    assert(size(arr) == 3);
    assert(capacity(arr) == 1000);
    assert(*at(arr, 0) == 5);
    assert(*at(arr, 1) == 15);
    assert(*at(arr, 2) == 20);

    reallocate(arr, 10);
    assert(capacity(arr) == 1000);

    freeArray(arr);
    printf("\nArrayPublicInterface passed.\n");
}
// TODO: Write tests for private methods
