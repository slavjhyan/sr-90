#ifndef JS_ARRAY_METHODS_TEST_H
#define JS_ARRAY_METHODS_TEST_H

#include "stdbool.h"

void executeAllJSArrayMethodsTests();

void __testJSArrayMethods();

void __testConcat();

void __testEntries();

void __testEvery();

void __testFilter();

void __testFill();

void __testFinds();

void __testForEach();

void __testInclude();

void __testIndexOf();

void __testJoin();

void __testLastIndexOf();

void __testMap();

void __testReduce();

void __testReverse();

void __testSlice();

void __testSome();

void __testSort();

void __testSplice();

void __testWith();


// MARK: Private Helper Methods

bool __isEven(int);

bool __isOdd(int);

void __assignToZero(int*);

int __add(int, int);

#endif /* JS_ARRAY_METHODS_TEST_H */
