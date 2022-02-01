#include "tests.h"
#include <math.h>

typedef struct {
	const char *s;
	double result;
} t_expression;

int expr_size = 6;

static t_dlist *spaced_str_to_dlist(const char *s)
{
	const char *delim = " ";
	t_dlist *dlist = t_dlist_new();

 	char *p = strtok((char *)s, delim);
	while (p != NULL)
	{
		p = strtok(NULL, delim);
		t_dlist_append(dlist, t_dlist_node_new(ft_strdup(p), sizeof(char)));
	}
	return dlist;
}

t_expression expr[6] = {
	{"+3 4 2 * 1 5 - 2 3 ^ ^ / +", 3.000122},
	{"1 1 +", 2.},
	{"123", 123.},
	{"1 2 + 3 4 5 + * +", 30.},
	{"1 2 * 3 *", 6.},
	{"1 2 2 2 3 + * + *", 12.}
};


START_TEST(test_calculation) {
	for (int i = 0; i < expr_size; i++) {
		t_dlist *dlist = spaced_str_to_dlist(expr[i].s);
		double value = rpn(dlist);
		ck_assert_int_eq(1, equal(value, expr[i].result));
		t_dlist_free(dlist, t_dlist_node_free_simple);
		break;
	}
} END_TEST


Suite *calculation_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("calculation");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_calculation);
  suite_add_tcase(s, tc_core);

  return s;
}