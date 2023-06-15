#include "js_string_methods.h"

#include "stdlib.h"

#include "../dynamic_array/dynamic_array.h"
#include "../array_utils/js_array_methods.h"

bool strEquals(const char* l, const char* r) {
    __checkPointerValidity(l);
    __checkPointerValidity(r);

    int lSize = __strlen(l);
    int rSize = __strlen(r);

    bool equals = true;
    if (lSize == rSize) {
        for (int i = 0; i < lSize; ++i) {
            if (*(l + i) != *(r + i)) {
                equals = false;
                break;
            }
        }
    } else {
        equals = false;
    }

    return equals;
}

char stringAt(char* str, int ix) {
    if (ix >= 0) {
        return __charAtHelper(str, ix);
    }
    __checkPointerValidity(str);

    int size = __strlen(str);
    return (ix * -1 <= size) ? *(str + (size + ix)) : -1;
}

char charAt(char* str, int ix) {
    return __charAtHelper(str, ix);
}

int charCodeAt(char* str, int ix) {
    return (int)__charAtHelper(str, ix);
}

char* strConcat(char* str1, char* str2) {
    __checkPointerValidity(str1);
    __checkPointerValidity(str2);

    int size1 = __strlen(str1);
    int size2 = __strlen(str2);

    char* result = (char*)malloc((size1 + size2) * sizeof(char) + 1);

    int i = 0;
    while (i < size1) {
        *(result + i) = *(str1 + i);
        ++i;
    }

    while (i - size1 < size2) {
        *(result + i) = *(str2 + (i - size1));
        ++i;
    }
    *(result + i) = '\0';

    return result;
}

bool endsWith(char* str, char* searchStr) {
    return __bookendHelper(str, searchStr, true);
}

bool startsWith(char* str, char* searchStr) {
    return __bookendHelper(str, searchStr, false);
}

bool __bookendHelper(char* str, char* searchStr, bool fromEnd) {
    __checkPointerValidity(str);
    __checkPointerValidity(searchStr);

    const int strSize = __strlen(str);
    const int searchStrSize = __strlen(searchStr);

    if (searchStrSize > strSize) {
        return false;
    }
    
    int i = fromEnd ? strSize - searchStrSize - 1: -1;
    int until = fromEnd ? strSize : searchStrSize;
    int align = fromEnd ? -1 * (strSize - searchStrSize) : 0;

    while (++i < until && (*(str + i) == *(searchStr + i + align))) {}

    return (i == until);
}

bool strIncludes(char* str, char* searchStr) {
    return strIndexOf(str, searchStr, 0) != -1;
}

int strIndexOf(const char* str, const char* searchStr, int startIx) {
    return __strIndexOfHelper(str, searchStr, startIx, false);
}

int strLastIndexOf(char* str, char* searchStr, int startIx) {
    return __strIndexOfHelper(str, searchStr, startIx, true);
}

void padEnd(char** str, size_t newSize, char* padStr) {
    __padHelper(str, newSize, padStr, true);
}

void padStart(char** str, size_t newSize, char* padStr) {
    __padHelper(str, newSize, padStr, false);
}

char* repeat(char* str, int count) {
    __checkPointerValidity(str);
    if (count <= 0) {
        return NULL;
    }

    const int strSize = __strlen(str);
    const int resSize = strSize * count;

    char* res = (char*)malloc((resSize + 1) * sizeof(char));
    for (int i = 0; i < resSize; i += strSize) {
        for (int j = 0; j < strSize; ++j) {
            *(res + i + j) = *(str + j);
        }
    }
    *(res + resSize) = '\0';

    return res;
}

char* trimStart(char* str) {
    return __trimHelper(str, false);
}

char* trimEnd(char* str) {
    return __trimHelper(str, true);
}

char* trim(char* str) {
    char* trimmedFromEnd = __trimHelper(str, true);
    if (trimmedFromEnd == NULL) {
        return NULL;
    }

    char* res = __trimHelper(trimmedFromEnd, false);
    free(trimmedFromEnd);

    return res;
}

void toLowerCase(char* str) {
    return __toCaseHelper(str, true);
}

void toUpperCase(char* str) {
    return __toCaseHelper(str, false);
}

char* substr(const char* str, int start, int end) {
    __checkPointerValidity(str);

    start = start < 0 ? 0 : start;
    end = end < 0 ? 0 : end;

    const int size = __strlen(str);
    __checkBounds(start, size);
    __checkBounds(end - 1, size);

    const int substrSize = (end - start);
    char* sub = (char*)malloc((substrSize + 1) * sizeof(char));
    for (int i = start; i < end; ++i) {
        *(sub + i - start) = *(str + i);
    }
    *(sub + substrSize) = '\0';

    return sub;
}

char* strSlice(const char* str, int start, int end) {
    __checkPointerValidity(str);

    int size = __strlen(str);
    start = (start < 0) ? (size + start) : start;
    end = (end < 0) ? (size + end) : end;

    return substr(str, start, end);
}

char** strSplit(const char* str, const char* separator) {
    __checkPointerValidity(str);
    __checkPointerValidity(separator);

    int strSize = __strlen(str);
    int sprtSize = __strlen(separator);

    if (strSize <= sprtSize) {
        return NULL;
    }

    const size_t MaxOccurancesCount = 100;
    int* separatorOccurences = (int*)malloc(MaxOccurancesCount * sizeof(int));

    size_t count = 0;
    separatorOccurences[count++] = 0 - sprtSize;

    int startIx = 0;

    while (true) {
        startIx = __strIndexOfHelper(str, separator, startIx, false);
        if (startIx == -1) {
            break;
        }
        separatorOccurences[count++] = startIx;
        startIx += sprtSize;
    }
    separatorOccurences[count++] = strSize;

    char** res = (char**)malloc((count + 1) * sizeof(char*));
    for (int i = 0; i < count - 1; ++i) {
        res[i] = substr(str, separatorOccurences[i] + sprtSize, separatorOccurences[i + 1]);
    }

    free(separatorOccurences);
    return res;
}

char* strReplace(const char* str, const char* pattern, const char* replacement, int searchFrom) {
    __checkPointerValidity(replacement);

    int patternStartIx = strIndexOf(str, pattern, searchFrom);
    if (patternStartIx == -1) {
        return NULL;
    }

    int strSize = __strlen(str);
    int patternSize = __strlen(pattern);
    int replacementSize = __strlen(replacement);

    int resSize = strSize + (replacementSize - patternSize);
    char* res = (char*)malloc((resSize + 1) * sizeof(char));

    int i = 0;
    for (; i < patternStartIx; ++i) {
        *(res + i) = *(str + i);
    }

    int j = 0;
    for (; j < replacementSize; ++j) {
        *(res + i + j) = *(replacement + j);
    }
    j += i;
    i += patternSize;

    while (j < resSize) {
        *(res + j) = *(str + i);
        ++j;
        ++i;
    }
    *(res + resSize) = '\0';

    return res;
}

char* __trimHelper(char* str, bool fromEnd) {
    int count = __symbolCountFromEdge(str, ' ', fromEnd);
    int strSize = __strlen(str);

    int trimmedSize = strSize - count;
    if (!trimmedSize) {
        return NULL;
    }

    char* trimmed = (char*)malloc((trimmedSize + 1) * sizeof(char));

    int align = fromEnd ? 0 : count;
    for (int i = 0; i < trimmedSize; ++i) {
        *(trimmed + i) = *(str + i + align);
    }
    *(trimmed + trimmedSize) = '\0';

    return trimmed;
}

int __symbolCountFromEdge(char* str, char symbol, bool fromEnd) {
    __checkPointerValidity(str);

    int strSize = __strlen(str);

    int ix = fromEnd ? strSize - 1 : 0;
    int final = fromEnd ? 0 : strSize;
    void(*step)(int*) = fromEnd ? __decrement : __increment;
    bool(*condOp)(int, int) = fromEnd ? __greaterOrEq : __less;

    while (condOp(ix, final) && *(str + ix) == symbol) {
        step(&ix);
    }

    return fromEnd ? strSize - ix - 1 : ix;
}

int __strlen(const char* str) {
    int size = -1;
    while (*(str + ++size)) {}

    return size;
}

char __charAtHelper(char* str, int ix) {
    __checkPointerValidity(str);
    int size = __strlen(str);

    return (ix < 0 || ix >= size) ? -1 : *(str + ix);
}

int __strIndexOfHelper(const char* str, const char* searchStr, int ix, bool getLast) {
    __checkPointerValidity(str);

    const int strSize = __strlen(str);
    const int searchStrSize = __strlen(searchStr);

    if ((searchStrSize > strSize) ||
        (!getLast && ix >= (strSize - searchStrSize)) ||
        (getLast && ix < searchStrSize)) {
        return -1;
    }

    int iInitialValue = -1;
    int iFinalValue = -1;
    bool(*op)(int, int) = NULL;
    void(*step)(int*) = NULL;

    __iterationConfigure(ix, strSize - searchStrSize + 1, &iInitialValue, &iFinalValue, &op, &step, getLast);

    if (getLast) {
        iFinalValue = 0;
        iInitialValue = ix;
    }

    int jInitialValue = getLast ? searchStrSize - 1 : 0;
    int jFinalValue = getLast ? 0 : searchStrSize;

    int res = -1;
    for (int i = iInitialValue; op(i, iFinalValue); step(&i)) {
        int j = jInitialValue;
        for (; op(j, jFinalValue); step(&j)) {
            char currCh = getLast ? *(str + i - (searchStrSize - j - 1)) : *(str + i + j);
            if (*(searchStr + j) != currCh) {
                break;
            }
        }

        if ((getLast && ((j + 1) == jFinalValue)) ||
            (!getLast && (j == jFinalValue))) {
            res = i - jInitialValue;
            break;
        }
    }

    return res;
}

void __padHelper(char** str, int newSize, char* padStr, bool fromEnd) {
    __checkPointerValidity(*str);
    __checkPointerValidity(padStr);

    const int strSize = __strlen(*str);
    int padStrSize = __strlen(padStr);
    if (newSize < strSize || !padStrSize) {
        return;
    }

    int extraSize = newSize - strSize;

    int fullRepeatCount = extraSize / padStrSize;
    char* padding = repeat(padStr, fullRepeatCount);

    int extraSymbolsCount = extraSize % padStrSize;
    int finalPaddingSize = padStrSize * fullRepeatCount + extraSymbolsCount;

    padding = realloc(padding, (finalPaddingSize + 1) * sizeof(char));
    for (int i = 0; i < extraSymbolsCount; ++i) {
        *(padding + fullRepeatCount * padStrSize) = *(padStr + i);
    }
    *(padding + finalPaddingSize) = '\0';

    char* res = fromEnd ? strConcat(*str, padding) : strConcat(padding, *str);
    free(*str);
    *str = res;
}

void __toCaseHelper(char* str, bool toLower) {
    __checkPointerValidity(str);

    int startRange = toLower ? 'A' : 'a';
    int endRange = toLower ? 'Z' : 'z';
    int align = toLower ? ('a' - 'A') : ('A' - 'a');

    int size = __strlen(str);
    for (int i = 0; i < size; ++i) {
        if (*(str + i) >= startRange && *(str + i) <= endRange) {
            char toCase = *(str + i) + align;
            *(str + i) = toCase;
        }
    }
}
