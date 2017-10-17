#ifndef RSA_H
#define RSA_H
#include "gmp.h"

int quiet;

int main(int argc, char** argv);

void key_gen(char* t_name);

void output_key(char *name, mpz_t mult_comp, mpz_t pub_exp, mpz_t priv_exp);

void fill_random(mpz_t r); 

void rsampz_mulmod(mpz_t r, mpz_t i, mpz_t m, mpz_t mod);

void rsa_rsh(mpz_t r, mpz_t i);

void rsa_mod_pow(mpz_t r, mpz_t a, mpz_t p, mpz_t m);

void rsa_mmi(mpz_t r, mpz_t a, mpz_t m);

void euclid_gcd(mpz_t a, mpz_t b);

void rsa_gcd_dcrmt(mpz_t r, mpz_t a, mpz_t b);

int rsa_prime_test(mpz_t test);

void rsa_prime_inc(mpz_t test);


void encrypt(char *filename, char *message);

void decrypt(char *filename);

#endif // RSA_H
