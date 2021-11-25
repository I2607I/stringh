#include "s21_string.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "errlist.h"

/**
 * @brief Searches for the first occurrence of the character (c) (an unsigned char)
 * in the first (n) bytes of the string pointed to, by the argument (str).
 *
 * @param str string which need to be searched to find a first occurance of "c"
 * @param c character which need to be found in "str"
 * @param n amount of bytes of "str" where "c" need to be found
 * @return void *
 */
void *s21_memchr(const void *str, int c, s21_size_t n) {
    void *returnable = S21_NULL;
    char *str_temp = (char *)str;
    if (str != S21_NULL && c > 0 && n > 0) {
        s21_size_t i = 0;
        if (s21_strlen(str) < n) n = s21_strlen(str);
        while (i < n && str_temp[i] != c) {
            i++;
        }
        if (str_temp[i] == c) {
            returnable = &str_temp[i];
        }
    }
    return returnable;
}

/**
 * @brief Compares the first n bytes of str1 and str2.
 *
 * @param str1 string which need to be compared with "str2"
 * @param str2 string which need to be compared with "str1"
 * @param n amount of bytes of strings which need to be compared
 * @return int 0 if equial; 1 if str1 > str2; -1 if str1 < str2;
 * if one of "str" is S21_NULL it's considered smaller, but equial if they are both are S21_NULL.
 */
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    int returnable = 0;
    char *str1_temp = (char *)str1;
    char *str2_temp = (char *)str2;
    if (str1_temp != S21_NULL && str2_temp != S21_NULL) {
        s21_size_t i = 0;
        while (i < n && str1_temp[i] == str2_temp[i]) {
            i++;
        }
        if (i != n && str1_temp[i] > str2_temp[i]) {
            returnable = 1;
        } else if (i != n && str1_temp[i] < str2_temp[i]) {
            returnable = -1;
        } else {
            returnable = 0;
        }
    } else if (str1_temp == S21_NULL && str2_temp != S21_NULL) {
        returnable = 1;
    } else if (str1_temp != S21_NULL && str2_temp == S21_NULL) {
        returnable = -1;
    }
    return returnable;
}

/**
 * @brief Copies n characters from src to dest.
 *
 * @param dest string which need to copy "src" to
 * @param src string which need to be copied to "dest"
 * @param n amount of bytes of "src" to be copied to "dest"
 * @return void *new string
 */
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    void *returnable = S21_NULL;
    char *dest_temp = (char *)dest;
    char *src_temp = (char *)src;
    s21_size_t len1 = s21_strlen(dest_temp);
    s21_size_t len2 = s21_strlen(src_temp);
    if (dest_temp == S21_NULL || src_temp == S21_NULL || len1 < len2) {
        returnable = S21_NULL;
    } else {
        if (len1 < n) n = len1;
        for (s21_size_t i = 0; i < n; i++) {
            dest_temp[i] = src_temp[i];
        }
        returnable = &dest_temp[0];
    }
    return returnable;
}

/**
 * @brief Another function to copy n characters from "src" to "dest".
 *
 * @param dest string which need to copy "src" to
 * @param src string which need to be copied to "dest"
 * @param n amount of bytes of "src" to be copied to "dest"
 * @return void *new string
 */
void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    void *returnable = S21_NULL;
    char *dest_temp = (char *)dest;
    char *src_temp = (char *)src;
    char *buffer = (char *)malloc(n * sizeof(char));
    if (dest_temp == S21_NULL || src_temp == S21_NULL || s21_strlen(dest_temp) < n || buffer == S21_NULL) {
        returnable = S21_NULL;
    } else {
        for (s21_size_t i = 0; i < n; i++) {
            buffer[i] = src_temp[i];
        }
        for (s21_size_t i = 0; i < n; i++) {
            dest_temp[i] = buffer[i];
        }
        returnable = &dest_temp[0];
    }
    free(buffer);
    return returnable;
}

/**
 * @brief Copies the character c (an unsigned char) to the first n
 * characters of the string pointed to, by the argument str.
 *
 * @param str string which need to be filled with "c"
 * @param c charcter to fill "str" with
 * @param n amount of bytes to fill with "c" inside "src"
 * @return char * sting filled with "c" inside "str" for "n" bytes
 */
void *s21_memset(void *str, int c, s21_size_t n) {
    char *returnable = S21_NULL;
    char *str_temp = (char *)str;
    if (str != S21_NULL && c > 0) {
        s21_size_t strIndex = s21_strlen(str) - 1;
        if (n > strIndex) n = strIndex;
        returnable = str_temp;
        while (n > 0) {
            *str_temp = (unsigned char)c;
            str_temp++;
            n--;
        }
    }
    return returnable;
}

/**
 * @brief Appends the string pointed to, by src to the end
 * of the string pointed to by dest.
 *
 * @param dest string where will be copied "src" to
 * @param src string which will be copied to "dest"
 * @return char * sting with "src" copied to "dest"
 */
char *s21_strcat(char *dest, const char *src) {
    char *returnable = S21_NULL;
    if (dest != S21_NULL && src != S21_NULL) {
        char *start = dest;
        while (*start != '\0') {
            start++;
        }
        while (*src != '\0') {
            *start++ = *src++;
        }
        *start = '\0';
        returnable = dest;
    }
    return returnable;
}

/**
 * @brief Appends the string pointed to, by src to the end of the
 * string pointed to, by dest up to n characters long.
 *
 * @param dest string where will be copied "src" to
 * @param src string which will be copied to "dest"
 * @param n amount of bytes to be copied
 * @return char * sting with "n" bytes of "src" copied to "dest"
 */
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    char *returnable = S21_NULL;
    s21_size_t zero = 0;  // because "comparison of unsigned expression >= 0 is always true"
    if (dest != S21_NULL && src != S21_NULL && n >= zero) {
        s21_size_t len = s21_strlen(src);
        if (n > len) n = len;
        char *tmpdst = dest;
        while (*tmpdst != '\0') {
            tmpdst++;
        }
        while (n-- && *src != '\0') {
            *tmpdst++ = *src++;
        }
        *tmpdst = '\0';
        returnable = dest;
    }
    return returnable;
}

/**
 * @brief Searches for the first occurrence of the character c
 * (an unsigned char) in the string pointed to, by the argument str.
 *
 * @param str string which need to be searched to find "c"
 * @param c characher which first occurance have to be found in "str"
 * @return char * string which starts from "c" in "str"
 */
char *s21_strchr(const char *str, int c) {
    char *returnable = S21_NULL;
    char *str_temp = (char *)str;
    if (str != S21_NULL && c > 0) {
        s21_size_t i = 0, strLen = s21_strlen(str);
        while (i < strLen && str_temp[i] != c) {
            i++;
        }
        if (str_temp[i] == c) {
            returnable = &str_temp[i];
        }
    }
    return returnable;
}

/**
 * @brief Compares the string pointed to, by str1 to the string pointed to by str2.
 *
 * @param str1 string which need to be compared with "str2"
 * @param str2 string which need to be compared with "str1"
 * @return int 0 if equial; 1 if str1 > str2; -1 if str1 < str2;
 * if one of "str" is S21_NULL it's considered smaller, but equial if they are both are S21_NULL.
 */
int s21_strcmp(const char *str1, const char *str2) {
    int returnable = 0;
    if (str1 != S21_NULL && str2 != S21_NULL) {
        s21_size_t len1 = s21_strlen(str1);
        s21_size_t len2 = s21_strlen(str2);
        if (len2 > len1) {
            returnable = -str2[len1];
        } else if (len2 < len1) {
            len1 = len2;
            returnable = str1[len2];
        }
        s21_size_t i = 0;
        while (i < len1 && str1[i] == str2[i]) {
            i++;
        }
        if (i < len1 && str1[i] > str2[i]) {
            returnable = 1;
        } else if (i < len1 && str1[i] < str2[i]) {
            returnable = -1;
        }
    } else if (str1 == S21_NULL && str2 != S21_NULL) {
        returnable = 1;
    } else if (str1 != S21_NULL && str2 == S21_NULL) {
        returnable = -1;
    }
    return returnable;
}

/**
 * @brief Compares at most the first n bytes of str1 and str2.
 *
 * @param str1 string which need to be compared with "str2"
 * @param str2 string which need to be compared with "str1"
 * @return int 0 if equial; 1 if str1 > str2; -1 if str1 < str2;
 * if one of "str" is S21_NULL it's considered smaller, but equial if they are both are S21_NULL.
 */
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    int returnable = 0;
    if (str1 != S21_NULL && str2 != S21_NULL) {
        s21_size_t len1 = s21_strlen(str1);
        s21_size_t len2 = s21_strlen(str2);
        if (len2 > len1) {
            returnable = -str2[len1];
        } else if (len2 < len1) {
            len1 = len2;
            returnable = str1[len2];
        }
        s21_size_t i = 0;
        if (n > len1) n = len1;
        while (i < n && str1[i] == str2[i]) {
            i++;
        }
        if (i < len1 && str1[i] > str2[i]) {
            returnable = 1;
        } else if (i < len1 && str1[i] < str2[i]) {
            returnable = -1;
        }
    } else if (str1 == S21_NULL && str2 != S21_NULL) {
        returnable = 1;
    } else if (str1 != S21_NULL && str2 == S21_NULL) {
        returnable = -1;
    }
    return returnable;
}

/**
 * @brief Copies the string pointed to, by src to dest.
 *
 * @param dest string which need to copy "src" to
 * @param src string which need to be copied to "dest"
 * @return char * string "src" copied till "\\0" appear
 */
char *s21_strcpy(char *dest, const char *src) {
    char *returnable = S21_NULL;
    s21_size_t i = 0;
    if (src != S21_NULL && dest != S21_NULL) {
        while (src[i] != '\0') {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
        returnable = dest;
    }
    return returnable;
}

/**
 * @brief Copies up to n characters from the string pointed to, by src to dest.
 *
 * @param dest string which need to copy "src" to
 * @param src string which need to be copied to "dest"
 * @param n amount of char to be copied from "src" to "dest"
 * @return char * string "src" copied till n-th character appear
 */
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    char *returnable = S21_NULL;
    s21_size_t i = 0;
    if (src != S21_NULL && dest != S21_NULL) {
        s21_size_t srcLen = s21_strlen(src);
        if (n > srcLen) n = srcLen;
        while (i != n) {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
        returnable = dest;
    }
    return returnable;
}

/**
 * @brief Calculates the length of the initial segment of str1
 * which consists entirely of characters not in str2.
 *
 * @param str1 string which need to be searched at the start for symbols of "str2"
 * @param str2 string of symbols which have not to be found at the start of "str1"
 * @return s21_size_t amount of symbols of "str1" weren't found matching with "str2"
 */
s21_size_t s21_strcspn(const char *str1, const char *str2) {
    s21_size_t len = 0, str1Index = 0, str2Index = 0;
    if (str1 != S21_NULL && str2 != S21_NULL) {
        for (; str1[str1Index] != str2[str2Index]; str2Index++) {
            if (str2[str2Index] == '\0') {
                len += 1;
                str1Index += 1;
                str2Index = 0;
            }
        }
    }
    return len;
}

/**
 * @brief Searches an internal array for the error number "errnum"
 * and returns a pointer to an error message string.
 *
 * @param errnum code of error
 * @return char * string with error message
 */
char *s21_strerror(int errnum) {
    static char *array[] = errlist;
    static char *err;
    err = array[errnum];
    static char buffer[1024];
#if defined(__APPLE__)
    snprintf(buffer, sizeof(buffer), "Unknown error: %d", (int)errnum);
#elif defined(__linux__)
    snprintf(buffer, sizeof(buffer), "Unknown error %d", (int)errnum);
#endif
    if (err == S21_NULL || errnum > MAX_ERROR || errnum < 0) {
        err = buffer;
    }
    return err;
}

/**
 * @brief Computes the length of the string str up to but not including the terminating S21_NULL character.
 *
 * @param str string which need to count character in
 * @return s21_size_t string length without "\\0"; return length 0 if str is S21_NULL.
 */
s21_size_t s21_strlen(const char *str) {
    s21_size_t i = 0;
    if (str != S21_NULL) {
        for (i = 0; str[i] != '\0'; i++) {
        }
    }
    return i;
}

/**
 * @brief Finds the first character in the string str1
 * that matches any character specified in str2.
 *
 * @param str1 string which need to be searched to find one out of symbols of "str2"
 * @param str2 string contains symbols had to be compared with characters in "str1"
 * @return char * string started with found character
 */
char *s21_strpbrk(const char *str1, const char *str2) {
    char *returnable = S21_NULL;
    if (str1 != S21_NULL && str2 != S21_NULL) {
        s21_size_t str1Index = 0, str2Index = 0;
        for (; str1[str1Index] && str1[str1Index] != str2[str2Index]; str2Index++) {
            if (str2[str2Index] == '\0') {
                str1Index++;
                str2Index = -1;
            }
        }
        if (str1[str1Index] != '\0') {
            returnable = (char *)&str1[str1Index];
        }
    }
    return returnable;
}

/**
 * @brief Searches for the last occurrence of the character c
 * (an unsigned char) in the string pointed to by the argument str.
 *
 * @param str string which need to be searched to find "c"
 * @param c characher which last occurance have to be found in "str"
 * @return char * string which starts from "c" in "str"
 */
char *s21_strrchr(const char *str, int c) {
    char *returnable = S21_NULL;
    if (str != S21_NULL && c > 0) {
        s21_size_t strIndex = s21_strlen(str) - 1;
        while (strIndex > 0 && str[strIndex] != c) {
            strIndex--;
        }
        if (str[strIndex] == c) {
            returnable = (char *)&str[strIndex];
        }
    }
    return returnable;
}

/**
 * @brief Calculates the length of the initial segment of str1
 * which consists entirely of characters in str2.
 *
 * @param str1 string which need to be searched at the start for symbols of "str2"
 * @param str2 string of symbols which have to be found at the start of "str1"
 * @return s21_size_t amount of symbols of "str1" were found matching with "str2"
 */
s21_size_t s21_strspn(const char *str1, const char *str2) {
    s21_size_t len = 0, str1Index = 0, str2Index = 0;
    if ((str1 != S21_NULL) || (str2 != S21_NULL)) {
        while (str2[str2Index] != '\0') {
            if (str1[str1Index] == str2[str2Index]) {
                str1Index++;
                str2Index = -1;  // because it's incremented the next
                len++;
            }
            str2Index++;
        }
    }
    return len;
}

/**
 * @brief Finds the first occurrence of the entire string needle
 * (not including the terminating S21_NULL character) which appears in the string haystack.
 *
 * @param haystack string which need to be searched to found "needle" in
 * @param needle string which need to be found inside "haystack"
 * @return char * string starting where "needle" starts inside "haystack" from
 */
char *s21_strstr(const char *haystack, const char *needle) {
    char *returnable = S21_NULL;
    if (haystack != S21_NULL && needle != S21_NULL) {
        s21_size_t hayLen = s21_strlen(haystack);
        s21_size_t indx = 0;
        for (s21_size_t i = 0; i < hayLen && returnable == S21_NULL; i++) {
            if (haystack[i] == needle[0]) {
                while (needle[indx] && haystack[i + indx] && haystack[i + indx] == needle[indx]) {
                    indx++;
                }
                indx--;
                if (haystack[i + indx] == needle[indx] && needle[indx + 1] == '\0') {
                    returnable = (char *)&haystack[i];
                }
                indx = 0;
            }
        }
    }
    return returnable;
}

/**
 * @brief Breaks string str into a series of tokens separated by delim.
 *
 * @param str string which need to be broken into tokens
 * @param delim string which contains symbols as a separators
 * @return char * string with symbols of "str" till one out of "delim" symbols appear.
 * Use S21_NULL as a "str" after first application to get next tokens of "str"
 */
char *s21_strtok(char *str, const char *delim) {
    static char *last = S21_NULL;
    char *returnable = S21_NULL;
    if (str == S21_NULL && delim != S21_NULL) {
        str = last;
    }
    if (str != S21_NULL && delim != S21_NULL) {
        s21_size_t str1Index = 0, str2Index = 0;
        for (; str[str1Index] && str[str1Index] != delim[str2Index]; str2Index++) {
            if (delim[str2Index] == '\0') {
                str1Index++;
                str2Index = -1;
            }
        }
        if (str[str1Index] == '\0' || str[str1Index + 1] == '\0') {
            str[str1Index] = '\0';
            last = S21_NULL;
        } else {
            str[str1Index] = '\0';
            last = (char *)&str[str1Index + 1];
        }
        returnable = str;
    }
    return returnable;
}

/**
 * @brief Returns a copy of string (str) converted to uppercase.
 * In case of any error, return S21_NULL.
 *
 * @param str string which need to be converted to uppercase
 * @return void *new string ATTENTION!!! MALLOC IS USED TO CREATE NEW STRING!!!
 * */
void *s21_to_upper(const char *str) {
    void *returnable = S21_NULL;
    if (str != S21_NULL) {
        s21_size_t i = 0, j = 0;
        for (i = 0; str[i] != '\0'; i++) {
        }
        char *copyStr = (char *)malloc(i * sizeof(char) + 1);

        while (j < i) {
            if (str[j] > 96 && str[j] < 123) {
                copyStr[j] = str[j] - 32;
                j++;
            } else {
                copyStr[j] = str[j];
                j++;
            }
        }
        copyStr[i + 1] = '\0';
        returnable = copyStr;
    }
    return returnable;
}

/**
 * @brief Returns a copy of string (str) converted to lowercase.
 * In case of any error, return S21_NULL.
 *
 * @param str string which need to be converted to lowercase
 * @return void *new string ATTENTION!!! MALLOC IS USED TO CREATE NEW STRING!!!
 */
void *s21_to_lower(const char *str) {
    void *returnable = S21_NULL;
    if (str != S21_NULL) {
        s21_size_t i = 0, j = 0;
        for (i = 0; str[i] != '\0'; i++) {
        }
        char *copyStr = (char *)malloc(i * sizeof(char) + 1);

        while (j < i) {
            if (str[j] > 64 && str[j] < 91) {
                copyStr[j] = str[j] + 32;
                j++;
            } else {
                copyStr[j] = str[j];
                j++;
            }
        }
        copyStr[i + 1] = '\0';
        returnable = copyStr;
    }
    return returnable;
}

/**
 * @brief Returns a new string in which a specified string (str) is inserted at a
 * specified index position (start_index) in the given string (src).
 * In case of any error, return S21_NULL.
 *
 * @param src string which need to paste "str" in
 * @param str string which need to be pasted into "src"
 * @param start_index number of place from where "str" need to be put into "src"
 * @return void *new string ATTENTION!!! MALLOC IS USED TO CREATE NEW STRING!!!
 */
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    void *returnable = S21_NULL;
    s21_size_t srcLen = 0;
    s21_size_t strLen = 0;
    char strValid = src != S21_NULL && str != S21_NULL;
    if (strValid == 1) {
        for (srcLen = 0; src[srcLen] != '\0'; srcLen++) {
        }
        for (strLen = 0; str[strLen] != '\0'; strLen++) {
        }
    }
    s21_size_t zero = 0;
    char indexValid = start_index >= zero && start_index <= srcLen;
    if (strValid == 1 && indexValid == 1) {
        char *buffer = (char *)malloc((srcLen + strLen) * sizeof(char) + 1);
        if (buffer != S21_NULL) {
            for (s21_size_t i = 0; i < start_index; i++) {
                buffer[i] = src[i];
            }
            for (s21_size_t j = 0; j < strLen; j++) {
                buffer[j + start_index] = str[j];
            }
            for (s21_size_t k = 0; k < srcLen - start_index; k++) {
                buffer[k + start_index + strLen] = src[k + start_index];
            }
            buffer[srcLen + strLen + 1] = '\0';
            returnable = buffer;
        }
    }
    return returnable;
}

/**
 * @brief Returns a new string in which all leading and trailing occurrences of a set of
 * specified characters (trim_chars) from the given string (src) are removed. In case of
 * any error, return S21_NULL.
 *
 * @param src string which need to remove symbols defined in "trim_chars" in
 * @param trim_chars string which contains symbols to remove from "src"
 * @return void *new string ATTENTION!!! MALLOC IS USED TO CREATE NEW STRING!!!
 */
void *s21_trim(const char *src, const char *trim_chars) {
    void *returnable = S21_NULL;
    s21_size_t startIndex = 0, endIndex = 0, i = 0;
    if (src != S21_NULL && trim_chars != S21_NULL) {
        for (endIndex = 0; src[endIndex] != '\0'; endIndex++) {
        }
        endIndex -= 1;

        while (trim_chars[i] != '\0') {
            if (src[startIndex] == trim_chars[i]) {
                startIndex += 1;
                i = -1;
            }
            i++;
        }

        i = 0;
        while (trim_chars[i] != '\0') {
            if (src[endIndex] == trim_chars[i]) {
                endIndex -= 1;
                i = -1;
            }
            i++;
        }

        if (endIndex - startIndex > 0) {
            char *copyStr = (char *)malloc((endIndex - startIndex) * sizeof(char) + 1);
            if (copyStr != S21_NULL) {
                for (i = startIndex; i <= endIndex; i++) {
                    copyStr[i - startIndex] = src[i];
                }
                copyStr[endIndex] = '\0';
                returnable = copyStr;
            }
        }
    }
    return returnable;
}

int s21_sprintf(char *output, char *str, ...) {
    va_list ap;        /* point on next unnamed argument */
    va_start(ap, str); /* set 'ap' on 1-st unnamed argument */
    int out_len =
        0;  // массив, куда осуществляется вывод, он должен задаваться как аргумент s21_sprintf, но пока так
    for (char *p = str; *p; p++) {
        if (*p != '%') {
            out_len++;
            output[s21_strlen(output)] = *p;
            continue;
        }
        char flag1 = -1;  // задаём значения подспецификаторов по умолчанию
        char flag3 = -1;
        int width = -1;
        int prec = -1;
        char lenght = -1;

        ++p;  // переключаемся на следующий символ и если он один из флагов, то считываем его
        while (1) {  // цикл бесконечный, так как флагов можно ставить хоть сколько
            if (*p == '-' || *p == '+' || *p == ' ') {
                if (*p == '+' || *p == ' ') {
                    if (flag1 == '+')
                        flag1 = '+';
                    else
                        flag1 = *p;
                }
                if (*p == '-') {
                    flag3 = *p;
                }
                ++p;
            } else {
                break;
            }
        }
        if (*p == '*') {  // следующий символ, и если он ширина, то считываем её. Один раз проверяем наличие
                          // шиирны, так как ширину можно указывать только один раз, в отличии от флагов
            width = va_arg(ap, int);
            ++p;
        }

        if (*p == '.' && *(p + 1) == '*') {  // следующий символ, и если он точность, то считываем его.
            prec = va_arg(ap, int);
            p += 2;
        }

        if (*p == 'h' || *p == 'l') {
            lenght = *p;
            ++p;
        }

        switch (*p) {
            case 'c': {
                char ival;
                ival = (char)va_arg(ap, int);
                if (flag3 != '-' && width != -1) {
                    for (int i = 0; i < width - 1; ++i) {
                        output[s21_strlen(output)] = ' ';
                        out_len++;
                    }
                }
                output[s21_strlen(output)] = ival;
                out_len++;
                if (flag3 == '-' && width != -1) {
                    for (int i = 0; i < width - 1; ++i) {
                        output[s21_strlen(output)] = ' ';
                        out_len++;
                    }
                }
                break;
            }
            case 'u': {
                unsigned long int ival = 0;
                if (lenght == 'l')
                    ival = (unsigned long int)va_arg(ap, unsigned long int);
                else
                    ival = (unsigned long int)va_arg(ap, unsigned int);
                char buf[21] = "";
                IntStr(buf, 1, ival, -1, flag3, width, prec);
                out_len += s21_strlen(buf);
                s21_strcat(output, buf);
                break;
            }
            case 'd': {
                long int ival = 0;
                if (lenght == 'l')
                    ival = (long int)va_arg(ap, long int);
                else
                    ival = (long int)va_arg(ap, int);
                char buf[50] = "";
                IntStr(buf, 1, ival, flag1, flag3, width, prec);
                out_len += s21_strlen(buf);
                s21_strcat(output, buf);
                break;
            }
            case 'i': {
                long int ival = 0;
                if (lenght == 'l')
                    ival = (long int)va_arg(ap, long int);
                else
                    ival = (long int)va_arg(ap, int);
                char buf[50] = "";
                IntStr(buf, 1, ival, flag1, flag3, width, prec);
                out_len += s21_strlen(buf);
                s21_strcat(output, buf);
                break;
                break;
            }
            case 'f': {
                double dval = 0.;
                dval = va_arg(ap, double);
                char buf[50] = "";
                DoubleStr(buf, dval, flag1, flag3, width, prec);
                out_len += s21_strlen(buf);
                s21_strcat(output, buf);
                break;
            }
            case 's': {
                char *buf = malloc(sizeof(char));
                int k = 0;
                for (char *sval = va_arg(ap, char *); *sval; sval++) {
                    k++;
                    if (prec < k && prec > 0) continue;
                    void *bufff = realloc(buf, k * sizeof(char));
                    if (S21_NULL == bufff) {
                        free(buf);
                    } else {
                        buf = bufff;
                    }
                    *(buf + k - 1) = *sval;
                    out_len++;
                }
                int l = s21_strlen(buf);
                if (flag3 != '-') {
                    for (int i = 0; i < width - l; ++i) {
                        s21_strcat(output, " ");
                        out_len++;
                    }
                }
                s21_strcat(output, buf);
                // free(buf);
                if (flag3 == '-') {
                    for (int i = 0; i < width - l; ++i) {
                        s21_strcat(output, " ");
                        out_len++;
                    }
                }
                break;
            }
            case '%': {
                s21_strcat(output, "%");
                out_len++;
                break;
            }
            default: {
                output[s21_strlen(output)] = *p;
                break;
            }
        }
    }
    va_end(ap); /* clean all */
    return out_len;
}

char *IntStr(char *buf, int is_int, long int n, char flag, char flag3, int width, int prec) {
    // char *index = buf;
    int len = LenInt(n);
    int fprec = 0;  // длина числа
    if (prec != -1 && is_int == 0) {
        fprec = prec + 1;
    }
    int tr_len = len;
    if (prec != -1 && prec > len && is_int == 1)  // если задана точность, то длина числа будет равна точности
        len = prec;
    int full_len = len;
    int i = 0;
    int j = 0;
    if ((flag == ' ' && n >= 0) || (flag == '+' && n > 0) || n < 0)
        // если заданы флаги пробел и + или число отрицательное, то фактическая длина больше на
        // единицу, так как нужно печатать плюс, минус или пробел
        full_len++;
    if (flag3 == -1 &&
        width != -1) {  // если задана ширина и нет флага 0 или -, то печатаем сначала пробелы, затем число
        for (; j < width - full_len - fprec; ++j) {
            *(buf + j) = ' ';
        }
    }
    if (flag == ' ' && n >= 0) {  // если если флаг пробел, то перед числом ставим пробел
        buf += j;
        *(buf++) = ' ';
        buf -= j;
    }
    if (flag == '+' && n > 0) {  // если если флаг +, то перед положительным числом ставим плюс
        buf += j;
        *(buf++) = '+';
        buf -= j;
    }
    if (n < 0) {  // если число отрицательно, то перед ним печатаем минус
        buf += j;
        *(buf++) = '-';
        buf -= j;
        n = -n;
    }
    // если число ноль, то печатаем ноль (ноль приходится отдельно обрабатывать, иначе не работает)
    if (n == 0) {
        buf += j;
        *(buf++) = '0';
        buf -= j;
    }
    while (n > 0) {  // непосредственно вывод самого числа
        *(buf + j + len - i - 1) = (n % 10) | '0';
        n /= 10;
        i++;
    }
    if (is_int == 1) {
        for (int h = 0; h < prec - tr_len; h++) {  // а это, если задана точность, вывод дополнительных нулей
            *(buf + j + len - i - 1) = '0';
            i++;
        }
    }
    // если флаг - и задана ширина, то после числа пробелы печатаем
    if (flag3 == '-' && width != -1 && is_int == 1) {
        for (; j < width - full_len - fprec; ++j) *(buf + len - 1 + j + 1) = ' ';
    }
    return (buf);
}

int LenInt(int n) {
    int len = 0;
    if (n < 0) n = n * (-1);
    while (n > 0) {
        len++;
        n /= 10;
    }
    return len;
}

char *DoubleStr(char *buf, long double n, char flag, char flag3, int width, int prec) {
    int len = LenInt((int)n);
    if ((flag == ' ' && n >= 0) || (flag == '+' && n > 0) ||
        n < 0)  // если заданы флаги пробел и + или число отрицательное, то фактическая длина больше на
                // единицу, так как нужно печатать плюс, минус или пробел
        len++;
    if (prec == -1) prec = 6;
    IntStr(buf, 0, (int)n, flag, flag3, width, prec);
    if (prec != 0)
        s21_strcat(buf, ".");
    else
        s21_strcat(buf, " ");
    if (n < 0) {
        n = n * (-1);
    }
    n = n - (long int)n;

    for (int i = 0; i < prec; i++) {
        n *= 10;
        buf[s21_strlen(buf)] = n + '0';
        n = n - (int)n;
    }
    if (flag3 == '-') {
        for (int i = 0; i < width - (len + prec + 1); i++) buf[s21_strlen(buf)] = ' ';
    }
    return buf;
}
