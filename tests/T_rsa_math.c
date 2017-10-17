#include "../rsa.h"
#include "rsa_test.h"
#include <stdio.h>
#include "gmp.h"
#include "CuTest.h"

void t_rsamulmod(CuTest* tc){
    int end;
    mpz_t m1, m2, mod, result;

    end = 23;

    mpz_init_set_si(m1, 40);
    mpz_init_set_si(m2, 13);
    mpz_init_set_si(mod, 497);
    mpz_init(result);

    rsampz_mulmod(result, m1, m2, mod);

    gmp_printf("%Zd * %Zd (mod. %Zd) = %Zd\n", m1, m2, mod, result);

    CuAssertTrue(tc, !(mpz_cmp_si(result, end)));
    mpz_clears(m1, m2, mod, result, NULL);
}

void t_rsa_rsh_even(CuTest* tc){
    int start, end;
    mpz_t result;
    
    start = 2048;
    end = 1024;

    mpz_init_set_si(result, start);
    rsa_rsh(result, result);

    gmp_printf("%d >> 1 = %Zd\n", start, result);
    
    CuAssertIntEquals(tc,mpz_get_si(result), end);
    mpz_clear(result);
}

void t_rsa_rsh_odd(CuTest* tc){
    int start, end;
    mpz_t result;
    
    start = 2047;
    end = 1023;

    mpz_init_set_si(result, start);
    rsa_rsh(result, result);

    gmp_printf("%d >> 1 = %Zd\n", start, result);
    
    CuAssertIntEquals(tc, mpz_get_si(result), end);
    mpz_clear(result);
}

void t_rsa_mod_pow(CuTest* tc){
    int end;
    mpz_t base, exp, mod, result;

    end = 445;

    mpz_init_set_si(base, 4);
    mpz_init_set_si(exp, 13);
    mpz_init_set_si(mod, 497);
    mpz_init(result);
    
    rsa_mod_pow(result, base, exp, mod);

    gmp_printf("%Zd ^ %Zd (mod. %Zd) = %Zd\n", base, exp, mod, result);
    
    CuAssertTrue(tc, !(mpz_cmp_si(result, end)));
    mpz_clears(base, exp, mod, result, NULL);
}

void t_rsa_gcd_dcrmt(CuTest* tc){
    int end;
    mpz_t a, b, result;

    end = 4;

    mpz_init_set_si(a, 41);
    mpz_init_set_si(b, 13);
    mpz_init(result);
    
    rsa_gcd_dcrmt(result, a, b);

    gmp_printf("gcd((%Zd - 1),(%Zd - 1)) = %Zd\n", a, b, result);
    
    CuAssertTrue(tc, !(mpz_cmp_si(result, end)));
    mpz_clears(a, b, result, NULL);
}

void t_euclid_gcd(CuTest* tc){
    int end;
    mpz_t a, b, result;

    end = 1;

    mpz_init_set_si(a, 41);
    mpz_init_set_si(b, 19);
    mpz_init(result);
    
    euclid_gcd(a, b);

    gmp_printf("gcd((%Zd - 1),(%Zd - 1)) = %Zd\n", a, b, result);
    
    CuAssertTrue(tc, !(mpz_cmp_si(a, end)) || !mpz_cmp_si(b, end));
    mpz_clears(a, b, result, NULL);
}

void t_rsa_prime_inc_even(CuTest* tc){
    int end;
    mpz_t a;

    end = 41;

    mpz_init_set_si(a, 40);
    
    rsa_prime_inc(a);

    gmp_printf("Prime after %d is %Zd\n", 40, a);
    
    CuAssertTrue(tc, !(mpz_cmp_si(a, end)));
    mpz_clear(a);
}

void t_rsa_prime_inc_odd(CuTest* tc){
    int end;
    mpz_t a;

    end = 128189;

    mpz_init_set_si(a, 128188);
    
    rsa_prime_inc(a);

    gmp_printf("Prime after %d is %Zd\n", end-1, a);
    
    CuAssertTrue(tc, !(mpz_cmp_si(a, end)));
    mpz_clear(a);
}

void t_rsa_prime_test_comp(CuTest* tc){
    int end, is_prime;
    mpz_t a;

    end = 0; // false since not prime

    mpz_init_set_si(a, 45);
    
    is_prime = rsa_prime_test(a);

    gmp_printf("Is %Zd prime? %d\n", a, is_prime);
    
    CuAssertTrue(tc, end == is_prime);
    mpz_clear(a);
}

void t_rsa_prime_test_prime(CuTest* tc){
    int end, is_prime;
    mpz_t a;

    end = 1; // true since prime

    mpz_init_set_si(a, 128189);
    
    is_prime = rsa_prime_test(a);

    gmp_printf("Is %Zd prime? %d\n", a, is_prime);
    
    CuAssertTrue(tc, is_prime == end);
    mpz_clear(a);
}

void t_rsa_mmi(CuTest* tc){
    int end;
    mpz_t a, b, m;
    mpz_init(b);
    mpz_init_set_si(a, 21);
    mpz_init_set_si(m, 47);

    end = 9; 

    rsa_mmi(b, a, m);
    
    gmp_printf("%Zd * %Zd \\equiv 1 (mod. %Zd)\n", a, b, m);
    
    CuAssertTrue(tc, !mpz_cmp_si(b, end));
    mpz_clears(a, b, m, NULL);

}

void t_mpz_mult_sub_swap(CuTest* tc){
    void mpz_mult_sub_swap(mpz_t a, mpz_t b, mpz_t mul, mpz_t temp);
    int end_a, end_b;
    mpz_t a, b, mul, temp;
    mpz_init(temp);
    mpz_init_set_si(a, 240);
    mpz_init_set_si(b, 46);
    mpz_init_set_si(mul, 5);

    end_a = 46;
    end_b = 10;

    mpz_mult_sub_swap(a, b, mul, temp);
    
    gmp_printf("%d - (%Zd * %Zd) = %Zd\n", 240, a, mul, b);
    
    CuAssertTrue(tc, !mpz_cmp_si(a, end_a));
    CuAssertTrue(tc, !mpz_cmp_si(b, end_b));
    mpz_clears(a, b, mul, temp, NULL);

}

void t_encryption(CuTest* tc){
    int end;
    mpz_t n, d, e, m;

    end = 47; 

    mpz_init_set_si(n, 3233);
    mpz_init_set_si(d, 17);
    mpz_init_set_si(e, 413);
    mpz_init_set_si(m, 47);

    rsa_mod_pow(m, m, d, n);
    rsa_mod_pow(m, m, e, n);
    
    gmp_printf("%Zd == %d\n",m , end);
    
    CuAssertTrue(tc, !mpz_cmp_si(m, end));
    mpz_clears(n, d, e, m, NULL);
}

CuSuite* RSAMathGetSuite() {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, t_rsamulmod);
    SUITE_ADD_TEST(suite, t_rsa_rsh_even);
    SUITE_ADD_TEST(suite, t_rsa_rsh_odd);
    SUITE_ADD_TEST(suite, t_rsa_mod_pow);
    SUITE_ADD_TEST(suite, t_euclid_gcd);
    SUITE_ADD_TEST(suite, t_rsa_gcd_dcrmt);
    SUITE_ADD_TEST(suite, t_rsa_prime_test_comp);
    SUITE_ADD_TEST(suite, t_rsa_prime_test_prime);
    SUITE_ADD_TEST(suite, t_rsa_prime_inc_even);
    SUITE_ADD_TEST(suite, t_rsa_prime_inc_odd);
    SUITE_ADD_TEST(suite, t_rsa_mmi);
    SUITE_ADD_TEST(suite, t_mpz_mult_sub_swap);
    SUITE_ADD_TEST(suite, t_encryption);
    

    return suite;     
}
