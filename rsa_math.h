#ifndef RSA_MATH_H
#define RSA_MATH_H
#include "gmp.h"

void rsampz_mulmod(mpz_t r, mpz_t i, mpz_t m, mpz_t mod);

void rsa_rsh(mpz_t r, mpz_t i);

void rsa_mod_pow(mpz_t r, mpz_t a, mpz_t p, mpz_t m);

void rsa_mmi(mpz_t r, mpz_t a, mpz_t m);

void euclid_gcd(mpz_t a, mpz_t b);

int rsa_prime_test(mpz_t test);

#endif // RSA_MATH_H
