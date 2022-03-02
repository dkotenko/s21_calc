#include "smartcalc.h"

t_deposit_output calc_deposit(t_deposit_input input)
{
    t_deposit_output output;
    output.message = NULL;
    
    while (input.tax_rate >= 1) {
        input.tax_rate /= 10;
    }

    //validation
    /*
        repl => 0
        with <= 0

        output.is_error = 1;
        output.message = ft_strdup("invalid replenishments data");
        return output;

    */


    double amount = input.amount;
    double int_per_month = input.interest_rate / 12;
    double accr_interest[input.term_in_months];
    double total_accr_interest = 0;
    int repl_counter = 1;
    int with_counter = 1;
    for (int i = 0; i < input.term_in_months; i++) {
        if (repl_counter == input.repl_every_n_month) {
            amount += input.repl_amount;
            repl_counter = 1;
        }
        if (with_counter == input.with_every_n_month) {
            amount -= input.with_amount;
            if (amount < 0) {
                amount = 0;
            }
            with_counter = 1;
        }
        accr_interest[i] = amount * int_per_month;
        total_accr_interest += accr_interest[i];
        if (input.is_capitalization) {
            amount += accr_interest[i];
        }
    }
    output.accrued_interest = total_accr_interest;
    output.tax_amount = total_accr_interest * input.tax_rate;
    output.deposit_by_end = amount;
    return output;
}