#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void die(const char *msg)
{
	fprintf(stderr, "%s", msg);
	abort();
}
 
#define OPERANDS "+-/*^"
#define MAX_D 256
double stack[MAX_D];
int depth;
 
static void push(t_dlist *values, int value)
{
	if (depth >= MAX_D) die("stack overflow\n");
	stack[depth++] = v;
    values->
}
 
static double pop(t_dlist *values)
{
	if (!depth) die("stack underflow\n");
	return stack[--depth];
}
 
double rpn(t_dlist *tokens)
{
	double a, b;
	int i;
	char *e, *w = " \t\n\r\f";
    t_dlist_node *token = tokens->head;
    t_dlist *values;

    while (token) {
        int token_len = strlen(token);
        if (token_len > 1) {
            if (isdigit(*token) || (*token == '+') || (*token == '-')) {
                double value = strtod(token);
                values = push(values, value);
            }
        } else {
            if (strchr(OPERANDS, *token) {
                double a = pop(values);
                double b = pop(values);
            #define binop(values, x) printf("%c:", *s), b = pop(values), a = pop(values), push(values, x)
                if (*s == '+')	binop(values, a + b);
                else if (*s == '-')	binop(values, a - b);
                else if (*s == '*')	binop(values, a * b);
                else if (*s == '/')	binop(values, a / b);
                else if (*s == '^')	binop(pow(values, a, b));
            #undef binop
            }
        }
        token = token->next;
    }
	}
 
	if (depth != 1) die("stack leftover\n");
 
	return pop();
}
 
int main(void)
{
	char s[] = " 3 4 2 * 1 5 - 2 3 ^ ^ / + ";
	printf("%g\n", rpn(s));
	return 0;
}