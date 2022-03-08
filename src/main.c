#include "smartcalc.h"
#include <stdio.h>
#include <string.h>

enum e_calc_mode {
	CALC_NORMAL,
	CALC_CREDIT_ANNUITY,
	CALC_CREDIT_DIFFERENTIATED,
	CALC_DEPOSIT
};

typedef struct {
	int console;
	int mode;
} t_args;

#define IS(s, s_orig) (!strcmp(s, s_orig))

static t_args parse_arguments(int ac, char **av)
{
	t_args args;

	memset(&args, 0, sizeof(t_args));
	args.mode = CALC_NORMAL;
	for (int i = 1; i < ac; i++) {
		if (IS(av[i], "-h") || IS(av[i], "--help")) {
			printf("%4s: %s\n", "-co", "--console");
			printf("%4s: %s\n", "-ca", "--credit-annuity");
			printf("%4s: %s\n", "-cd", "--credit-differentiated");
			printf("%4s: %s\n", "-de", "--deposit");
			exit(0);
		}
		args.console = !strcmp(av[i], "-co") || !strcmp(av[i], "--console") ? 1 : 0;
		args.mode = !strcmp(av[i], "-ca") || !strcmp(av[i], "--credit-annuity") ? CALC_CREDIT_ANNUITY : args.mode;
		args.mode = !strcmp(av[i], "-cd") || !strcmp(av[i], "--credit-differentiated") ? CALC_CREDIT_DIFFERENTIATED : args.mode;
		args.mode = !strcmp(av[i], "-de") || !strcmp(av[i], "--deposit") ? CALC_DEPOSIT : args.mode;
	}
	return args;
}

static void print_rpn_string(t_dlist *rpn)
{
	t_dlist_node *tmp = rpn->head;
	while (tmp) {
		printf("%s ", (char *)tmp->data);
		tmp = tmp->next;
	}
	printf("\n");

}

void calc_normal()
{
	int i;
	const char *tests[] = {
		"cos(sin(30))",
		"1+1", 
		"+3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3",	/* RC mandated: OK */
		"123",					/* OK */
		"(((((((1+2+3*(4 + 5))))))))",		/* bad parens */
		"(1*2)*3",		/* OK */
		//"2 + 2 *",
		"(1) * (2+2*(2+3))",			/* unexpected eol */
		0
	};
 
	//if (!init()) {
	//	return ;
	//}

	t_dlist *rpn_string;
	t_rpn_transit t;
	
	for (i = 0; tests[i]; i++) {
		printf("Testing string `%s'   <enter>\n", tests[i]);
		t = parse(tests[i]);
		rpn_string = t.list;
		printf("string `%s': %s\n\n", tests[i],
			 rpn_string ? "Ok" : "Error");
		if (t.is_error) {
			printf("ERROR: %s\n", t.message);
			free(t.message);
		} else {
			print_rpn_string(rpn_string);
			t_calc_output out = rpn(rpn_string, 0);
			if (out.is_error) {
				printf("ERROR: %s\n", out.message);
				free(out.message);
			} else {
				printf("RESULT: %f\n", out.output);
				t_dlist_free(rpn_string, t_dlist_node_free_simple);
			}
		}
	}
}

t_calc_output calculate(char *s, double x)
{
	t_calc_output out;
	t_rpn_transit t;
	
	t = parse((const char *)s);
	if (t.is_error) {
		out.is_error = true;
		out.message = t.message;
	} else {
		out = rpn(t.list, x);
		t_dlist_free(t.list, t_dlist_node_free_simple);
	}
	return out;
}

int main(int ac, char **av)
{
	t_args args = parse_arguments(ac, av);
	if (!args.console) {
		run_gui();
	}

	t_credit_input data;
	memset(&data, 0, sizeof(t_credit_input));
	t_credit_output out;

	switch (args.mode) {
		case CALC_DEPOSIT:
			//calc_deposit();
			break ;
		case CALC_CREDIT_ANNUITY:
			out = calc_annuity(data);
			if (out.is_error) {
				printf("%s", out.message);
				free(out.message);
			} else {
				print_annuity(data, out);
				free(out.monthly_payments);
			}
			
			break ;
		case CALC_CREDIT_DIFFERENTIATED:
			out = calc_differentiated(data);
			if (out.is_error) {
				printf("%s", out.message);
				free(out.message);
			} else {
				print_differentiated(data, out);
				free(out.monthly_payments);
			}
			break ;
		default:
			calc_normal();
	}
	return 0;
}
