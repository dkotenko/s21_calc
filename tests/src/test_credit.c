#include "tests.h"

START_TEST(test_credit_annuity) {
	t_credit_input input;
	memset(&input, 0, sizeof(t_deposit_input));

	input.amount = 10000;
	input.interest_rate = 10;
	input.term_in_months = 12;
	input.type = ANNUITY;

	t_credit_output output = calc_credit(input);
	t_credit_output expected_output;
	memset(&expected_output, 0, sizeof(t_credit_output));
	expected_output.total_payment = 10549.92;
	expected_output.overpayment = 549.92;

	ck_assert_int_eq(1, equal(expected_output.total_payment, output.total_payment));
	ck_assert_int_eq(1, equal(expected_output.overpayment, output.overpayment));
} END_TEST

START_TEST(test_credit_diff) {
	t_credit_input input;
	memset(&input, 0, sizeof(t_deposit_input));

	input.amount = 10000;
	input.interest_rate = 10;
	input.term_in_months = 12;
	input.type = DIFFERENTIATED;

	t_credit_output output = calc_credit(input);
	t_credit_output expected_output;
	memset(&expected_output, 0, sizeof(t_credit_output));
	expected_output.total_payment = 10541.67;
	expected_output.overpayment = 541.67;

	ck_assert_int_eq(1, equal(expected_output.total_payment, output.total_payment));
	ck_assert_int_eq(1, equal(expected_output.overpayment, output.overpayment));
} END_TEST

Suite *credit_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("credit");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_credit_annuity);
  tcase_add_test(tc_core, test_credit_diff);
  suite_add_tcase(s, tc_core);


  return s;
}

