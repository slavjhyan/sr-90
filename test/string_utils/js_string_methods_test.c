#include "js_string_methods_test.h"

#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

#include "../../string_utils/js_string_methods.h"

void executeAllJSStringMethodsTests() {
    __testStringAtMethods();
    __testStringConcat();
    __testStringBookend();
    __testStringIncludes();
    __testStringIndexOf();
    __testStringLastIndexOf();
    __testStringPad();
    __testStringRepeat();
    __testStringTrim();
    __testToCase();
    __testSubstrAndSlice();
    __testStringSplit();
    __testStringReplace();
    printf("\033[0;34m");
    printf("\n\tJS String Methods Tests Have Passed\n");
    printf("\033[0m");
}

void __testStringAtMethods() {
    char* str = "abcd";

    assert(stringAt(str, 0) == (char)'a');
    assert(stringAt(str, 1) == (char)'b');
    assert(stringAt(str, 2) == (char)'c');
    assert(stringAt(str, 3) == (char)'d');
    assert(stringAt(str, 4) == (char)255);

    assert(stringAt(str, -1) == (char)'d');
    assert(stringAt(str, -2) == (char)'c');
    assert(stringAt(str, -3) == (char)'b');
    assert(stringAt(str, -4) == (char)'a');
    assert(stringAt(str, -5) == (char)255);

    assert(charAt(str, 0) == (char)'a');
    assert(charAt(str, 1) == (char)'b');
    assert(charAt(str, 2) == (char)'c');
    assert(charAt(str, 3) == (char)'d');
    assert(charAt(str, 4) == (char)255);
    assert(charAt(str, -1) == (char)255);

    assert(charCodeAt(str, 0) == 'a');
    assert(charCodeAt(str, 1) == 'b');
    assert(charCodeAt(str, 2) == 'c');
    assert(charCodeAt(str, 3) == 'd');
    assert(charCodeAt(str, 4) == -1);
    assert(charCodeAt(str, -1) == (char)255);
}

void __testStringConcat() {
    char* str1 = "hello";
    char* str2 = ", ";
    char* str3 = "world";

    char* cat12 = "hello, ";
    char* res12 = strConcat(str1, str2);
    for (int i = 0; i < __strlen(res12); ++i) {
        assert(*(res12 + i) == *(cat12 + i));
    }

    char* cat13 = "helloworld";
    char* res13 = strConcat(str1, str3);
    for (int i = 0; i < __strlen(res13); ++i) {
        assert(*(res13 + i) == *(cat13 + i));
    }

    char* cat123 = "hello, world";
    char* res123 = strConcat(str1, str2);
    for (int i = 0; i < __strlen(res123); ++i) {
        assert(*(res123 + i) == *(cat123 + i));
    }

    free(res12);
    free(res13);
    free(res123);
}

void __testStringBookend() {
    char* str = "javascript";

    assert(endsWith(str, "script"));
    assert(endsWith(str, "t"));
    assert(endsWith(str, "javascript"));

    assert(startsWith(str, "jav"));
    assert(startsWith(str, "j"));
    assert(startsWith(str, "javascript"));

    assert(!endsWith(str, "java"));
    assert(!endsWith(str, "javascriptt"));
    assert(!endsWith(str, "jjavascript"));

    assert(!startsWith(str, "ipt"));
    assert(!startsWith(str, "javascriptt"));
    assert(!startsWith(str, "jjavascript"));
}

void __testStringIncludes() {
    char* str = "javascript";

    assert(strIncludes(str, "vasc"));
    assert(strIncludes(str, "t"));
    assert(strIncludes(str, "j"));

    assert(!strIncludes(str, "scriptt"));
    assert(!strIncludes(str, "jjava"));
    assert(!strIncludes(str, "vascz"));
}

void __testStringIndexOf() {
    char* str = "javascript_javascript";

    assert(strIndexOf(str, "vasc", 0) == 2);
    assert(strIndexOf(str, "t", 9) == 9);
    assert(strIndexOf(str, "java", 0) == 0);
    assert(strIndexOf(str, "java", 1) == 11);

    assert(strIndexOf(str, "scriptt", 0) == -1);
    assert(strIndexOf(str, "jjava", 0) == -1);
    assert(strIndexOf(str, "vascz", 0) == -1);
    assert(strIndexOf(str, "script", 16) == -1);
}

void __testStringLastIndexOf() {
    char* str = "javascript_javascript";

    assert(strLastIndexOf(str, "vasc", 18) == 13);
    assert(strLastIndexOf(str, "vasc", 9) == 2);
    assert(strLastIndexOf(str, "java", 20) == 11);
    assert(strLastIndexOf(str, "script", 16) == 4);

    assert(strLastIndexOf(str, "t", 4) == -1);
    assert(strLastIndexOf(str, "scriptt", 0) == -1);
    assert(strLastIndexOf(str, "jjava", 0) == -1);
    assert(strLastIndexOf(str, "vascz", 0) == -1);
}

void __testStringPad() {
    char* str = (char*)malloc(5 * sizeof(char));
    for (char ch = 'a'; ch <= 'd'; ++ch) {
        *(str + ch - 'a') = ch;
    }
    *(str + 4) = '\0';
    char* pad = "hi";

    padEnd(&str, 13, pad);
    char* expected1 = "abcdhihihihih";
    for (int i = 0; i < __strlen(str); ++i) {
        assert(*(str + i) == *(expected1 + i));
    }

    padStart(&str, 16, pad); 
    char* expected2 = "hihabcdhihihihih";
    for (int i = 0; i < __strlen(str); ++i) {
        assert(*(str + i) == *(expected2 + i));
    }

    free(str);
}

void __testStringRepeat() {
    char* abc = "abc";
    char* threeTimesAbc = "abcabcabc";

    char* res = repeat(abc, 3);
    for (int i = 0; i < __strlen(res); ++i) {
        assert(*(res + i) == *(threeTimesAbc + i));
    }

    free(res);
}

void __testStringTrim() {
    char* expectedTrim = "hello";

    char* str0 = "  hello    ";
    char* res = trim(str0);
    for (int i = 0; i < __strlen(res); ++i) {
        assert(*(res + i) == *(expectedTrim + i));
    }
    free(res);

    char* str1 = "hello    ";
    res = trim(str1);
    for (int i = 0; i < __strlen(res); ++i) {
        assert(*(res + i) == *(expectedTrim + i));
    }
    free(res);

    char* str2 = "  hello";
    res = trim(str2);
    for (int i = 0; i < __strlen(res); ++i) {
        assert(*(res + i) == *(expectedTrim + i));
    }
    free(res);

    char* str3 = "      ";
    res = trim(str3);
    assert(res == NULL);
}

void __testToCase() {
    char* str = "A12abcdEFGH34I";

    char* str0 = (char*)malloc(__strlen(str) + 1);
    for (int i = 0; i < __strlen(str); ++i) {
        *(str0 + i) = *(str + i);
    }

    char* toLowerRes = "a12abcdefgh34i";
    toLowerCase(str0);
    for (int i = 0; i < __strlen(str0); ++i) {
        assert(*(str0 + i) == *(toLowerRes + i));
    }

    char* str1 = (char*)malloc(__strlen(str) + 1);
    for (int i = 0; i < __strlen(str); ++i) {
        *(str1 + i) = *(str + i);
    }
    char* toUpperRes = "A12ABCDEFGH34I";
    toUpperCase(str1);
    for (int i = 0; i < __strlen(str1); ++i) {
        assert(*(str1 + i) == *(toUpperRes + i));
    }

}

void __testSubstrAndSlice() {
    const char* str = "abcdefgh";

    int start = 1;
    int end = 4;
    char* sub = substr(str, start, end);
    char* sli = strSlice(str, start, end);

    for (int i = start; i < end; ++i) {
        assert(*(str + i) == *(sub + i - start));
        assert(*(str + i) == *(sli + i - start));
    }
    free(sub);
    free(sli);

    start = 5;
    end = __strlen(str);
    sub = substr(str, start, end);
    sli = strSlice(str, start, end);

    for (int i = start; i < end; ++i) {
        assert(*(str + i) == *(sub + i - start));
    }
    free(sub);
    free(sli);

    start = 0;
    end = 1;
    sub = substr(str, start, end);
    sli = strSlice(str, start, end);
    assert(*(sub) == (char)'a');
    free(sub);
    free(sli);

    start = -5;
    end = -2;
    sli = strSlice(str, start, end);

    int size = __strlen(str);
    for (int i = size + start; i < size + end; ++i) {
        assert(*(str + i) == *(sub + i - (size + start)));
    }
    free(sli);
}

void __testStringSplit() {
    const char* str = "hello, this, is, some, random, sentence";
    const char* separator = ", ";
    char* expected[] = {
        "hello",
        "this",
        "is",
        "some",
        "random",
        "sentence"
    };

    char** res = strSplit(str, separator);
    for (int i = 0; i < 6; ++i) {
        assert(strEquals(expected[i], *(res + i)));
    }
    free(res);

    const char* str1 = ", hello,, , , , ,  this, is, some, random, sentence, ";
    res = strSplit(str, separator);
    for (int i = 0; i < 6; ++i) {
        assert(strEquals(expected[i], *(res + i)));
    }
    free(res);
}

void __testStringReplace() {
    const char* str = "The quick brown fox jumps over the lazy doggo. If the doggo reacted, was it really lazy?";
    const char* pattern = "doggo";
    const char* replacement0 = "cat";

    char* res = strReplace(str, pattern, replacement0, 0);
    const char* expected0 = "The quick brown fox jumps over the lazy cat. If the doggo reacted, was it really lazy?";
    assert(strEquals(res, expected0));
    free(res);

    const char* replacement1 = "elephant";
    res = strReplace(str, pattern, replacement1, 41);
    const char* expected1 = "The quick brown fox jumps over the lazy doggo. If the elephant reacted, was it really lazy?";
    assert(strEquals(res, expected1));
    free(res);
}