#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "smartcalc.h"


t_calc_output output;

#define fail(s1) { \
	char err_buf[100]; \
	fprintf(stderr, "[Error] %s\n", s1); \
	sprintf(err_buf, "[Error] %s\n", s1); \
	output.is_error = true; \
	output.message = ft_strdup(err_buf); \
    }

#define check_pop() { \
    if (output.is_error) { \
        output.output = 0; \
        return output; \
    } \
}

#define OPERANDS "+-/*^"
#define X_VAR "xX"
#define calc(values, x) push(values, x)

static int eq(char *a, char *b)
{
    return !strcmp(a, b);
}

/*
static void t_dlist_print(t_dlist *dlist)
{
    return ;
    //printf("dlist content:\n");
    t_dlist_node *tmp = dlist->head;
    while (tmp) {
        printf("%.0f ", *((double *)tmp->data));
        tmp = tmp->next;
    }
    printf("\n");
    //printf("dlist content end\n");
}
*/

static void push(t_dlist *values, double value)
{
    if (isnan(value) || isinf(value)) {
        fail("calculation error");
        return;
    }
    double *dbl_storage = ft_memalloc(sizeof(double));
    memcpy(dbl_storage, &value, sizeof(double));
    //printf("values size before push: %d\n", values->size);
    t_dlist_push(values, t_dlist_node_new(dbl_storage, sizeof(double)));
    //printf("values size after push: %d\n", values->size);
}
 
static double pop(t_dlist *values)
{
	if (!values->size) {
        fail("stack underflow");
        return 0;
    } 
    //printf("values size before pop: %d\n", values->size);
    //t_dlist_print(values);
	t_dlist_node *popped = t_dlist_pop(values, values->head);
    double value = *((double *)popped->data);
    t_dlist_node_free_simple(popped);
    //printf("values size after pop: %d\n", values->size);
    //t_dlist_print(values);
    return value;
}

char *answer_to_string(double answ)
{
    if (isnan(answ) || isinf(answ)) {
        return ft_strdup("Error: zero division");
    }
    char *s = ft_memalloc(50);
    sprintf(s, "%.7f", answ);
    return s;
}
 
t_calc_output rpn(t_dlist *tokens, double x_val)
{
	double a, b;
    t_dlist_node *token = tokens ? tokens->head : NULL;
    t_dlist *values = t_dlist_new();
    double value;
    memset(&output, 0, sizeof(t_calc_output));

    char x_str[20];
    sprintf(x_str, "%.7f", x_val);

    //t_dlist_print_str(tokens);
    while (token) {
        char *s = (char *)token->data;
        //printf("token: %s\n", s);
        int token_len = strlen(s);
        if (token_len > 1 || isdigit(*s)) {
            if (isdigit(*s) || (*s == '+') || (*s == '-')) {
                value = strtod(s, NULL);
                push(values, value);
            } else {
                a = pop(values);
                check_pop();
                if (eq("cos", s)) calc(values, cos(a));
                else if (eq("sin", s)) calc(values, sin(a));
                else if (eq("tan", s)) calc(values, tan(a));
                else if (eq("acos", s)) calc(values, acos(a));
                else if (eq("asin", s)) calc(values, asin(a));
                else if (eq("atan", s)) calc(values, atan(a));
                else if (eq("sqrt", s)) calc(values, sqrt(a));
                else if (eq("log", s)) calc(values, log10(a));
                else if (eq("ln", s)) calc(values, log(a));
            }
        } else {
            if (strchr(OPERANDS, *s)) {
                b = pop(values);
                check_pop();
                a = pop(values);
                check_pop();
                if (*s == '+')	calc(values, a + b);
                else if (*s == '-')	calc(values, a - b);
                else if (*s == '*')	calc(values, a * b);
                else if (*s == '/')	calc(values, a / b);
                else if (*s == '^')	calc(values, pow(a, b));
            } else if (strchr(X_VAR, *s)) {
                value = strtod(x_str, NULL);
                push(values, value);
            }
        }
        //t_dlist_print(values);
        token = token->next;
    }
 
	if (values->size != 1) {
        fail("stack leftover");
    } else if (tokens) {
        output.output = pop(values);
        check_pop();
        t_dlist_free(values, t_dlist_node_free_simple);
    }
	return output;
}
 
/*
int main(void)
{
	char s[] = " 3 4 2 * 1 5 - 2 3 ^ ^ / + ";
	printf("%g\n", rpn(s));
	return 0;
}
*/