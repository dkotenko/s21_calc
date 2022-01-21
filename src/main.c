#include "smartcalc.h"
#include <stdio.h>
#include <string.h>

char    *parse_letter(char *s, int *pointer_position, int len_s) {
    int i = *pointer_position;

    if (s[i] == 'x') {
        return ;
    } else if (!strcmp("mod", s + i)) {
        return ;
    } else if (!strcmp("sin", s + i)) {

    } else if (!strcmp("con", s + i)) {

    } else if (!strcmp("tan", s + i)) {
    
    } else if (!strcmp("asin", s + i)) {

    } else if (!strcmp("acos", s + i)) {

    } else if (!strcmp("atan", s + i)) {

    } else if (!strcmp("sqrt", s + i)) {

    } else if (!strcmp("log", s + i)) {
    
    } else if (!strcmp("ln", s + i)) {

    } else {
        handle_error();
    }
    parse_expression()
    parse_bracket()
}


char    *lexer(char *s)
{
    int len_s = strlen(s);
    int i = 0;
    t_dlist *tokens = t_dlist_new();
    while (s[i]) {
        if isalpha(s[i]) {
            parse_letter(s, &i, len_s);
        } else if (isdigit(s[i])) {
            parse_number(s, &i);
        } else if (strchr(OPERANDS,s[i])) {
            parse_operand(s, &i);
        } else if (s[i] == '(' || s[i] == ')') {
            parse_bracket();
        } else {
            handle_error((s, &i);
        }
        i++;
    }
    return NULL;
}

char *calculate(char *s)
{
    char *result = lexer(s);
    return result;
}

int main() {
    char *s = "1 + 1";

    char *result = calculate(s);
    printf("result: %s\n", result);
    return 0;
}
