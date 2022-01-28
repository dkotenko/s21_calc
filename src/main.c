#include "smartcalc.h"
#include <stdio.h>
#include <string.h>

typedef struct {
	int console;
} t_args;

static t_args parse_arguments(int ac, char **av)
{
	t_args args;

	for (int i = 1; i < ac; i++) {
		args.console = !strcmp(av[i], "-c") || !strcmp(av[i], "--console") ? 1 : 0;
	}
	return args;
}

static void print_prn_string(t_dlist *rpn)
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

int main(int ac, char **av)
{
	t_args args = parse_arguments(ac, av);
	if (!args.console) {
		run_gui();
	}

	int i;
	const char *tests[] = {
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
		print_prn_string(rpn_string);
		printf("RESULT: %f\n", rpn(rpn_string));
        //must be 3 4 2 * 1 5 - 2 3 ^ ^ / +
	}
 
	return 0;
}
