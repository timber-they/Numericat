#include <check.h>
#include "Check_Parser.h"

int main(void)
{
    Suite *parserSuite = suite_create("Parser");
//    Suite *solverSuite = solver_suite("Solver");
    TCase *parserCase1 = tcase_create("Unit tests");
//    TCase *solverCase1 = tcase_create("Solver");
    SRunner *sr = srunner_create(parserSuite);
//    srunner_add_suite(sr, solverSuite);
    int nf;

    suite_add_tcase(parserSuite, parserCase1);
//    suite_add_tcase(solverSuite, solverCase1);

    tcase_add_test(parserCase1, test_Parse_Functions);
    tcase_add_test(parserCase1, test_Parse_Failing);

    srunner_run_all(sr, CK_NORMAL);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
