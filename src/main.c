#include "smartcalc.h"
#include <stdio.h>
#include <string.h>

int debug;

static void print_prn_string(t_dlist *rpn)
{
	t_dlist_node *tmp = rpn->head;
	while (tmp) {
		printf("%s ", (char *)tmp->data);
		tmp = tmp->next;
	}
	printf("\n");

}

int main(int ac, char **av)
{
	debug = ac == 2 && !strcmp(av[1], "-d") ? 1 : 0;

	int i;
	const char *tests[] = { 
		"+3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3",	/* RC mandated: OK */
		"123",					/* OK */
		"3+4 * 2 / ( 1 - 5 ) ^ 2 ^ 3.14",	/* OK */
		"(((((((1+2+3**(4 + 5))))))",		/* bad parens */
		"a^(b + c/d * .1e5)",			/* unknown op */
		"(1**2)**3",				/* OK */
		"2 + 2 *",
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
		exit(0);
        //must be 3 4 2 * 1 5 - 2 3 ^ ^ / +
	}
 
	return 0;
}
