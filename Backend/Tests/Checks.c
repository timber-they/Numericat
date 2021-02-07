#include <check.h>
#include "Check_Parser.h"
#include "Check_Function.h"
#include "Check_Matrix.h"
#include "Check_Complex.h"

int main(void)
{
    Suite *parserSuite = suite_create("Parser");
    Suite *solverSuite = suite_create("Solver");

    TCase *parserCase1 = tcase_create("Parser");
    TCase *parserCase2 = tcase_create("Function");
    TCase *solverCase1 = tcase_create("Solver");
    TCase *complexCase1 = tcase_create("Complex");

    SRunner *sr = srunner_create(parserSuite);
    srunner_add_suite(sr, solverSuite);
    int nf;

    suite_add_tcase(parserSuite, parserCase1);
    suite_add_tcase(parserSuite, parserCase2);
    suite_add_tcase(solverSuite, solverCase1);
    suite_add_tcase(solverSuite, complexCase1);

    tcase_add_test(parserCase1, test_Parse_Functions);
    tcase_add_test(parserCase1, test_Parse_Failing);
    tcase_add_test(parserCase1, test_Validate_Dyck);
    tcase_add_test(parserCase1, test_Validate_Dyck_Failing);
    tcase_add_test(parserCase2, test_Evaluate);
    tcase_add_test(solverCase1, test_multiply);
    tcase_add_test(solverCase1, test_identity);
    tcase_add_test(solverCase1, test_multiply_3x3);
    tcase_add_test(solverCase1, test_ones);
    tcase_add_test(solverCase1, test_sum);
    tcase_add_test(solverCase1, test_Matrixsubtract);
    tcase_add_test(solverCase1, test_factor);
    tcase_add_test(solverCase1, test_arrayToMatrix);
    tcase_add_test(solverCase1, test_MatrixToArray);
    tcase_add_test(solverCase1, test_thomas);
    tcase_add_test(solverCase1, test_sumComplexMatrix);
    tcase_add_test(solverCase1, test_ComplexmultiplyMatrix);
    tcase_add_test(solverCase1, test_ComplexMatrixsubtract);
    tcase_add_test(solverCase1, test_ComplexFactor);
    tcase_add_test(complexCase1, test_sumComplex);
    tcase_add_test(complexCase1, test_subtractComplex);
    tcase_add_test(complexCase1, test_multiplyComplex);
    tcase_add_test(complexCase1, test_divideComplex);
    tcase_add_test(complexCase1, test_powerComplex);
    tcase_add_test(complexCase1, test_absSquareComplex);


    srunner_run_all(sr, CK_NORMAL);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
