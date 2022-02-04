#ifndef SMARTCALC_H
#define SMARTCALC_H

#include <regex.h>
#include "dlist.h"
#include "types.h"
#include <string.h>

typedef struct s_token {
	const char *s;
	int len;
	int precedence;
	int assoc;
} t_token;
 
typedef struct s_pattern {
	const char * str;
	int assoc;
	int precedence;
	regex_t re;
} t_pattern;
 
enum assoc {
	A_NONE,
	A_L,
	A_R
};

int		init(void);
t_dlist *parse(const char *s);
char	*ft_strdup(const char *src);
char	*ft_strndup(const char *src, size_t n);
size_t	ft_strnlen(const char *s, size_t maxlen);
void	*ft_memalloc(size_t size);
int	handle_error(char *s);
double rpn(t_dlist *tokens);
int equal(double a, double b);
void calc_credit(void);

#endif