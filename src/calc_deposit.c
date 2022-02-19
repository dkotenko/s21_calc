#include "smartcalc.h"

static int get_arr_len(char **arr)
{
    int arr_len = 0;
    while (arr[arr_len++]) ;
    return arr_len;
}

static void sort_trans_by_month(t_dlist *trans)
{
    int was_sorted = 1;
    while (was_sorted) {
        was_sorted = 0;
        t_dlist_node *tmp = trans->head;
        while (tmp) {
            if (tmp->next) {
                t_transaction *curr = (t_transaction *)tmp->data;
                t_transaction *next = (t_transaction *)tmp->next;
                if (curr->month > next->month) {
                    t_dlist_node *curr_popped = t_dlist_pop(trans, tmp);
                    t_dlist_insert_after(trans, tmp, tmp->next);
                    was_sorted = 1;
                }
            }
            tmp = tmp->next;
        }
    }
}

static t_dlist *parse_trans_to_dlist(char *months, char *amounts)
{
    if (!months || !amounts) {
        return NULL;
    }

    t_dlist *dlist = t_dlist_new();
    char **spl_months = ft_strsplit(months, SEPARATOR);
    months_arr_len = get_arr_len(spl_months);

    char **spl_amounts = ft_strsplit(amounts, SEPARATOR);
    months_arr_len = get_arr_len(spl_amounts);

    //Здесь нужен проброс ошибки парсинга и валидации наверх
    int i = 0
    while (spl_months[i] && spl_amounts[i]) {
        t_transaction *trans = ft_memalloc(sizeof(t_transaction));
        trans->month = atoi(spl_months[i]);
        trans->amount = strtod(spl_amounts[i]);
        t_dlist_append(dlist, t_dlist_node_new(trans));
        i++;
    }
    return dlist;
}

static int is_valid_trans_dlist(t_dlist *list)
{

    return TRUE;
}

t_deposit_output calc_deposit(t_deposit_input input)
{
    t_deposit_output output;
    output.message = NULL;
    
    t_transaction *repls = parse_trans_to_dlist(input.repl_months, input.repl_amounts);
    if (!is_valid_trans_dlist(repls)) {
        output.is_error = 1;
        output.message = ft_strdup("invalid replenishments data");
        return output;
    }

    t_transaction *withs = parse_trans_to_dlist(input.with_months, input.with_amounts);
    if (!is_valid_trans_dlist(withs)) {
        output.is_error = 1;
        output.message = ft_strdup("invalid withdrawals data");
        return output;
    }

    double amount = input.amount;
    double int_per_month = input.interest_rate / 12;
    t_dlist_node *tmp_repl = repls ? repls->head : NULL;
    t_dlist_node *tmp_with = withs ? withs->head : NULL;
    t_transaction *tmp = NULL;
    t_transaction *

    for (int i = 0; i < term_in_months; i++) {
        if (repls && tmp_repl_trans->month == i + 1) {
            amount += tmp_repl_trans->amount;
            tmp_repl = tmp_repl->next;
        }
        if (withs && tmp_with)
        tmp_with = tmp_with->next;
        //где капиталиация?
        //TODO calculations
    }
}