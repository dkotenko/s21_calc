#include "smartcalc.h"
#include <math.h>
#include <stdio.h>

#define ERR_CREDIT_AMOUNT "invalid credit amount"
#define ERR_CREDIT_TERM "invalid credit term"
#define ERR_CREDIT_RATE "invalid interest rate"

enum e_credit_type {
    DIFFERENTIATED,
    ANNUITY
};

void print_annuity(t_credit_inputdata, t_credit_output *out)
{
    char *two = "  ";
    char *four = "    ";
    printf("credit with annuity payment:\n");
    printf("%sinput:\n", two);
    printf("%stotal credit amount: %lf\n", four, data.amount);
    printf("%sterm in months: %d\n", four, data.term_in_months);
    printf("%sinterest rate: %lf\n", four, data.interest_rate);
    printf("%soutput:\n", two);
    printf("%smonthly payment: %lf\n", four, out->monthly_payments[0]);
    printf("%soverpayment: %lf\n", four, out->overpayment);
    printf("%stotal amount: %lf\n", four, out->total_payment);
}

void print_differentiated(t_credit_inputdata, t_credit_output *out)
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
        printf("month %d: %lf\n", i + 1, out->monthly_payments[i]);
    }
    printf("%soverpayment: %lf\n", four, out->overpayment);
    printf("%stotal amount: %lf\n", four, out->total_payment);
}

void free_credit_output(t_credit_output *out)
{
    free(out->monthly_payments);
    free(out);
}

char *validate_credit(t_credit_inputdata)
{
    char *message = NULL;

    if (data.amount <= 0 || data.term_in_months <= 0 || data.interest_rate <= 0) {
        if (data.amount < 0) {
            message = ft_strdup(ERR_CREDIT_AMOUNT);
        } else if (data.term_in_months <= 0) {
            message = ft_strdup(ERR_CREDIT_TERM);
        } else if (data.interest_rate <= 0) {
            message = ft_strdup(ERR_CREDIT_RATE);
        }
    }
    return message;
}

t_credit_output *calc_annuity(t_credit_input*data)
{
    //a - сумма 
    //a = k * s;
    //k = (i * pow((1 + i), n)) / (pow((1 + i), n) - 1);
    t_credit_output *out = ft_memalloc(sizeof(t_credit_output));
    char *is_error = validate_credit(*data);
    if (is_error) {
        out->message = is_error;
        return out;
    }

    data->amount = 2000;
    data->term_in_months = 48;
    data->interest_rate = 0.48;

    double sum = data->amount;
    double rate = data->interest_rate;
    double rate_per_month = rate / 12;
    double term_in_months = data->term_in_months;
    

    double rate_months = pow((1 + rate_per_month), term_in_months);
    double annuity_coef = (rate_per_month * rate_months) / (rate_months - 1);
    double annuity_payment = annuity_coef * sum;
    
    out->total_payment = annuity_payment * term_in_months;
    out->overpayment = out->total_payment - sum;

    out->monthly_payments = ft_memalloc(sizeof(double) * term_in_months);
    for (int i = 0; i < term_in_months; i++) {
        out->monthly_payments[i] = annuity_payment;
    }
    return out;
}

/*
 *  dp = s / n + od * (i / k)
 *  where:
 *      dp - diff payment
 *      s - credit sum
 *      od - credit leftover for recent date
 *      i - annual credit rate
 *      k - number of credit periods per year
 *      n - number of credit periods per credit
 */
t_credit_output *calc_differentiated(t_credit_input*data)
{    
    
    data->amount = 1000000.; 
    data->term_in_months = 12;
    data->interest_rate = 0.12;

    double rate = data->interest_rate;
    double rate_per_month = rate / 12;
    double sum = data->amount;
    double term_in_months = data->term_in_months;
    double credit_leftover = sum;
    double sum_per_month = sum / term_in_months;

    t_credit_output *out = ft_memalloc(sizeof(t_credit_output));
    out->monthly_payments = ft_memalloc(sizeof(double) * term_in_months);

    for (int i = 0; i < data->term_in_months; i++) {
        out->monthly_payments[i] = sum / term_in_months +\
            credit_leftover * rate_per_month;
        credit_leftover -= sum_per_month;
        out->total_payment += out->monthly_payments[i];
    }
    out->overpayment = out->total_payment - sum;
    return out;
}
