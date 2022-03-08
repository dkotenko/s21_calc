#include "tests.h"

int main(void) {
    int no_failed = 0;                   
    SRunner *runner;
    
    runner = srunner_create(calculation_suite());          
    srunner_add_suite(runner, deposit_suite());
    srunner_add_suite(runner, credit_suite());
    
    
    srunner_run_all(runner, CK_NORMAL);  
    no_failed = srunner_ntests_failed(runner); 
    srunner_free(runner);                      
    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;  
}