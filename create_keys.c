#include "rsa.h"
#include "rsa_math.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gmp.h>

#define MIN_LENGTH 128*8

#define PUBLIC_EXPONENT 0x10001


// fill `r` with random bits until it is MIN_LENGTH long
void fill_random(mpz_t r){
    srand(time(NULL));
    int rand_num;
    while (mpz_sizeinbase(r, 2) < MIN_LENGTH){
        // using 2^8 = 256 makes length calculation easy
        // and guarantees platform independence
        
        rand_num = rand() % 256; // generate 8 random bits
        mpz_mul_2exp(r, r, 8); // bitshift left 8 bits
        mpz_add_ui(r, r, rand_num);
    }
}

// increases the test number until it is prime
void rsa_prime_inc(mpz_t test){
    mpz_t result;
    mpz_init(result);
    if (mpz_even_p(test)) mpz_add_ui(test, test, 1); //must be odd
    
    if (!rsa_prime_test(test)){ // not a prime
        mpz_add_ui(test, test, 2);
        rsa_prime_inc(test);
    }
    mpz_clear(result);
}

// wrapper find gcd(a - 1, b - 1) so that a, b are effectively being passed by value.
void rsa_gcd_dcrmt(mpz_t r, mpz_t a, mpz_t b){
    mpz_t a_temp, b_temp;
    mpz_init_set(a_temp, a);
    mpz_init_set(b_temp, b);
    mpz_sub_ui(a_temp, a_temp, 1);
    mpz_sub_ui(b_temp, b_temp, 1);
    // call with temporary values to be modified
    euclid_gcd(a_temp, b_temp);
    
    mpz_set(r, a_temp);
    mpz_clears(a_temp, b_temp, NULL);
}

// write keys to file
// char* name: file-name to write to (writes private key to file-name + ".priv")
// mpz_t mult, pub_exp, priv_exp: public and private key components
void output_key(char *name, mpz_t mult, mpz_t pub_exp, mpz_t priv_exp){
    FILE *pub_key, *priv_key;
    
    pub_key = fopen(name, "w");

    fprintf(pub_key, "---BEGIN RSA PUBLIC (@tfpk) KEY ---\n");
    gmp_fprintf(pub_key, "%Zx\n%Zx", mult, pub_exp);

    fclose(pub_key);
    
    strcat(name, ".priv");
    priv_key = fopen(name, "w");

    fprintf(priv_key, "---BEGIN RSA PRIVATE (@tfpk) KEY ---\n");
    gmp_fprintf(priv_key, "%Zx\n%Zx", mult, priv_exp);

    fclose(priv_key);

}

// main key generation function, takes a name
// char* t_name: file-name to write to.
void key_gen(char* t_name){
    mpz_t r1, r2, pub_exp, priv_exp, m, m_dcrmt, gcd, ctf;

    mpz_init(r1); // r1 = 0
    mpz_init(r2); // r2 = 0
    mpz_inits(gcd, m, pub_exp, priv_exp, m_dcrmt, ctf, NULL);

    // seed r1, r2 as at least a MIN_LENGTH key
    fill_random(r1);
    rsa_prime_inc(r1);
    fill_random(r2);
    rsa_prime_inc(r2);

    // m = r1 * r2
    mpz_mul(m, r1, r2);

    // m_dcrmt = (r1 - 1) * (r2 - 1) = m - r1 - r2 + 1
    mpz_sub(m_dcrmt, m, r1); mpz_sub(m_dcrmt, m_dcrmt, r2); mpz_add_ui(m_dcrmt, m_dcrmt, 1);
    
    // gcd = gcd(r1 - 1, r2 - 1)
    rsa_gcd_dcrmt(gcd, r1, r2);
  
    // carmichel totient function = lcd(r1 - 1, r2 - 2) = m_dcrmt / gcd
    mpz_divexact(ctf, m_dcrmt, gcd);

    // const public exponent, assumes r1, r2 != e
    mpz_set_ui(pub_exp, PUBLIC_EXPONENT);
   
    rsa_mmi(priv_exp, pub_exp, ctf); // priv_exp = pub_exp^-1 mod. ctf

    output_key(t_name, m, pub_exp, priv_exp);

    mpz_clears(gcd, m, pub_exp, priv_exp, m_dcrmt, ctf, NULL);

}

