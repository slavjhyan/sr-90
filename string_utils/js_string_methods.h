#ifndef JS_STRING_METHODS
#define JS_STRING_METHODS

#include "stdbool.h"
#include "stddef.h"

bool strEquals(const char* l, const char* r);

char stringAt(char* str, int ix);

char charAt(char* str, int ix);

int charCodeAt(char* str, int ix);

char* strConcat(char* str1, char* str2);

bool endsWith(char* str, char* searchStr);

bool startsWith(char* str, char* searchStr);

bool strIncludes(char* str, char* searchStr);

int strIndexOf(const char* str, const char* searchStr, int startIx);

int strLastIndexOf(char* str, char* searchStr, int startIx);

void padEnd(char** str, size_t newSize, char* padStr);

void padStart(char** str, size_t newSize, char* padStr);

char* repeat(char* str, int count);

char* trimStart(char* str);

char* trimEnd(char* str);

char* trim(char* str);

void toLowerCase(char* str);

void toUpperCase(char* str);

char* substr(const char* str, int start, int end);

char* strSlice(const char* str, int start, int end);

char** strSplit(const char* str, const char* separator);

char* strReplace(const char* str, const char* pattern, const char* replacement, int searchFrom);

char* strReplaceAll(const char* str, const char* pattern, const char* replacement);

char* __trimHelper(char* str, bool fromEnd);

int __symbolCountFromEdge(char* str, char symbol, bool fromEnd);

int __strlen(const char* str);

char __charAtHelper(char* str, int ix);

int __strIndexOfHelper(const char* str, const char* searchStr, int ix, bool getLast);

void __padHelper(char** str, int newSize, char* padStr, bool fromEnd);

bool __bookendHelper(char* str, char* searchStr, bool fromEnd);

void __toCaseHelper(char* str, bool toLower);

#endif /* JS_STRING_METHODS */
