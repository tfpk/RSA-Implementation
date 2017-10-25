#ifndef RSA_H
#define RSA_H
#include "gmp.h"

// -q flag: won't print to stdout
int quiet;

int main(int argc, char** argv);

void key_gen(char* t_name);

void fill_random(mpz_t r); 

void output_key(char *name, mpz_t mult_comp, mpz_t pub_exp, mpz_t priv_exp);


void encrypt(char *filename, char *message);

void decrypt(char *filename);

#endif // RSA_H
