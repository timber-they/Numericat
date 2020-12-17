#include <check.h>
#include "Check_Parser.h"
#include "Check_Function.h"
#include "Check_Matrix.h"

int main(void)
{
    Suite *parserSuite = suite_create("Parser");
    Suite *solverSuite = suite_create("Solver");
    
    TCase *parserCase1 = tcase_create("Parser");
    TCase *parserCase2 = tcase_create("Function");
    TCase *solverCase1 = tcase_create("Solver");
    SRunner *sr = srunner_create(parserSuite);
    srunner_add_suite(sr, solverSuite);
    int nf;

    suite_add_tcase(parserSuite, parserCase1);
    suite_add_tcase(parserSuite, parserCase2);
    suite_add_tcase(solverSuite, solverCase1);

    tcase_add_test(parserCase1, test_Parse_Functions);
    tcase_add_test(parserCase1, test_Parse_Failing);
    tcase_add_test(parserCase2, test_Evaluate);
    tcase_add_test(solverSuite, test_determinant);
    tcase_add_test(solverSuite, test_Inverse);
    tcase_add_test(solverSuite, test_multiply);

    srunner_run_all(sr, CK_NORMAL);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
