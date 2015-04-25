#include "assoc_array.h"
#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

START_TEST(test_HashMap_alloc_and_dealloc)
{
	HashMap *test = HashMap_alloc();
	HashMap_dealloc(test);
}
END_TEST

START_TEST(test_HashMap_set_and_get_simple)
{
	HashMap *test_map = HashMap_alloc();
	HashMap_set(test_map, "spam", 32);
	HashMap_set(test_map, "eggs", 42);
	HashMap_set(test_map, "spam and eggs", 37);
	ck_assert_int_eq(HashMap_get(test_map, "spam"), 32);
	ck_assert_int_eq(HashMap_get(test_map, "eggs"), 42);
	ck_assert_int_eq(HashMap_get(test_map, "spam and eggs"), 37);
	HashMap_dealloc(test_map);
}
END_TEST

START_TEST(test_HashMap_set_and_get_many)
{
	HashMap *test_map = HashMap_alloc();
	FILE *word_list = fopen("wordsEn.txt", "r");
	char word[50];
	int chars_scanned;
	int words_scanned = 0;
	int counter = 0;
	while (true) {
		chars_scanned = fscanf(word_list, "%s", word);
		if (chars_scanned == EOF) {
			break;
		}
		word[chars_scanned] = '\0';
		HashMap_set(test_map, word, counter);
		ck_assert_int_eq(HashMap_get(test_map, word), counter);
		counter++;
	}
	fclose(word_list);
	HashMap_dealloc(test_map);
}
END_TEST

Suite * assoc_array_suite(void) {
	Suite *s;
	TCase *tc_core;

	s = suite_create("assoc_array");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_HashMap_alloc_and_dealloc);
	tcase_add_test(tc_core, test_HashMap_set_and_get_simple);
	tcase_add_test(tc_core, test_HashMap_set_and_get_many);
	suite_add_tcase(s, tc_core);

	return s;
}

int main(void) {
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = assoc_array_suite();
	sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
