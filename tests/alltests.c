#include "../rsa.h"
#include "rsa_test.h"
#include "CuTest.h"
#include <stdio.h>

void RunAllTests(void){
    CuString *output = CuStringNew();
    CuSuite* suite = RSAMathGetSuite();

    CuSuiteRun(suite);

    CuSuiteSummary(suite, output);
    printf("%s\n", output->buffer);
}

int main(int argc, char** argv){
    RunAllTests();
}
