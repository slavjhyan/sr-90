#ifndef JS_ARRAY_METHODS_H
#define JS_ARRAY_METHODS_H

#include "../dynamic_array/dynamic_array.h"
#include "../dynamic_array/iterator/dynamic_array_iterator.h"

/**
 * @brief The concat() method is used to merge two or more arrays.
 * 
 * @note This method does not change the existing arrays.
 * 
 * @param darr0 Pointer to the first array to concatinate
 * @param darr1 Pointer to the second array to concatinate
 * @return A new concatinated array instance
*/
DynamicArray* concat(DynamicArray* darr0, DynamicArray* darr1);

/**
 * @brief The every() method tests whether all elements
 *        in the array pass the test implemented by the provided function.
 * 
 * @param darr Pointer to the array
 * @param f Pointer to the function that tests each element of the array
 * @return true if all elements of the array pass the test implemnted in f
 *         false otherwise
*/
bool every(DynamicArray* darr, bool(*f)(int));

/**
 * @brief The filter() method creates a shallow copy of a portion of a given array,
 *        filtered down to just the elements from the given array that pass the test
 *        implemented by the provided function.
 * 
 * @param darr Pointer to the array whose elements will be used for filtering
 * @param f Pointer to the function that tests each element of the array
 * @return Pointer to a new array with filtered values that passed f
*/
DynamicArray* filter(DynamicArray* darr, bool(*f)(int));

/**
 * @brief The forEach() method executes a provided function once for each array element.
 *  
 * @param darr Pointer to the array whose elements will be passed to f
 * @param f Pointer to the function
*/
void forEach(DynamicArray* darr, void(*f)(int));

/**
 * @brief The indexOf() method returns the first index at which a given element can be found in the array
 *  
 * @param darr Pointer to the array
 * @param val Element to search in the array
 * @return Index of the first occurance of val in the array
 *         -1 if the provided element was not found
*/
int indexOf(DynamicArray* darr, int val);

/**
 * @brief The lastIndexOf() method returns the last index at which a given element can be found in the array
 *  
 * @param darr Pointer to the array
 * @param val Element to search in the array
 * @return Index of the last occurance of val in the array
 *         -1 if the provided element was not found
*/
int lastIndexOf(DynamicArray* darr, int val);

/**
 * @brief The map() method creates a new array populated with the results of
 *        calling a provided function on every element in the calling array.
 * 
 * @note The array itself remains unchanged
 * 
 * @param darr Pointer to the array based on whose elements the new array will be created
 * @param f Pointer to the function to perform changes for every element in darr to construct the new array
*/
DynamicArray* map(DynamicArray* darr, void(*f)(int*));

/**
 * @brief The reverse() method reverses an array in-place and returns the reference to the same array
 * 
 * @param darr Pointer to the array which will be reversed
 * @param f Pointer to the function to perform changes for every element in darr to construct the new array
*/
DynamicArray* reverse(DynamicArray* darr);

/**
 * @brief The slice() method returns a shallow copy of a portion of an array
 *        into a new array object selected from start to end,
 *        end is not included
 * 
 * @note The original array remains unchanged
 * 
 * @param darr Pointer to the array whose elements will be used for filtering
 * @param start starting index of a portion of the array
 * @param end ending index of a portion of the array (not included)
 * @return Pointer to a new array with sliced portion
*/
DynamicArray* slice(DynamicArray* darr, int start, int end);

/**
 * @brief The some() method tests whether at least one element
 *        in the array passes the test implemented by the provided function
 * 
 * @param darr Pointer to the array
 * @param f Pointer to the function that tests each element of the array
 * @return True if it finds an element in darr for which the provided function returns true
 *         false otherwise
*/
bool some(DynamicArray* darr, bool(*f)(int));

/**
 * @brief The sort() method sorts the elements of an array in place
 * 
 * @param darr Pointer to the array to be sorted
 * @return reference to the same array, which is now sorted
*/
DynamicArray* sort(DynamicArray* darr);

/**
 * @brief The fill() method changes all elements in an array
 *        to a static value, from a start index to an end index
 * 
 * @note The array is modified
 * 
 * @param darr Pointer to the array whose elements will be modified
 * @param start starting index of the range
 * @param end ending index of the range (not included)
 * @return Pointer to the array with already filled values
*/
DynamicArray* fill(DynamicArray* darr, int value, int start, int end);

/**
 * @brief The find() method returns the first element in the
 *        provided array that satisfies the provided testing function
 *  
 * @param darr Pointer to the array
 * @param f Pointer to the function to execute on each element of the array
 *          until it returns true
 * @return Value of the first occurance that satisfies f in the array,
 *         INT_MIN if no element satisfies f
*/
int find(DynamicArray* darr, bool(*f)(int));

/**
 * @brief The findIndex() method returns the index of the first element in the
 *        provided array that satisfies the provided testing function
 *  
 * @param darr Pointer to the array
 * @param f Pointer to the function to execute on each element of the array
 *          until it returns true
 * @return Index of the first occurance that satisfies f in the array,
 *         -1 if no element satisfies f
*/
int findIndex(DynamicArray* darr, bool(*f)(int));

/**
 * @brief The findLastIndex() method returns the index of the last element in the
 *        provided array that satisfies the provided testing function
 *  
 * @param darr Pointer to the array
 * @param f Pointer to the function to execute on each element of the array
 *          until it returns true
 * @return Index of the last occurance that satisfies f in the array,
 *         -1 if no element satisfies f
*/
int findLastIndex(DynamicArray* darr, bool(*f)(int));

/**
 * @brief The includes() method determines whether an array includes a certain value
 *  
 * @param darr Pointer to the array
 * @param val Value to be searched in the array
 * @return true if the value exists in the array,
 *         false otherwise
*/
bool includes(DynamicArray* darr, int val);

/**
 * @brief The join() method creates and returns a new string by
 *        concatenating all of the elements in an array by specified separator
 *  
 * @param darr Pointer to the array to be concatinated
 * @param separator Separator to use for the elements of the array in string
 * @return Pointer to concatinated string
*/
char* join(DynamicArray* darr, char separator);

/**
 * @brief The with() method creates a copy of the passed array
 *        with one element modified
 * 
 * @note The original array remains unchanged
 * 
 * @param darr Pointer to the array whose elements will be used for filtering
 * @param index index of the element in the array to be modified
 * @param val the new value of the element at 'index' in the array
 * @return Pointer to a new array with changed value
*/
DynamicArray* with(DynamicArray* darr, int index, int val);

/**
 * @brief The entries() method returns a new array iterator pointer
 *        that contains the key/value pairs for each index in the array
 * 
 * @param darr Pointer to the array
 * @return Pointer to a new iterator of the array
*/
ArrayIterator* entries(DynamicArray* darr);

/**
 * @brief The splice() method changes the contents of an array by removing
 *        or replacing existing elements and/or adding new elements in-place
 * 
 * @param darr Pointer to the array to be spliced
 * @param start index from where the array will be spliced
 * @param deleteCount amount of elements to be deleted from start in array
 * @param val element value to replace/insert
*/
void splice(DynamicArray* darr, int start, int deleteCount, int val);


/**
 * @brief The reduce() method executes a user-supplied "reducer" callback function
 *        on each element of the array, in order, passing in the return value from
 *        the calculation on the preceding element. The final result of running the
 *        reducer across all elements of the array is a single value
 * 
 * @param darr Pointer to the array of which elemets will be passed to "reducer" function
 * @param f Pointer to the "reducer" function
 * @param initVal the first argument of "reducer"
 * @return result from running the "reducer" callback function to completion over the entire array
*/
int reduce(DynamicArray* darr, int(*f)(int, int), int initVal);


// MARK: Private Helper Methods

int __findHelper(DynamicArray* darr, bool(*f)(int), bool getIndex, bool last);

int __indexOfHelper(DynamicArray* darr, int val, bool last);

void __checkRangeValidity(int start, int end);

void __iterationConfigure(int beginVal, int endVal,
                          int* start, int* end,
                          bool(**conditionOp)(int, int),
                          void(**step)(int*),
                          bool getLast);

bool __greaterOrEq(int x, int y);

bool __less(int x, int y);

void __increment(int* x);

void __decrement(int* x);

int __digitCount(int num);

#endif /* JS_ARRAY_METHODS_H */
