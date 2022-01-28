#include "tests.h"
#include <math.h>

typedef struct {
	const char *s;
	double result;
} expression;

int expr_size = 5;



/*
START_TEST(test_calculation_1) {
	for (int i = 0; i < expr_size; i++) {
		double value = rpn(parse(expr[i].s));
		ck_assert_int_eq(1, equal(value, expr[i].result));
		break;
	}
} END_TEST
*/

START_TEST(test_calculation_1) {
		//char *s = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3";
		double result = 3.00012207;
		t_dlist *p = parse("1+1");
		exit(0);
		double value = rpn(p);
		
		ck_assert_int_eq(1, equal(value, result));
} END_TEST

/*
START_TEST(test_calculation_2) {
		double value = rpn(parse(expr[1].s));
		ck_assert_int_eq(1, equal(value, expr[1].result));
} END_TEST

START_TEST(test_calculation_3) {
		double value = rpn(parse(expr[2].s));
		ck_assert_int_eq(1, equal(value, expr[2].result));
} END_TEST

START_TEST(test_calculation_4) {
		double value = rpn(parse(expr[3].s));
		ck_assert_int_eq(1, equal(value, expr[3].result));
} END_TEST

START_TEST(test_calculation_5) {
		double value = rpn(parse(expr[4].s));
		ck_assert_int_eq(1, equal(value, expr[4].result));
} END_TEST
*/

Suite *calculation_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("calculation");
  tc_core = tcase_create("Core");

/*
expression expr[5] = {
	,
	{"123", 123.},
	//{"3+4 * 2 / ( 1 - 5 ) ^ 2 ^ 3.14", }, radicals not supported
	{"(((((((1+2+3*(4 + 5))))))))",  30},
	//{"a^(b + c/d * .1e5)", }, 
	{"(1*2)*3", 6.},
	{"(1) * (2+2*(2+3))", 12}
};
*/
  tcase_add_test(tc_core, test_calculation_1);
  /*
  tcase_add_test(tc_core, test_calculation_2);
  tcase_add_test(tc_core, test_calculation_3);
  tcase_add_test(tc_core, test_calculation_4);
  tcase_add_test(tc_core, test_calculation_5);
  */
  suite_add_tcase(s, tc_core);

  return s;
}