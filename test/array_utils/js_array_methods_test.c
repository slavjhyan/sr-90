#include "js_array_methods_test.h"

#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

#include "../../array_utils/js_array_methods.h"

void executeAllJSArrayMethodsTests() {
    __testJSArrayMethods();
    printf("\033[0;34m");
    printf("\n\tJS Array Methods Tests Have Passed\n");
    printf("\033[0m");
}

void __testJSArrayMethods() {
    __testConcat();
    __testEvery();
    __testFilter();
    __testForEach();
    __testIndexOf();
    __testLastIndexOf();
    __testMap();
    __testReduce();
    __testReverse();
    __testSlice();
    __testSome();
    __testSort();
    __testSplice();
    __testFill();
    __testFinds();
    __testInclude();
    __testJoin();
    __testWith();
    __testEntries();
    printf("\nJSArrayMethods passed.\n");
}

void __testConcat() {
    DynamicArray* arr0 = (DynamicArray*)malloc(sizeof(DynamicArray));
    DynamicArray* arr1 = (DynamicArray*)malloc(sizeof(DynamicArray));

    defaultInitArray(arr0);
    defaultInitArray(arr1);

    for (int i = 0; i < 5; ++i) {
        pushBack(arr0, i * 10);
    }

    for (int i = 5; i < 10; ++i) {
        pushBack(arr1, i * 10);
    }

    DynamicArray* catRes = concat(arr0, arr1);
    for (int i = 0; i < arr0->_size; ++i) {
        assert(*at(catRes, i) == *at(arr0, i));
    }

    for (int i = 0; i < arr1->_size; ++i) {
        assert(*at(catRes, i + arr0->_size) == *at(arr1, i));
    }

    clear(arr0);
    freeArray(catRes);

    catRes = concat(arr0, arr1);
    for (int i = 0; i < catRes->_size; ++i) {
        assert(*at(catRes, i) == *at(arr1, i));
    }

    freeArray(catRes);
    catRes = concat(arr1, arr0);
    for (int i = 0; i < catRes->_size; ++i) {
        assert(*at(catRes, i) == *at(arr1, i));
    }

    freeArray(arr0);
    freeArray(arr1);
    freeArray(catRes);
}

void __testEvery() {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    defaultInitArray(arr);

    for(int i = 0; i < 5; ++i) {
        pushBack(arr, 2 * i);
    }

    assert(every(arr, &__isEven));

    insert(arr, 2, 3);
    assert(!every(arr, &__isEven));
    assert(!every(arr, &__isOdd));

    freeArray(arr);
}

void __testFilter() {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    defaultInitArray(arr);

    for(int i = 0; i < 5; ++i) {
        pushBack(arr, 2 * i);
    }

    pushBack(arr, 33);
    insert(arr, 2, 55);

    DynamicArray* res = filter(arr, &__isOdd);
    assert(*at(res, 0) == 55);
    assert(*at(res, 1) == 33);

    freeArray(res);
    freeArray(arr);
}

void __testForEach() {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    defaultInitArray(arr);

    for(int i = 0; i < 5; ++i) {
        pushBack(arr, i);
    }

    // forEach(arr, &__isEven);

    // for(int i = 0; i < 5; ++i) {
    //     assert(*at(arr, 0) == 0);
    // }

    freeArray(arr);
}

void __testIndexOf() {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    defaultInitArray(arr);

    for(int i = 0; i < 5; ++i) {
        pushBack(arr, i);
    }
    pushBack(arr, 4);

    assert(indexOf(arr, 4) == 4);
    assert(indexOf(arr, 5) == -1);

    freeArray(arr);
}

void __testLastIndexOf() {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    defaultInitArray(arr);

    for(int i = 0; i < 5; ++i) {
        pushBack(arr, i);
    }
    pushBack(arr, 4);

    assert(lastIndexOf(arr, 4) == 5);
    assert(lastIndexOf(arr, 5) == -1);

    freeArray(arr);
}

void __testMap() {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    defaultInitArray(arr);

    for(int i = 0; i < 5; ++i) {
        pushBack(arr, i);
    }

    DynamicArray* res = map(arr, &__assignToZero);

    for(int i = 0; i < 5; ++i) {
        assert(*at(res, 0) == 0);
    }

    freeArray(res);
    freeArray(arr);
}

void __testReverse() {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    defaultInitArray(arr);

    for(int i = 0; i < 5; ++i) {
        pushBack(arr, i);
    }

    DynamicArray* res = reverse(arr);

    for (int i = 0; i < 5; ++i) {
        assert(*at(arr, i) == *at(res, i) && *at(arr, i) == 4 - i);
    }

    freeArray(res);
    freeArray(arr);
}

void __testSlice() {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    defaultInitArray(arr);

    for(int i = 0; i < 5; ++i) {
        pushBack(arr, i);
    }

    int startIx = 1;
    int endIx = 3;

    DynamicArray* res = slice(arr, startIx, endIx);
    assert(size(res) == 2);
    assert(*at(res, 0) == 1);
    assert(*at(res, 1) == 2);

    freeArray(res);
    freeArray(arr);
}

void __testSome() {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    defaultInitArray(arr);

    for(int i = 0; i < 5; ++i) {
        pushBack(arr, 2 * i);
    }

    assert(!some(arr, &__isOdd));

    insert(arr, 2, 3);
    assert(some(arr, &__isEven));
    assert(some(arr, &__isOdd));

    freeArray(arr);
}

void __testSort() {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    defaultInitArray(arr);

    pushBack(arr, 7);
    pushBack(arr, 3);
    pushBack(arr, 4);
    pushBack(arr, 0);
    pushBack(arr, 1);
    pushBack(arr, 6);
    pushBack(arr, 5);
    pushBack(arr, 2);

    sort(arr);
    for (int i = 0; i < size(arr); ++i) {
        assert(*at(arr, i) == i);
    }

    clear(arr);
    pushBack(arr, 0);
    pushBack(arr, 0);
    pushBack(arr, 0);
    pushBack(arr, 0);

    sort(arr);
    for (int i = 0; i < size(arr); ++i) {
        assert(*at(arr, i) == 0);
    }

    freeArray(arr);
}

void __testFill() {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    defaultInitArray(arr);

    for (int i = 0; i < 8; ++i) {
        pushBack(arr, i);
    }

    const int val = -1;
    const int start = 2;
    const int end = 6;

    fill(arr, val, start, end);
    assert(size(arr) == 8);

    for (int i = 0; i < 8; ++i) {
        int assertVal = 0;
        if (i >= start && i < end) {
            assertVal = val;
        } else {
            assertVal = i;
        }
        assert(*at(arr, i) == assertVal);
    }

    freeArray(arr);
}

void __testFinds() {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    defaultInitArray(arr);

    for(int i = 0; i < 5; ++i) {
        pushBack(arr, 2 * i);
    }

    assert(find(arr, &__isOdd) == INT_MIN);
    assert(find(arr, &__isEven) == 0);

    assert(findIndex(arr, &__isOdd) == -1);
    assert(findIndex(arr, &__isEven) == 0);

    assert(findLastIndex(arr, &__isOdd) == -1);
    assert(findLastIndex(arr, &__isEven) == 4);

    insert(arr, 2, 3);
    assert(find(arr, &__isOdd) == 3);
    assert(findIndex(arr, &__isOdd) == 2);
    assert(findLastIndex(arr, &__isOdd) == 2);

    freeArray(arr);
}

void __testInclude() {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    defaultInitArray(arr);

    for(int i = 0; i < 5; ++i) {
        pushBack(arr, i);
    }

    assert(includes(arr, 4));
    assert(!includes(arr, 5));

    freeArray(arr);
}

void __testJoin() {
    DynamicArray* darr = (DynamicArray*)malloc(sizeof(DynamicArray));
    defaultInitArray(darr);

    for(int i = 0; i < 5; ++i) {
        pushBack(darr, i);
    }

    const char separator = ',';
    char* concatinatedArrPtr = join(darr, separator);

    for (int i = 0; *(concatinatedArrPtr + i) != '\0'; ++i) {
        char ch = *(concatinatedArrPtr + i);
        if (!(i & 1)) {
            assert(ch == '0' + (i / 2));
        } else {
            assert(ch == separator);
        }
    }

    // TODO:
    // free(concatinatedArrPtr);
    free(darr);
}

void __testWith() {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    defaultInitArray(arr);

    for(int i = 0; i < 8; ++i) {
        pushBack(arr, i);
    }

    int ix = 2;
    int val = 42;

    DynamicArray* res = with(arr, ix, val);
    assert(size(res) == size(arr));
    assert(*at(res, 0) == 0);
    assert(*at(res, 1) == 1);
    assert(*at(res, ix) == val);
    for(int i = ix + 1; i < size(res); ++i) {
        assert(*at(res, i) == i);
    }

    freeArray(res);
    freeArray(arr);
}

void __testEntries() {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    defaultInitArray(arr);

    for(int i = 0; i < 5; ++i) {
        pushBack(arr, i);
    }

    ArrayIterator* it = entries(arr);
    for (int i = 0; i < size(arr); ++i) {
        assert(next(it) == i);
    }
    assert(it->_p - size(arr) == arr->_ptr);

    free(it);
    free(arr);
}


void __testSplice() {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    defaultInitArray(arr);

    for(int i = 0; i < 8; ++i) {
        pushBack(arr, i);
    }

    int startIx = 3;
    int deleteCount = 0;
    int val = 77;

    splice(arr, startIx, deleteCount, val);
    assert(size(arr) == 9);
    assert(*at(arr, 0) == 0);
    assert(*at(arr, 1) == 1);
    assert(*at(arr, 2) == 2);
    assert(*at(arr, startIx) == val);

    for(int i = startIx + 1; i < 9; ++i) {
        assert(*at(arr, i) == (i - 1));
    }

    deleteCount = 3;
    val = 42;
    splice(arr, startIx, deleteCount, val);
    assert(size(arr) == 7);
    assert(*at(arr, startIx) == val);
    for (int i = startIx + 1; i < 7; ++i) {
        assert(*at(arr, i) == i + 1);
    }

    deleteCount = 99999;
    val = -1;
    startIx = 1;
    splice(arr, startIx, deleteCount, val);
    assert(size(arr) == 2);
    assert(*at(arr, 0) == 0);
    assert(*at(arr, startIx) == val);

    freeArray(arr);
}

void __testReduce() {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    defaultInitArray(arr);

    for(int i = 0; i < 5; ++i) {
        pushBack(arr, i);
    }

    int sum = reduce(arr, &__add, 0);
    assert(sum == 10);

    sum = reduce(arr, &__add, -10);
    assert(sum == 0);

    freeArray(arr);
}

bool __isEven(int n) {
    return n >= 0 && !(n & 1);
}

bool __isOdd(int n) {
    return n >= 0 && (n & 1);
}

void __assignToZero(int* n) {
    __checkPointerValidity(n);
    *n = 0;
}

int __add(int x, int y) {
    return x + y;
}
