
#include <stdio.h>
#include <string.h>
#include "smartcalc.h"


extern int debug;

t_pattern end_of_string = {"", A_NONE, 0, {0}};
 
t_pattern operands[] = {
	{"^\\)",	A_NONE, -1, {0}},
	{"^\\*\\*",	A_R, 3, {0}},
	{"^\\^",	A_R, 3, {0}},
	{"^\\*",	A_L, 2, {0}},
	{"^/",		A_L, 2, {0}},
	{"^\\+",	A_L, 1, {0}},
	{"^-",		A_L, 1, {0}},
	{0}
};
 
t_pattern arguments[] = {
	{"^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?", 0, 0, {0}},
	{"^[a-zA-Z_][a-zA-Z_0-9]*", 0, 0, {0}},
	{"^\\(", A_L, -1, {0}},
	{0}
};



t_token stack[256]; /* assume these are big enough */
t_token queue[256];
t_dlist *dl_stack;
t_dlist *dl_queue;

int l_queue, l_stack;
#define qpush(x) queue[l_queue++] = x
#define spush(x) stack[l_stack++] = x
#define spop()   stack[--l_stack]
#define WHITE_SPACE " \t"
 
static void display(const char *s)
{
	if (!debug) {
		return ;
	}
	int i;
	printf("\033[1;1H\033[JText | %s", s);
	printf("\nStack| ");
	for (i = 0; i < l_stack; i++)
		printf("%.*s ", stack[i].len, stack[i].s); // uses C99 format strings
	printf("\nQueue| ");
	for (i = 0; i < l_queue; i++)
		printf("%.*s ", queue[i].len, queue[i].s);
	puts("\n\n<press enter>");
	getchar();
}
 
int precedence_booster;

 
#define fail(s1, s2) {fprintf(stderr, "[Error %s] %s\n", s1, s2); return 0;}
 
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

	dl_stack = t_dlist_new();
	dl_queue = t_dlist_new();
	return 1;
}
 
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
 
int parse(const char *s) {
	t_pattern *pattern;
	t_token *t, tok;
 
	precedence_booster = l_queue = l_stack = 0;
	display(s);
	while (*s) {
		pattern = match(s, arguments, &tok, &s);
		if (!pattern || pattern == &end_of_string) {
			fail("parse arg", s);
		}
 
		if (pattern->precedence == -1) {
			precedence_booster += 100;
			continue;
		}
		t_dlist_append(dl_queue, t_dlist_node_new(ft_strndup(tok.s, tok.len), sizeof(char)));
		qpush(tok);
		display(s);
 
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
				t_dlist_append(dl_queue, t_dlist_pop(dl_stack, dl_stack->head));
				qpush(spop());
				display(s);
			}
 
			if (pattern->precedence == -1) {
				precedence_booster -= 100;
			} else {
				break ;
			}
		}

		if (!pattern->precedence) {
			display(s);
			if (precedence_booster)
				fail("unmatched (", s);

			printf("Queue: %d\n", dl_queue->size);
			t_dlist_node *tmp = dl_queue->head;
			while (tmp) {
				printf("%s \n", (char *)tmp->data);
				tmp = tmp->next;
			}
			printf("\n");
			dl_stack = NULL;
			dl_queue = NULL;

			
			for (int o = 0; o < l_queue; o++) {
				printf("%s ", queue[o].s);
			}
			printf("\n");
			return 1;
		}
		t_dlist_append(dl_stack, t_dlist_node_new(ft_strndup(tok.s, tok.len), sizeof(char)));
		spush(tok);
		display(s);
	}
 
	if (pattern->precedence > 0) {
		fail("unexpected eol", s);
	}

	
	return 1;
}
 
