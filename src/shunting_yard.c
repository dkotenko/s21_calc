#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "smartcalc.h"

t_pattern end_of_string = {"", A_NONE, 0, {0}};
 
t_pattern operands[] = {
	{")",	A_NONE, -1, {0}},
	{"mod",	A_R, 3, {0}},
	{"^",	A_R, 3, {0}},
	{"*",	A_L, 2, {0}},
	{"/",		A_L, 2, {0}},
	{"+",	A_L, 1, {0}},
	{"-",		A_L, 1, {0}},
	{0}
};
 
t_pattern arguments[] = {
	{"^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?", 0, 0, {0}},
	//{"^[a-zA-Z_][a-zA-Z_0-9]*", 0, 0, {0}},
	{"^[xX]", 0, 0, {0}},
	{"^\\(", A_L, -1, {0}},
	{0}
};	

t_pattern functions[] = {
	{"asin", A_R, 3, {0}},
	{"acos", A_R, 3, {0}},
	{"atan", A_R, 3, {0}},
	{"sin", A_R, 3, {0}},
	{"cos", A_R, 3, {0}},
	{"tan", A_R, 3, {0}},
	{"ln", A_R, 3, {0}},
	{"log", A_R, 3, {0}},
	{"sqrt", A_R, 3, {0}},
	{0}
};

static t_pattern *parse_number(const char *s, int *num_len, t_pattern *p)
{
	char *s_start = (char *)s;

	if (*s == '+' || *s == '-') {
		s++;
	}

	if (!*s || !isdigit(*s)) {
		*num_len = s - s_start;
		return 0;
	}

	while (isdigit(*s)) {
			s++;
		}

	if (*s == '.') {
		s++;
		while (isdigit(*s)) {
			s++;
		}	
	}
	*num_len = s - s_start;
	return p;

}

static t_pattern *match_args(const char *s, t_pattern *p, t_token * t, const char **e)
{
	while (*s == ' ' || *s == '\t') {
		s++;
	} 
	*e = s;

	if (!*s) {
		return &end_of_string;
	}

	if (*s == '+' || *s == '-' || isdigit(*s)) {
		int num_len = 0;
		t_pattern *to_return = parse_number(s, &num_len, p);
		t->s = s;
		*e = s + (t->len = num_len);
		return to_return;
	} else if (*s == 'x' || *s == 'X') {
		t->s = s;
		*e = s + (t->len = 1);
		return p + 1;
	} else if (*s == '(') {
		t->s = s;
		*e = s + (t->len = 1);
		return p + 2;
	}
	return 0;
}

static t_pattern* match(const char *s, t_pattern *p, t_token * t, const char **e)
{
	int i;
	
	while (*s == ' ' || *s == '\t') {
		s++;
	} 
	*e = s;
 
	if (!*s) {
		return &end_of_string;
	} 
 
	int s_len = strlen(s);
	for (i = 0; p[i].str; i++) {
		int pattern_len = strlen(p[i].str);
		if (pattern_len > s_len || strncmp(p[i].str, s, pattern_len)) {
			continue;
		}
		t->s = s;
		*e = s + (t->len = pattern_len);
		return p + i;
	}
	return 0;
}

/*
static t_pattern* match(const char *s, t_pattern *p, t_token * t, const char **e)
{
	int i;
	regmatch_t m;
	
	while (*s == ' ' || *s == '\t') {
		s++;
	} 
	*e = s;
 
	if (!*s) {
		return &end_of_string;
	} 
 
	for (i = 0; p[i].str; i++) {
		if (regexec(&(p[i].re), s, 1, &m, REG_NOTEOL))
			continue;
		t->s = s;
		*e = s + (t->len = m.rm_eo - m.rm_so);
		return p + i;
	}
	return 0;
}
*/

t_token stack[256]; /* assume these are big enough */
t_token queue[256];
t_dlist *dl_stack;
t_dlist *dl_queue;

int l_queue, l_stack;
#define qpush(x) queue[l_queue++] = x
#define spush(x) stack[l_stack++] = x
#define spop()   stack[--l_stack]
#define WHITE_SPACE " \t\n\r\f"

void free_node(t_dlist_node * node)
{
	free(node->data);
	free(node);
}

#define fail(s1, s2) { \
	char err_buf[100]; \
	fprintf(stderr, "[Error %s] %s\n", s1, s2); \
	sprintf(err_buf, "[Error %s] %s\n", s1, s2); \
	transit.is_error = true; \
	transit.message = ft_strdup(err_buf); \
	transit.list = NULL; \
	t_dlist_free(dl_stack, free_node); \
	t_dlist_free(dl_funct, free_node); \
	t_dlist_free(dl_queue, free_node); \
	return transit; }

/*
int init(void)
{
	int i;
	t_pattern *p;
	
	for (i = 0, p = operands; p[i].str; i++)
		if (regcomp(&(p[i].re), p[i].str, REG_NEWLINE|REG_EXTENDED))
			fail("comp", p[i].str);
 
	for (i = 0, p = arguments; p[i].str; i++)
		if (regcomp(&(p[i].re), p[i].str, REG_NEWLINE|REG_EXTENDED))
			fail("comp", p[i].str);

	for (i = 0, p = functions; p[i].str; i++)
		if (regcomp(&(p[i].re), p[i].str, REG_NEWLINE|REG_EXTENDED))
			fail("comp", p[i].str);
	return 1;
}
*/

 
t_rpn_transit parse(const char *s) {
	t_pattern *pattern = NULL;
	t_token *t, tok;
	dl_stack = t_dlist_new();
	dl_queue = t_dlist_new();
	t_dlist *dl_funct = t_dlist_new();
	int precedence_booster;
	t_rpn_transit transit;
	memset(&transit, 0, sizeof(t_rpn_transit));
	//printf("%s\n", s);
	precedence_booster = l_queue = l_stack = 0;
	while (*s) {
		pattern = match(s, functions, &tok, &s);

		if (pattern) {
			t_dlist_append(dl_funct, t_dlist_node_new(ft_strndup(tok.s, tok.len), sizeof(char)));
		}

		pattern = match_args(s, arguments, &tok, &s);
		if (!pattern || pattern == &end_of_string) {
			fail("parse arg", s);
		}
 
		if (pattern->precedence == -1) {
			precedence_booster += 100;
			continue;
		}
		t_dlist_append(dl_queue, t_dlist_node_new(ft_strndup(tok.s, tok.len), sizeof(char)));
		while (dl_funct->size) {
			t_dlist_append(dl_queue, t_dlist_pop(dl_funct, dl_funct->tail));
		}
		qpush(tok);
 
		while (1) {
			pattern = match(s, operands, &tok, &s);
			if (!pattern) {
				fail("parse op", s);
			}
 
			tok.assoc = pattern->assoc;
			tok.precedence = pattern->precedence;
 
			if (pattern->precedence > 0)
				tok.precedence = pattern->precedence + precedence_booster;
			else if (pattern->precedence == -1) {
				if (precedence_booster < 100) {
					fail("unmatched )", s);
				}
				tok.precedence = precedence_booster;
			}
 
			while (l_stack) {
				t = stack + l_stack - 1;
				if (!(t->precedence == tok.precedence && t->assoc == A_L)
					&& t->precedence <= tok.precedence) {
						break;
					}
				t_token tmp = spop();
				t_dlist_node *tmp_node = t_dlist_pop(dl_stack, dl_stack->tail);
				t_dlist_append(dl_queue, tmp_node);
				qpush(tmp);
			}
 
			if (pattern->precedence == -1) {
				precedence_booster -= 100;
			} else {
				break ;
			}
		}

		if (!pattern->precedence) {
			if (precedence_booster) {
				fail("unmatched (", s);
			}
			t_dlist_free(dl_stack, free_node);
			t_dlist_free(dl_funct, free_node);
			transit.list = dl_queue;
			return transit;
		}
		t_dlist_append(dl_stack, t_dlist_node_new(ft_strndup(tok.s, tok.len), sizeof(char)));
		spush(tok);
	}
 
	if (pattern->precedence > 0) {
		fail("unexpected eol", s);
	}
	t_dlist_free(dl_stack, free_node);
	t_dlist_free(dl_funct, free_node);
	transit.list = dl_queue;
	//printf("%s\n", "parse_end");
	return transit;
}
 
