#define RSA_TEST

#ifdef RSA_TEST
#include "CuTest.h"

void t_rsamulmod(CuTest* tc);
void t_rsa_rsh_even(CuTest* tc);
void t_rsa_rsh_odd(CuTest* tc);
void t_rsa_mod_pow(CuTest* tc);
void t_rsa_gcd_dcrmt(CuTest* tc);
void t_euclid_gcd(CuTest* tc);
void t_rsa_prime_test_comp(CuTest* tc);
void t_rsa_prime_test_prime(CuTest* tc);
void t_rsa_prime_inc_even(CuTest* tc);
void t_rsa_prime_inc_odd(CuTest* tc);

// test utilities

CuSuite* RSAMathGetSuite();

void RunAllTests();

#endif // RSA_TEST

