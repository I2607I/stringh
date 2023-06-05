#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errlist.h"
#include "string.h"

START_TEST(s21_memchr_test) {
    char testStr[] = "ABCDE";
    char *testNULL = S21_NULL;
    int boolean = 0;

    boolean = s21_memcmp(s21_memchr(testStr, 'B', 5), memchr(testStr, 'B', 5), 4) == 0;
    ck_assert_msg(boolean, "FAILED with \"B\" inside \"ABCDE\"");
    boolean = s21_memcmp(s21_memchr(testStr, 'B', 10), memchr(testStr, 'B', 3), 2) == 0;
    ck_assert_msg(boolean, "FAILED with exceed of bytes");
    boolean = s21_memcmp(s21_memchr(testStr, 'C', 4), memchr(testStr, 'C', 4), 5) == 0;
    ck_assert_msg(boolean, "FAILED with case with no match");
    boolean = s21_memchr(testNULL, 'E', 4) == S21_NULL;
    ck_assert_msg(boolean, "FAILED with S21_NULL string");
}
END_TEST

START_TEST(s21_memcmp_test) {
    char testStr1[] = "ABCDE";
    char testStr2[] = "ABC";
    char testStr3[] = "ABCDD";
    char *testNULL = S21_NULL;
    int boolean = 0;

    boolean = s21_memcmp(testStr1, testStr1, 5) == memcmp(testStr1, testStr1, 5);
    ck_assert_msg(boolean, "FAILED with equal string");
    boolean = s21_memcmp(testStr1, testStr2, 5) == 1;  // There is undefined behaviour in memcmp()
    ck_assert_msg(boolean, "FAILED with str2 shorter than str1");
    boolean = s21_memcmp(testStr2, testStr1, 5) == -1;  // There is undefined behaviour in memcmp()
    ck_assert_msg(boolean, "FAILED with str1 shorter than str2");
    boolean = s21_memcmp(testStr1, testStr3, 5) == memcmp(testStr1, testStr3, 5);
    ck_assert_msg(boolean, "FAILED with bite in str2 lower than in str1");
    boolean = s21_memcmp(testStr3, testStr1, 5) == memcmp(testStr3, testStr1, 5);
    ck_assert_msg(boolean, "FAILED with bite in str1 lower than in str2");
    boolean = s21_memcmp(testStr1, testStr1, 50) == memcmp(testStr1, testStr1, 5);
    ck_assert_msg(boolean, "FAILED with exceed of bytes");
    boolean = s21_memcmp(testNULL, testNULL, 50) == 0;
    ck_assert_msg(boolean, "FAILED with S21_NULL string");
}
END_TEST

START_TEST(s21_memcpy_test) {
    char testStr1[] = "ABCDE";
    char testStr2[] = "ABC";
    char testStr3[] = "GREK";
    char *testNULL = S21_NULL;
    int boolean = 0;

    boolean = s21_memcmp(s21_memcpy(testStr1, testStr3, 4), memcpy(testStr1, testStr3, 4), 7) == 0;
    ck_assert_msg(boolean, "FAILED with copying \"GREK\" into \"ABCDE\"");
    boolean = s21_memcpy(testStr2, testStr1, 4) == S21_NULL;  // There is a segmentation fault in memcpy()
    ck_assert_msg(boolean, "FAILED with dest shorter than str2");
    boolean = s21_memcpy(testStr2, testNULL, 1) == S21_NULL;  // There is a segmentation fault in memcpy()
    ck_assert_msg(boolean, "FAILED with S21_NULL string");
}
END_TEST

START_TEST(s21_memmove_test) {
    char testStr1[] = "ABCDE";
    char testStr3[] = "GREK";
    int boolean = 0;

    boolean = s21_memmove(testStr1, testStr3, 4) == memmove(testStr1, testStr3, 4);
    ck_assert_msg(boolean, "FAILED with copying \"GREK\" into \"ABCDE\"");
    boolean = s21_memmove(testStr1, testStr3, 7) == S21_NULL;  // There is undefined behaviour in memmove()
    ck_assert_msg(boolean, "FAILED with copying \"GREK\" into \"ABCDE\"");
}
END_TEST

START_TEST(s21_memset_test) {
    unsigned char src[] = "1234567890";  // 1111167890
    s21_memset(src, '1', 5);
    int boolean = 0;

    boolean = s21_strcmp(s21_memset(src, '1', 5), memset(src, '1', 5)) == 0;
    ck_assert_msg(boolean, "FAIL - missing \"1\" 5 times in \"1234567890\"");
    boolean = s21_memset(src, 'g', 3) == memset(src, 'g', 3);
    ck_assert_msg(boolean, "FAIL - missing \"g\" 3 times in \"1234567890\"");
    boolean = s21_memset(src, '0', 8) == memset(src, '0', 8);
    ck_assert_msg(boolean, "FAIL - missing \"0\" 8 times in \"1234567890\"");
}
END_TEST

START_TEST(s21_strcat_test) {
    char dest[20] = "Go to ";
    char src[] = "home";
    char *testNULL = S21_NULL;
    int boolean = 0;

    boolean = s21_strcmp(s21_strcat(dest, src), strcat(dest, src)) == 0;
    ck_assert_msg(boolean, "FAIL - S21 lib dest != STD lib dest");
    boolean = s21_strcat(dest, testNULL) == S21_NULL;
    ck_assert_msg(boolean, "FAIL - S21_NULL string");
}
END_TEST

START_TEST(s21_strncat_test) {
    char dest[120] = "Go to ";
    char src[] = "home";
    char *testNULL = S21_NULL;
    int boolean = 0;

    boolean = s21_strncat(dest, testNULL, 5) == S21_NULL;
    ck_assert_msg(boolean, "FAIL - with S21_NULL string");
    boolean = s21_strcmp(s21_strncat(dest, src, 3), strncat(dest, src, 3)) == 0;
    ck_assert_msg(boolean, "FAIL - S21lib dest != STDlib dest - dest doesnt include 3 chars of src");
    boolean = s21_strcmp(s21_strncat(dest, src, 4), strncat(dest, src, 4)) == 0;
    ck_assert_msg(boolean, "FAIL - S21lib dest != STDlib dest - dest doesnt include 4 chars of src");
    boolean = s21_strcmp(s21_strncat(dest, src, 1), strncat(dest, src, 1)) == 0;
    ck_assert_msg(boolean, "FAIL - S21lib dest != STDlib dest - dest doesnt include 3 chars of src");
}
END_TEST

START_TEST(s21_strchr_test) {
    char str[] = "School 21";
    int boolean = 0;
    char *testNULL = S21_NULL;

    char *first = s21_strchr(str, 'S');
    char *second = strchr(str, 'S');
    boolean = s21_strcmp(first, second) == 0;
    ck_assert_msg(boolean, "FAIL - with \"S\" inside \"School 21\"");

    first = s21_strchr(str, '1');
    second = strchr(str, '1');
    boolean = s21_strcmp(first, second) == 0;
    ck_assert_msg(boolean, "FAIL - with \"1\" inside \"School 21\"");

    first = s21_strchr(str, '2');
    second = strchr(str, '2');
    boolean = s21_strcmp(first, second) == 0;
    ck_assert_msg(boolean, "FAIL - with \"2\" inside \"School 21\"");

    first = s21_strchr(testNULL, '2');
    boolean = first == S21_NULL;
    ck_assert_msg(boolean, "FAIL - with S21_NULL string");

    first = s21_strchr(testNULL, -20);
    boolean = first == S21_NULL;
    ck_assert_msg(boolean, "FAIL - with S21_NULL string");
}
END_TEST

START_TEST(s21_strcmp_test) {
    char *str1 = "12345";
    char *str2 = "12344";
    char *testNULL = S21_NULL;
    ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));
    ck_assert_int_eq(s21_strcmp(str1, str1), strcmp(str1, str1));
    char *str3 = "123456789";
    ck_assert_int_eq(s21_strcmp(str1, str3), strcmp(str1, str3));
    char *str4 = "";
    char *str5 = " ";
    ck_assert_int_eq(s21_strcmp(str4, str4), strcmp(str4, str4));
    ck_assert_int_eq(s21_strcmp(str4, str5), strcmp(str4, str5));
    char *str6 = "1234";
    ck_assert_int_eq(s21_strcmp(str6, testNULL), -1);
    ck_assert_int_eq(s21_strcmp(str6, testNULL), -1);
}
END_TEST

START_TEST(s21_strncmp_test) {
    char *str1 = "12345";
    char *str2 = "12344";
    char *testNULL = S21_NULL;
    ck_assert_int_eq(s21_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
    ck_assert_int_eq(s21_strncmp(str1, str1, 5), strncmp(str1, str1, 5));
    char *str3 = "123456789";
    ck_assert_int_eq(s21_strncmp(str1, str3, 9), strncmp(str1, str3, 9));
    char *str4 = "";
    char *str5 = " ";
    ck_assert_int_eq(s21_strncmp(str4, str4, 0), strncmp(str4, str4, 0));
    ck_assert_int_eq(s21_strncmp(str4, str5, 1), strncmp(str4, str5, 1));
    char *str6 = "1234";
    ck_assert_int_eq(s21_strncmp(str6, testNULL, 2), -1);
    ck_assert_int_eq(s21_strncmp(str6, testNULL, 2), -1);
}
END_TEST

START_TEST(s21_strcpy_test) {
    char testStr1[20] = "ABCDE";
    char testStr2[10] = "ABC";
    char testStr3[] = "GREK";
    char *testNULL = S21_NULL;
    int boolean = 0;

    boolean = s21_strcmp(s21_strcpy(testStr1, testStr3), strcpy(testStr1, testStr3)) == 0;
    ck_assert_msg(boolean, "FAILED with copying \"GREK\" into \"ABCDE\"");
    boolean = s21_strcpy(testNULL, testStr1) == S21_NULL;  // There is a segmentation fault in memcpy()
    ck_assert_msg(boolean, "FAILED S21_NULL string as dest");
    boolean = s21_strcpy(testStr2, testNULL) == S21_NULL;  // There is a segmentation fault in memcpy()
    ck_assert_msg(boolean, "FAILED with S21_NULL string as src");
}
END_TEST

START_TEST(s21_strncpy_test) {
    char testStr1[20] = "ABCDE";
    char testStr2[] = "ABC";
    char testStr3[] = "GREK";
    char *testNULL = S21_NULL;
    int boolean = 0;

    boolean = s21_strcmp(s21_strncpy(testStr1, testStr3, 3), strncpy(testStr1, testStr3, 3)) == 0;
    ck_assert_msg(boolean, "FAILED with copying \"GREK\" into \"ABCDE\"");
    boolean = s21_strncpy(testNULL, testStr1, 5) == S21_NULL;  // There is a segmentation fault in memcpy()
    ck_assert_msg(boolean, "FAILED S21_NULL string as dest");
    boolean = s21_strncpy(testStr2, testNULL, 6) == S21_NULL;  // There is a segmentation fault in memcpy()
    ck_assert_msg(boolean, "FAILED with S21_NULL string as src");
}
END_TEST

START_TEST(s21_strcspn_test) {
    char *test = "string for testing 123";
    char *test2 = "231";
    char *testNULL = S21_NULL;

    ck_assert_int_eq(s21_strcspn(test, test2), strcspn(test, test2));
    ck_assert_int_eq(s21_strcspn("123456789", "987"), strcspn("123456789", "987"));
    ck_assert_int_eq(s21_strcspn("123456789", " "), strcspn("123456789", " "));
    ck_assert_int_eq(s21_strcspn(" ", " "), strcspn(" ", " "));
    ck_assert_int_eq(s21_strcspn("123456789", "\n"), strcspn("123456789", "\n"));
    ck_assert_int_eq(s21_strcspn("123456789", testNULL), 0);
}
END_TEST

START_TEST(s21_strerror_test) {
    for (int i = 1; i <= MAX_ERROR; i++) {
        ck_assert_str_eq(s21_strerror(i), strerror(i));
    }
}
END_TEST

START_TEST(s21_strlen_test) {
    char *str = "Test string";
    ck_assert_int_eq(s21_strlen(str), strlen(str));
    ck_assert_int_eq(s21_strlen("55"), strlen("55"));
    ck_assert_int_eq(s21_strlen(""), strlen(""));
    ck_assert_int_eq(s21_strlen(" "), strlen(" "));
    ck_assert_int_eq(s21_strlen("\n"), strlen("\n"));
    ck_assert_int_eq(s21_strlen("How is\0this is a string"), strlen("How is\0this is a string"));
}
END_TEST

START_TEST(s21_strpbrk_test) {
    char *test = "string for testing 123";
    char *test2 = "orf";
    char *testNULL = S21_NULL;
    ck_assert_str_eq(s21_strpbrk(test, test2), strpbrk(test, test2));
    ck_assert_str_eq(s21_strpbrk("123456789", "9"), strpbrk("123456789", "9"));
    ck_assert_msg(s21_strpbrk("123456789", "0") == S21_NULL, "S21_NULL should be returned s21_strbrk");
    ck_assert_msg(s21_strpbrk("12345678", "09") == S21_NULL, "S21_NULL should be returned strbrk");
    ck_assert_msg(s21_strpbrk(testNULL, "09") == S21_NULL, "S21_NULL should be returned strbrk");
}
END_TEST

START_TEST(s21_strrchr_test) {
    char str[] = "School 21";
    int boolean = 0;
    char *testNULL = S21_NULL;

    char *first = s21_strrchr(str, 'S');
    char *second = strrchr(str, 'S');
    boolean = s21_strcmp(first, second) == 0;
    ck_assert_msg(boolean, "FAIL - with \"S\" inside \"School 21\"");

    first = s21_strrchr(str, '1');
    second = strrchr(str, '1');
    boolean = s21_strcmp(first, second) == 0;
    ck_assert_msg(boolean, "FAIL - with \"1\" inside \"School 21\"");

    first = s21_strrchr(str, '2');
    second = strrchr(str, '2');
    boolean = s21_strcmp(first, second) == 0;
    ck_assert_msg(boolean, "FAIL - with \"2\" inside \"School 21\"");

    first = s21_strrchr(testNULL, '2');
    boolean = first == S21_NULL;
    ck_assert_msg(boolean, "FAIL - with S21_NULL string");

    first = s21_strrchr(testNULL, -20);
    boolean = first == S21_NULL;
    ck_assert_msg(boolean, "FAIL - with S21_NULL string");
}
END_TEST

START_TEST(s21_strspn_test) {
    char *test = "string for testing 123";
    char *test2 = "gnsrti orf";
    // char *testNULL = S21_NULL;

    ck_assert_int_eq(s21_strspn(test, test2), strspn(test, test2));
    ck_assert_int_eq(s21_strspn("123456789", "987"), strspn("123456789", "987"));
    ck_assert_int_eq(s21_strspn("123456789", " "), strspn("123456789", " "));
    ck_assert_int_eq(s21_strspn(" ", " "), strspn(" ", " "));
    ck_assert_int_eq(s21_strspn("123456789", "\n"), strspn("123456789", "\n"));
    // ck_assert_int_eq(s21_strspn("123456789", testNULL), 0);
}
END_TEST

START_TEST(s21_strstr_test) {
    char *test1 = "123qwe45qwer678qwerty9098";
    char *test2 = "qwerty";
    char *testNULL = S21_NULL;

    ck_assert_str_eq(s21_strstr(test1, test2), strstr(test1, test2));
    ck_assert_msg(s21_strstr(test1, testNULL) == S21_NULL, "FAILED with S21_NULL string");
    ck_assert_msg(s21_strstr(testNULL, test2) == S21_NULL, "FAILED with S21_NULL string");
}
END_TEST

START_TEST(s21_strtok_test) {
    char test1[] = "arava#arriva/";
    char test2[] = "arava#arriva/";
    char testch[3] = "#/";
    char *testNULL = S21_NULL;

    ck_assert_str_eq(s21_strtok(test1, testch), strtok(test2, testch));
    ck_assert_str_eq(s21_strtok(testNULL, testch), strtok(testNULL, testch));
}
END_TEST

START_TEST(s21_to_upper_test) {
    char testStr[] = "qWeRtYuIoP123!@#$%%^&*/|'";
    char testRes[] = "QWERTYUIOP123!@#$%%^&*/|'";
    char *testNULL = S21_NULL;
    char *funcResult = S21_NULL;
    int boolean = 0;

    funcResult = s21_to_upper(testStr);
    boolean = s21_memcmp(funcResult, testRes, 24) == 0;
    ck_assert_msg(boolean, "FAILED with \"qWeRtYuIoP123!@#$%%^&*/|'\"");
    free(funcResult);
    funcResult = s21_to_upper(testNULL);
    boolean = funcResult == S21_NULL;
    ck_assert_msg(boolean, "FAILED with S21_NULL str");
    free(funcResult);
}
END_TEST

START_TEST(s21_to_lower_test) {
    char testStr[] = "QWERTYUIOP123!@#$%%^&*/|'";
    char testRes[] = "qwertyuiop123!@#$%%^&*/|'";
    char *testNULL = S21_NULL;
    char *funcResult = S21_NULL;
    int boolean = 0;

    funcResult = s21_to_lower(testStr);
    boolean = s21_memcmp(funcResult, testRes, 24) == 0;
    ck_assert_msg(boolean, "FAILED with \"QWERTYUIOP123!@#$%%^&*/|'\"");
    free(funcResult);
    funcResult = s21_to_lower(testNULL);
    boolean = funcResult == S21_NULL;
    ck_assert_msg(boolean, "FAILED with S21_NULL str");
    free(funcResult);
}
END_TEST

START_TEST(s21_insert_test) {
    char testSrc[] = "QWERTYUIOP";
    char testStr[] = "12345";
    char testResult[] = "QWERTY12345UIOP";
    s21_size_t testIndex = 6;
    char *testNULL = S21_NULL;
    char *funcResult = S21_NULL;
    int boolean = 0;

    funcResult = s21_insert(testSrc, testStr, testIndex);
    boolean = s21_memcmp(funcResult, testResult, 15) == 0;
    ck_assert_msg(boolean, "FAILED with \"12345\" to 6th plase into \"QWERTYUIOP\"");
    free(funcResult);
    funcResult = s21_insert(testNULL, testNULL, testIndex);
    boolean = funcResult == S21_NULL;
    ck_assert_msg(boolean, "FAILED with S21_NULL str");
    free(funcResult);
    funcResult = s21_insert(testSrc, testStr, 100);
    boolean = funcResult == S21_NULL;
    ck_assert_msg(boolean, "FAILED with exceeded index");
    free(funcResult);
}
END_TEST

START_TEST(s21_trim_test) {
    char testSrc1[] = "#*/*#/DodgE*/#";
    char testTrim[] = "#/*";
    char testResult[] = "DodgE";
    char testSrc2[] = "#*/";
    char *testNULL = S21_NULL;
    char *funcResult = S21_NULL;
    int boolean = 0;

    funcResult = s21_trim(testSrc1, testTrim);
    boolean = s21_memcmp(funcResult, testResult, 5) == 0;
    ck_assert_msg(boolean, "FAILED with \"#/*\" inside \"#*/*#/DodgE*/#\"");
    free(funcResult);
    funcResult = s21_trim(testSrc2, testTrim);
    boolean = funcResult == S21_NULL;
    ck_assert_msg(boolean, "FAILED with \"#/*\" inside \"#*/\"");
    free(funcResult);
    funcResult = s21_trim(testNULL, testTrim);
    boolean = funcResult == S21_NULL;
    ck_assert_msg(boolean, "FAILED with S21_NULL string");
    free(funcResult);
}
END_TEST
float a = 0.430000;
START_TEST(s21_sprintf_test) {
    char str1[150] = "";
    char str2[150] = "";
    char buf1[60] = "";
    char buf2[60] = "";
    char s1[150] = "";
    char s2[150] = "";
    char buff1[50] = "";
    char buff2[50] = "";
    char st1[100] = "";
    char st2[100] = "";
    int l1 = s21_sprintf(str1, "%+*d", 6, 534);
    int l2 = sprintf(str2, "%+*d", 6, 534);
    ck_assert_int_eq(l1, l2);
    ck_assert_str_eq(str1, str2);
    int l3 = s21_sprintf(buf1, "%.*d %d % f %+-*d %% ", 6, 2888, -286, 4.0, 6, 100);
    int l4 = sprintf(buf2, "%.*d %d % f %+-*d %% ", 6, 2888, -286, 4.0, 6, 100);
    ck_assert_int_eq(l3, l4);
    ck_assert_str_eq(buf1, buf2);
    int l5 = sprintf(s1, "%*.*d %d % f %+-*d %% %.*i %*c %-*lu\n", 9, 6, 2888, -286, 4.0, 6, 100, 7, 45674, 8,
                     'Q', 7, 5555555555);
    int l6 = s21_sprintf(s2, "%*.*d %d % f %+-*d %% %.*i %*c %-*lu\n", 9, 6, 2888, -286, 4.0, 6, 100, 7,
                         45674, 8, 'Q', 7, 5555555555);
    ck_assert_int_eq(l5, l6);
    ck_assert_str_eq(s1, s2);
    int l7 = s21_sprintf(buff1, "%s", "Hello world Hello world Hello world");
    int l8 = sprintf(buff2, "%s", "Hello world Hello world Hello world");
    ck_assert_int_eq(l7, l8);
    ck_assert_str_eq(buff1, buff2);
    int l9 = s21_sprintf(st1, "%-*.*f %d %-*c", 10, 0, -123.2345, 0, 5, 'S');
    int l10 = sprintf(st2, "%-*.*f %d %-*c", 10, 0, -123.2345, 0, 5, 'S');
    ck_assert_int_eq(l9, l10);
    ck_assert_str_eq(st1, st2);
}
END_TEST

Suite *s21_string_suite(void) {
    Suite *suite;
    TCase *getCase;

    suite = suite_create("String");
    getCase = tcase_create("core");

    tcase_add_test(getCase, s21_memchr_test);
    tcase_add_test(getCase, s21_memcmp_test);
    tcase_add_test(getCase, s21_memcpy_test);
    tcase_add_test(getCase, s21_memmove_test);
    tcase_add_test(getCase, s21_memset_test);
    tcase_add_test(getCase, s21_strcat_test);
    tcase_add_test(getCase, s21_strncat_test);
    tcase_add_test(getCase, s21_strchr_test);
    tcase_add_test(getCase, s21_strcmp_test);
    tcase_add_test(getCase, s21_strncmp_test);
    tcase_add_test(getCase, s21_strcpy_test);
    tcase_add_test(getCase, s21_strncpy_test);
    tcase_add_test(getCase, s21_strcspn_test);
    tcase_add_test(getCase, s21_strerror_test);
    tcase_add_test(getCase, s21_strlen_test);
    tcase_add_test(getCase, s21_strpbrk_test);
    tcase_add_test(getCase, s21_strrchr_test);
    tcase_add_test(getCase, s21_strspn_test);
    tcase_add_test(getCase, s21_strstr_test);
    tcase_add_test(getCase, s21_strtok_test);
    tcase_add_test(getCase, s21_to_upper_test);
    tcase_add_test(getCase, s21_to_lower_test);
    tcase_add_test(getCase, s21_insert_test);
    tcase_add_test(getCase, s21_trim_test);
    tcase_add_test(getCase, s21_sprintf_test);
    suite_add_tcase(suite, getCase);

    return suite;
}

int main(void) {
    int amountOfFailed = 0;
    Suite *suite;
    SRunner *runner;

    suite = s21_string_suite();
    runner = srunner_create(suite);

    srunner_run_all(runner, CK_NORMAL);
    amountOfFailed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (amountOfFailed == 0) ? 0 : 1;
}
