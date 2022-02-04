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

static t_args parse_arguments(int ac, char **av)
{
	t_args args;

	args.mode = CALC_NORMAL;
	for (int i = 1; i < ac; i++) {
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

void run_gui()
{
	return ;
}

void calc_normal()
{
	;
}

void calc_deposit()
{
	;
}



int main(int ac, char **av)
{
	t_args args = parse_arguments(ac, av);
	if (!args.console) {
		run_gui();
	}

	t_credit credit;
	memset(&data, 0);

	switch (args.mode) {
		case CALC_DEPOSIT:
			calc_deposit();
			break ;
		case CALC_CREDIT_ANNUITY:
			calc_annuity(data);
			break ;
		case CALC_CREDIT_DIFFERENTIATED:
			calc_differentiated(data	);
			break ;
		default:
			calc_normal();
	}	

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
 
	if (!init()) {
		return 1;
	}

	t_dlist *rpn_string;

	for (i = 0; tests[i]; i++) {
		printf("Testing string `%s'   <enter>\n", tests[i]);
		//getchar();

		rpn_string = parse(tests[i]);
		printf("string `%s': %s\n\n", tests[i],
			 rpn_string ? "Ok" : "Error");
		print_rpn_string(rpn_string);
		printf("RESULT: %f\n", rpn(rpn_string));
        //must be 3 4 2 * 1 5 - 2 3 ^ ^ / +
		exit(0);
	}
 
	return 0;
}
