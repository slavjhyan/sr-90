#include "js_array_methods.h"

#include "stdlib.h"
#include "math.h"

// TODO: Use only public interface of DynamicArray

DynamicArray* concat(DynamicArray* darr0, DynamicArray* darr1) {
    __checkPointerValidity(darr0);
    __checkPointerValidity(darr1);

    const int resSize = darr0->_size + darr1->_size;
    const int resCap = resSize + 1;
    int* resArrPtr = (int*)malloc(resCap * sizeof(int));

    for (int i = 0; i < darr0->_size; ++i) {
        resArrPtr[i] = darr0->_ptr[i];
    }

    for (int i = 0; i < darr1->_size; ++i) {
        resArrPtr[darr0->_size + i] = darr1->_ptr[i];
    }

    DynamicArray* resArr = (DynamicArray*)malloc(sizeof(DynamicArray));
    initArray(resArr, resArrPtr, resSize, resCap);

    return resArr;
}

bool every(DynamicArray* darr, bool(*f)(int)) {
    __checkPointerValidity(darr);
    __checkPointerValidity(f);

    bool pass = true;
    for (int i = 0; i < darr->_size; ++i) {
        if (!f(*at(darr, i))) {
            pass = false;
            break;
        }
    }

    return pass;
}

DynamicArray* filter(DynamicArray* darr, bool(*f)(int)) {
    __checkPointerValidity(darr);
    __checkPointerValidity(f);

    DynamicArray* filteredArr = (DynamicArray*)malloc(sizeof(DynamicArray));
    defaultInitArray(filteredArr);

    for (int i = 0; i < darr->_size; ++i) {
        int elem = *at(darr, i);
        if (f(elem)) {
            pushBack(filteredArr, elem);
        }
    }

    return filteredArr;
}

void forEach(DynamicArray* darr, void(*f)(int)) {
    __checkPointerValidity(darr);
    __checkPointerValidity(f);

    for (int i = 0; i < darr->_size; ++i) {
        f(*at(darr, i));
    }
}

int indexOf(DynamicArray* darr, int val) {
    return __indexOfHelper(darr, val, false);
}

int lastIndexOf(DynamicArray* darr, int val) {
    return __indexOfHelper(darr, val, true);
}

DynamicArray* map(DynamicArray* darr, void(*f)(int*)) {
    __checkPointerValidity(darr);
    __checkPointerValidity(f);

    DynamicArray* res = (DynamicArray*)malloc(sizeof(DynamicArray));

    defaultInitArray(res);
    copy(darr, res);

    for (int i = 0; i < darr->_size; ++i) {
        f(at(res, i));
    }

    return res;
}

DynamicArray* reverse(DynamicArray* darr) {
    __checkPointerValidity(darr);
    for (int i = 0; i < darr->_size / 2; ++i) {
        int tmp = *at(darr, i);
        *at(darr, i) = *at(darr, darr->_size - i - 1);
        *at(darr, darr->_size - i - 1) = tmp;
    }

    DynamicArray* reversedArrCpy = (DynamicArray*)malloc(sizeof(DynamicArray));
    defaultInitArray(reversedArrCpy);
    copy(darr, reversedArrCpy);

    return reversedArrCpy;
}

DynamicArray* slice(DynamicArray* darr, int start, int end) {
    __checkPointerValidity(darr);
    __checkArrayBounds(darr, start);
    __checkArrayBounds(darr, end);
    __checkRangeValidity(start, end);

    if (darr->_ptr == NULL) {
        return NULL;
    }

    const int resSize = end - start;
    const int resCap = resSize + 1;

    int* slicedArrPtr = (int*)malloc(resCap * sizeof(int));
    for (int i = start; i < end; ++i) {
        slicedArrPtr[i - start] = *at(darr, i);
    }

    DynamicArray* slicedArr = (DynamicArray*)malloc(sizeof(DynamicArray));
    initArray(slicedArr, slicedArrPtr, resSize, resCap);

    return slicedArr;
}

bool some(DynamicArray* darr, bool(*f)(int)) {
    __checkPointerValidity(darr);
    __checkPointerValidity(f);

    bool pass = false;
    for (int i = 0; i < darr->_size; ++i) {
        if (f(*at(darr, i))) {
            pass = true;
            break;
        }
    }

    return pass;
}

DynamicArray* sort(DynamicArray* darr) {
    __checkPointerValidity(darr);
    for (int i = 0; i < darr->_size - 1; ++i) {
        for (int j = 0; j < darr->_size - i - 1; ++j) {
            if (*at(darr, j) > *at(darr, j + 1)) {
                int tmp = *at(darr, j);
                *at(darr, j) = *at(darr, j + 1);
                *at(darr, j + 1) = tmp;
            }
        }
    }

    return darr;
}

DynamicArray* fill(DynamicArray* darr, int value, int start, int end) {
    __checkPointerValidity(darr);
    __checkArrayBounds(darr, start);
    __checkArrayBounds(darr, end);
    __checkRangeValidity(start, end);

    if (darr->_ptr == NULL) {
        return NULL;
    }

    for (int i = start; i < end; ++i) {
        darr->_ptr[i] = value;
    }

    return darr;
}

int find(DynamicArray* darr, bool(*f)(int)) {
    return __findHelper(darr, f, false, false);
}

int findIndex(DynamicArray* darr, bool(*f)(int)) {
    return __findHelper(darr, f, true, false);
}

int findLastIndex(DynamicArray* darr, bool(*f)(int)) {
    return __findHelper(darr, f, true, true);
}

bool includes(DynamicArray* darr, int val) {
    return __indexOfHelper(darr, val, false) != -1;
}

char* join(DynamicArray* darr, char separator) {
    __checkPointerValidity(darr);

    if (size(darr) <= 0) {
        return NULL;
    }

    size_t strSize = size(darr) - 1;
    for (int i = 0; i < size(darr); ++i) {
        strSize += __digitCount(*at(darr, i));
    }

    char* str = (char*)malloc(strSize);
    int count = 0;
    for (int i = 0; i < size(darr); ++i) {
        int num = *at(darr, i);
        itoa(num, str + count, 10);
        count += __digitCount(num);
        *(str + count) = separator;
        ++count;
    }
    *(str + count - 1) = '\0';

    return str;
}

DynamicArray* with(DynamicArray* darr, int index, int val) {
    __checkPointerValidity(darr);
    __checkArrayBounds(darr, index);

    const int resSize = size(darr);
    const int resCap = resSize;

    int* resArrPtr = (int*)malloc(resCap * sizeof(int));
    for (int i = 0; i < resSize; ++i) {
        resArrPtr[i] = *at(darr, i);
    }
    resArrPtr[index] = val;

    DynamicArray* resArr = (DynamicArray*)malloc(sizeof(DynamicArray));
    initArray(resArr, resArrPtr, resSize, resCap);

    return resArr;
}

ArrayIterator* entries(DynamicArray* darr) {
    __checkPointerValidity(darr);

    ArrayIterator* it = (ArrayIterator*)malloc(sizeof(ArrayIterator));
    defaultInitArrayIter(it);
    bindTo(it, darr);

    return it;
}

void splice(DynamicArray* darr, int start, int deleteCount, int val) {
    __checkPointerValidity(darr);
    __checkArrayBounds(darr, start);

    if (start + deleteCount >= size(darr)) {
        deleteCount = size(darr) - start;
    }

    if (!deleteCount) {
        insert(darr, start, val);
    }
    else {
        __shiftLeft(darr, start, deleteCount - 1);
        *at(darr, start) = val;
        darr->_size = darr->_size - deleteCount + 1;
    }
}

int reduce(DynamicArray* darr, int(*f)(int, int), int initVal) {
    __checkPointerValidity(darr);
    __checkPointerValidity(f);

    for (int i = 0; i < size(darr); ++i) {
        initVal = f(initVal, *at(darr, i));
    }

    return initVal;
}


int __findHelper(DynamicArray* darr, bool(*f)(int), bool getIndex, bool getLast) {
    __checkPointerValidity(darr);
    __checkPointerValidity(f);

    int ret = getIndex ? -1 : INT_MIN;
    if(size(darr) <= 0) {
        return ret;
    }

    int iterInitialValue = 0;
    int iterFinalValue = 0;
    bool(*op)(int, int) = NULL;
    void(*step)(int*) = NULL;

    __iterationConfigure(0, size(darr), &iterInitialValue, &iterFinalValue, &op, &step, getLast);

    for (int i = iterInitialValue; op(i, iterFinalValue); step(&i)) {
        int elem = *at(darr, i);
        if (f(elem)) {
            ret = getIndex ? i : elem;
            break;
        }
    }

    return ret;
}

int __indexOfHelper(DynamicArray* darr, int val, bool getLast) {
    __checkPointerValidity(darr);

    int ix = -1;
    if(size(darr) <= 0) {
        return ix;
    }

    int iterInitialValue = 0;
    int iterFinalValue = 0;
    bool(*op)(int, int) = NULL;
    void(*step)(int*) = NULL;

    __iterationConfigure(0, size(darr), &iterInitialValue, &iterFinalValue, &op, &step, getLast);

    for (int i = iterInitialValue; op(i, iterFinalValue); step(&i)) {
        if (*at(darr, i) == val) {
            ix = i;
            break;
        }
    }

    return ix;
}

void __iterationConfigure(int beginVal, int endVal, int* start, int* end, bool(**conditionOp)(int, int), void(**step)(int*), bool getLast) {
    *start = getLast ? endVal - 1 : beginVal;
    *end = getLast ? beginVal : endVal;
    *conditionOp = getLast ? &__greaterOrEq : &__less;
    *step = getLast ? &__decrement : &__increment;
}

void __checkRangeValidity(int start, int end) {
    if (start >= end) {
        perror("start index should be less than the end index\n");
        exit(1);
    }
}

bool __greaterOrEq(int x, int y) {
    return x >= y;
}

bool __less(int x, int y) {
    return x < y;
}

void __increment(int* x) {
    ++(*x);
}

void __decrement(int* x) {
    --(*x);
}

int __digitCount(int num) {
    int count = 0;
    do {
        ++count;
        num /= 10;
    } while (num);

    return count;
}
