#ifndef SMARTCALC_H
#define SMARTCALC_H

#include <regex.h>
#include "dlist.h"
#include "types.h"
#include <string.h>
#include <stdbool.h>

#define SEPARATOR ' '

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

typedef struct {
    double amount;
    int term_in_months;
    double interest_rate;
    int type;
} t_credit_input;

enum e_credit_type {
    DIFFERENTIATED,
    ANNUITY
};

typedef struct {
	int month;
	double amount;
} t_transaction;

typedef struct {
	double amount;
	int term_in_months;
	double interest_rate;
	double tax_rate;
	char *repl_months;
	char *repl_amounts;
	char *with_months;
	char *with_amounts;
	bool is_capitalization;
} t_deposit_input;

typedef struct {
	bool is_error;
	double accrued_interest;
	double tax_amount;
	double deposit_by_end;
	char *message;
} t_deposit_output;

typedef struct {
	double *monthly_payments;
	double overpayment;
	double total_payment;
	char *message;
	bool is_error;
} t_credit_output;

typedef struct {
	bool is_error;
	double output;
	char *message;
} t_calc_output;






int		init(void);
t_dlist *parse(const char *s);
char	*ft_strdup(const char *src);
char	*ft_strndup(const char *src, size_t n);
size_t	ft_strnlen(const char *s, size_t maxlen);
void	*ft_memalloc(size_t size);
int	handle_error(char *s);
double rpn(t_dlist *tokens, double x_val);
int equal(double a, double b);
t_credit_output *calc_annuity(t_credit_input *data);
t_credit_output *calc_differentiated(t_credit_input *data);
void print_annuity(t_credit_input data, t_credit_output *out);
void print_differentiated(t_credit_input data, t_credit_output *out);
void free_credit_output(t_credit_output *out);
char *answer_to_string(double answ);
char	**ft_strsplit(char const *s, char c);

#endif