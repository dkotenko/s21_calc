#include "tests.h"
#include <math.h>

typedef struct {
	const char *s;
	double result;
} t_expression;



static t_dlist *spaced_str_to_dlist(const char *str_origin)
{
	const char *delim = " ";
	t_dlist *dlist = t_dlist_new();
	char *s = ft_strdup(str_origin);
 	char *p = strtok((char *)s, delim);
	
	while (p != NULL)
	{
		t_dlist_append(dlist, t_dlist_node_new(ft_strdup(p), sizeof(char)));
		p = strtok(NULL, delim);		
	}
	free(s);
	return dlist;
}

t_expression expr[6] = {
	{"+3 4 2 * 1 5 - 2 3 ^ ^ / +", 3.000122},
	{"1 1 +", 2.},
	{"123", 123.},
	{"1 2 + 3 4 5 + * +", 30.},
	{"1 2 * 3 *", 6.},
	{"1 cos", 0}
};

int expr_size = 6;

START_TEST(test_calculation) {
	for (int i = 0; i < expr_size; i++) {
		t_dlist *dlist = spaced_str_to_dlist(expr[i].s);
		double value = (rpn(dlist, 0)).output;
		double rpn_result = expr[i].result;
		ck_assert_int_eq(1, equal(value, rpn_result));
		t_dlist_free(dlist, t_dlist_node_free_simple);
		break;
	}
} END_TEST

START_TEST(test_var_x) {
	char *s = "x 20 +";
	int x = 10;
	t_dlist *dlist = spaced_str_to_dlist(s);
	double value = (rpn(dlist, x)).output;
	double rpn_result = 30;
	ck_assert_int_eq(1, equal(value, rpn_result));
	t_dlist_free(dlist, t_dlist_node_free_simple);
} END_TEST

START_TEST(test_null_tokens) {
	t_dlist *dlist = NULL;
	double value = (rpn(dlist, 0)).output;
	double rpn_result = 0;
	ck_assert_int_eq(1, equal(value, rpn_result));
} END_TEST

START_TEST(test_zero) {
	char *s = "20 / 0";
	int x = 10;
	t_dlist *dlist = spaced_str_to_dlist(s);
	t_dlist_print_str(dlist);
	t_calc_output out = rpn(dlist, x);
	ck_assert_int_eq(out.is_error, true);
	ck_assert_int_eq(out.output, 0);
	free(out.message);
	t_dlist_free(dlist, t_dlist_node_free_simple);
} END_TEST

START_TEST(test_stack_underflow) {
	char *s = "20 / 1 +";
	int x = 10;
	t_dlist *dlist = spaced_str_to_dlist(s);
	t_dlist_print_str(dlist);
	t_calc_output out = rpn(dlist, x);
	ck_assert_int_eq(out.is_error, true);
	ck_assert_int_eq(out.output, 0);
	free(out.message);
	t_dlist_free(dlist, t_dlist_node_free_simple);
} END_TEST

START_TEST(test_stack_overflow) {
	char *s = "20 1 0";
	int x = 10;
	t_dlist *dlist = spaced_str_to_dlist(s);
	t_dlist_print_str(dlist);
	t_calc_output out = rpn(dlist, x);
	ck_assert_int_eq(0, strcmp("[Error] stack leftover\n", out.message));
	ck_assert_int_eq(out.is_error, true);
	ck_assert_int_eq(out.output, 0);
	free(out.message);
	t_dlist_free(dlist, t_dlist_node_free_simple);
} END_TEST

START_TEST(test_push_nan) {
	char *s = "20 nan +";
	int x = 10;
	t_dlist *dlist = spaced_str_to_dlist(s);
	t_dlist_print_str(dlist);
	t_calc_output out = rpn(dlist, x);
	ck_assert_int_eq(out.output, 0);
	free(out.message);
	t_dlist_free(dlist, t_dlist_node_free_simple);
} END_TEST

START_TEST(test_answer_to_string_error) {
	char *answer = answer_to_string(NAN);
	ck_assert_int_eq(0, strcmp(answer, "Error: zero division"));
	free(answer);
} END_TEST

START_TEST(test_answer_to_string) {
	char *answer = answer_to_string(10);
	ck_assert_int_eq(0, strcmp(answer, "10.0000000"));
	free(answer);
} END_TEST

Suite *calculation_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("calculation");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_calculation);
  tcase_add_test(tc_core, test_var_x);
  tcase_add_test(tc_core, test_zero);
  tcase_add_test(tc_core, test_stack_underflow);
  tcase_add_test(tc_core, test_stack_overflow);
  tcase_add_test(tc_core, test_answer_to_string);
  tcase_add_test(tc_core, test_answer_to_string_error);
  tcase_add_test(tc_core, test_null_tokens);
  tcase_add_test(tc_core, test_push_nan);
  
  suite_add_tcase(s, tc_core);

  return s;
}