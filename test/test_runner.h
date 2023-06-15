#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include "stdio.h"

#include "dynamic_array/dynamic_array_test.h"
#include "array_utils/js_array_methods_test.h"
#include "string_utils/js_string_methods_test.h"

void executeAllTests() {
    executeAllDynamicArrayTests();
    executeAllJSArrayMethodsTests();
    executeAllJSStringMethodsTests();
    printf("\033[0;32m");
    printf("\n\t\t\t\t!!! All Tests Have Passed !!!\n");
    printf("\033[0m");
}

#endif /* TEST_RUNNER_H */
