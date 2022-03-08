#include "tests.h"

START_TEST(test_deposit_basic) {
	t_deposit_input input;
	memset(&input, 0, sizeof(t_deposit_input));
	input.amount = 100000;
	input.interest_rate = 10;
	input.is_capitalization = false;
	input.term_in_months = 12;
	input.tax_rate = 10;
	input.with_amount = 100;
	input.with_every_n_month = 2;
	input.repl_amount = 100;
	input.repl_every_n_month = 2;

	t_deposit_output output = calc_deposit(input);
	t_deposit_output expected_output;
	memset(&expected_output, 0, sizeof(t_deposit_input));
	expected_output.accrued_interest = 10000;
	expected_output.tax_amount = 1000;
	expected_output.deposit_by_end = input.amount;

	ck_assert_int_eq(1, equal(expected_output.accrued_interest, output.accrued_interest));
	ck_assert_int_eq(1, equal(expected_output.tax_amount, output.tax_amount));
	ck_assert_int_eq(1, equal(expected_output.deposit_by_end, output.deposit_by_end));
} END_TEST


Suite *deposit_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("deposit");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_deposit_basic);
  suite_add_tcase(s, tc_core);

  return s;
}