#define _POSIX_C_SOURCE  200809L
#define _GNU_SOURCE
#include "smartcalc.h"
#include <unistd.h>
#include <float.h>
#include <stdio.h>

#define ERR_MALLOC "MALLOC FAILED"
#define ERR_MALLOC_SIZE "INVALID MALLOC SIZE"
#define EPSILON 0.0000001

static void	*ft_memset(void *destination, int c, size_t n)
{
	unsigned char	*s;

	s = (unsigned char *)destination;
	while (n > 0)
	{
		*(s++) = (unsigned char)c;
		n--;
	}
	return (destination);
}

void	*ft_memalloc(size_t size)
{
	void	*a;

	if (size + 1 < size)
		handle_error(ERR_MALLOC_SIZE);
	a = malloc(size);
	if (!a)
		handle_error(ERR_MALLOC);
	ft_memset(a, 0, size);
	return (a);
}

char	*ft_strdup(const char *src)
{
	char			*dupl;
	unsigned int	len;

	len = strlen(src);
	dupl = (char *)ft_memalloc((len + 1) * sizeof(char));
	
	len = 0;
	while (src[len])
	{
		dupl[len] = src[len];
		len++;
	}
	return (dupl);
}

char	*ft_strndup(const char *src, size_t n)
{
	char	*dst;
	size_t	i;

	dst = (char *)ft_memalloc((ft_strnlen(src, n) + 1) * sizeof(char));
	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	i;

	i = 0;
	while (i < maxlen && s[i])
		++i;
	return (i);
}

int	handle_error(char *s)
{
	dprintf(STDERR_FILENO, "ERROR:\t%s\n", s);
	exit(0);
}

int equal(double a, double b)
{
	return a - b < EPSILON;
}

void print_annuity(t_credit_input data, t_credit_output out)
{
    char *two = "  ";
    char *four = "    ";
    printf("credit with annuity payment:\n");
    printf("%sinput:\n", two);
    printf("%stotal credit amount: %lf\n", four, data.amount);
    printf("%sterm in months: %d\n", four, data.term_in_months);
    printf("%sinterest rate: %lf\n", four, data.interest_rate);
    printf("%soutput:\n", two);
    printf("%smonthly payment: %lf\n", four, out.monthly_payments[0]);
    printf("%soverpayment: %lf\n", four, out.overpayment);
    printf("%stotal amount: %lf\n", four, out.total_payment);
}

void print_differentiated(t_credit_input data, t_credit_output out)
{
    char *two = "  ";
    char *four = "    ";
    printf("credit with differentiated payment:\n");
    printf("%sinput:\n", two);
    printf("%stotal credit amount: %lf\n", four, data.amount);
    printf("%sterm in months: %d\n", four, data.term_in_months);
    printf("%sinterest rate: %lf\n", four, data.interest_rate);
    printf("%soutput:\n", two);
    printf("%smonthly payments: \n", four);
    for (int i = 0; i < data.term_in_months; i++) {
        printf("month %d: %lf\n", i + 1, out.monthly_payments[i]);
    }
    printf("%soverpayment: %lf\n", four, out.overpayment);
    printf("%stotal amount: %lf\n", four, out.total_payment);
}


