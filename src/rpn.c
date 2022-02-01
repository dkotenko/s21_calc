#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "smartcalc.h"

static void die(const char *msg)
{
	fprintf(stderr, "%s", msg);
	abort();
}
 
#define OPERANDS "+-/*^"
#define calc(values, x) push(values, x)

static int eq(char *a, char *b)
{
    return !strcmp(a, b);
}

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
/*
static void t_dlist_print_str(t_dlist *dlist)
{
    printf("dlist content:\n");
    t_dlist_node *tmp = dlist->head;
    while (tmp) {
        printf("%s\n", (char *)tmp->data);
        tmp = tmp->next;
    }
    printf("dlist content end\n");
}
*/
static void push(t_dlist *values, double value)
{
    double *dbl_storage = ft_memalloc(sizeof(double));
    memcpy(dbl_storage, &value, sizeof(double));
    //printf("values size before push: %d\n", values->size);
    t_dlist_push(values, t_dlist_node_new(dbl_storage, sizeof(double)));
    //printf("values size after push: %d\n", values->size);
}
 
static double pop(t_dlist *values)
{
	if (!values->size) die("stack underflow\n");
    //printf("values size before pop: %d\n", values->size);
    //t_dlist_print(values);
	t_dlist_node *popped = t_dlist_pop(values, values->head);
    double value = *((double *)popped->data);
    t_dlist_node_free_simple(popped);
    //printf("values size after pop: %d\n", values->size);
    //t_dlist_print(values);
    return value;
}
 
double rpn(t_dlist *tokens)
{
	double a, b;
    t_dlist_node *token = tokens->head;
    t_dlist *values = t_dlist_new();

    //t_dlist_print_str(tokens);
    while (token) {
        char *s = (char *)token->data;
        //printf("token: %s\n", s);
        int token_len = strlen(s);
        if (token_len > 1 || isdigit(*s)) {
            if (isdigit(*s) || (*s == '+') || (*s == '-')) {
                double value = strtod(s, NULL);
                push(values, value);
            } else {
                a = pop(values);
                if (eq("cos", s)) calc(values, cos(a));
                else if (eq("sin", s)) calc(values, sin(a));
                else if (eq("tan", s)) calc(values, tan(a));
                else if (eq("acos", s)) calc(values, acos(a));
                else if (eq("asin", s)) calc(values, asin(a));
                else if (eq("atan", s)) calc(values, atan(a));
            }
        } else {
            if (strchr(OPERANDS, *s)) {
                b = pop(values);
                a = pop(values);
                if (*s == '+')	calc(values, a + b);
                else if (*s == '-')	calc(values, a - b);
                else if (*s == '*')	calc(values, a * b);
                else if (*s == '/')	calc(values, a / b);
                else if (*s == '^')	calc(values, pow(a, b));
            }
        }
        t_dlist_print(values);
        token = token->next;
    }
 
	if (values->size != 1) die("stack leftover\n");
    double result = pop(values);
    t_dlist_free(values, t_dlist_node_free_simple);
    t_dlist_free(tokens, t_dlist_node_free_simple);
	return result;
}
 
/*
int main(void)
{
	char s[] = " 3 4 2 * 1 5 - 2 3 ^ ^ / + ";
	printf("%g\n", rpn(s));
	return 0;
}
*/