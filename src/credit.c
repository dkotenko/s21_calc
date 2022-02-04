#include "smartcalc.h"

enum e_credit_type {
    DIFFERENTIATED,
    ANNUITY
}

typedef struct {
    double amount;
    int term_in_months;
    double interest_rate;
    int type;
} t_credit;

long long calc_annuity(t_credit data)
{
    //a - сумма 
    //a = k * s;
    //k = (i * pow((1 + i), n)) / (pow((1 + i), n) - 1);

    double sum = 2000;
    double rate = 0.48;
    double rate_per_month = rate / 12;
    double term = 4;
    double term_in_months = term * 12;
    

    double rate_months = pow((1 + rate_per_month), term_in_months);
    double annuity_coef = (rate_per_month * rate_months) / (rate_months - 1);
    double annuity_payment = annuity_coef * sum;

    return annuity_payment;
}

long calc_differentiated(t_credit data)
{
    double sum = 18000.;
    double term = 3;
    double term_in_months = term * 12;
    double credit_body = sum / term_in_months;
    return 0;
}
void calc_credit(void)
{
	;
}