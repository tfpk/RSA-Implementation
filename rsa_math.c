#include "rsa.h"
#include <stdio.h>
#include "gmp.h"

// r = (m1*m2)%mod
void rsampz_mulmod(mpz_t r, mpz_t m1, mpz_t m2, mpz_t mod){
    mpz_mul(r, m1, m2); // r = m1 * m2
    mpz_mod(r, r, mod); // r = r % mod
}

// rsa right shift (r = i>>1)
void rsa_rsh(mpz_t r, mpz_t i){
    mpz_set(r, i);                         // r = i
    if (mpz_odd_p(i)) mpz_sub_ui(i, i, 1); // if i is odd, sub one to make it div by 2
    mpz_divexact_ui(r, i, 2);              // r = i // 2
}

// modpow with r = b^e (mod. m)
void rsa_mod_pow(mpz_t r, mpz_t b, mpz_t e, mpz_t m){
    mpz_t b_temp, e_temp;
    mpz_init_set(b_temp, b); // b_temp = b
    mpz_init_set(e_temp, e); // e_temp = e
    
    mpz_set_ui(r, 1);
    while (mpz_cmp_si(e_temp, 0) > 0){                         // e_temp > 0
        if (mpz_odd_p(e_temp)) rsampz_mulmod(r, r, b_temp, m); // r = (r ^ b_temp) % m
        rsa_rsh(e_temp, e_temp);                               // r >>= 1
        rsampz_mulmod(b_temp, b_temp, b_temp, m);              // b_temp = b_temp^2 % m
    }
    mpz_clears(b_temp, e_temp, NULL);
}

// a, b = b, a - (b * mul)
void mpz_mult_sub_swap(mpz_t a, mpz_t b, mpz_t mul, mpz_t temp){
    mpz_mul(temp, b, mul); // temp = b * mul
    mpz_sub(a, a, temp);   // a -= temp
    mpz_swap(a, b);        // a, b = b, a
}

void euclid_ext(mpz_t a, mpz_t b, mpz_t *s, mpz_t *t, mpz_t q){
    // assert a > b
    if (!mpz_cmp_si(b, 0)) return; // if (b == 0) return
    mpz_t temp;
    mpz_init(temp);
    mpz_tdiv_q(q, a, b); // q = a / b // truncate, quotient only

    // perform the extended ext
    mpz_mult_sub_swap(a, b, q, temp);
    mpz_mult_sub_swap(s[0], s[1], q, temp);
    mpz_mult_sub_swap(t[0], t[1], q, temp);

    mpz_clear(temp);
    euclid_ext(a, b, s, t, q);
}

void rsa_mmi(mpz_t r, mpz_t a, mpz_t m){
    // assert a < m
    mpz_t a_temp, m_temp, s[2], t[2], q;
    mpz_inits(a_temp, m_temp, s[0], s[1], t[0], t[1], q, NULL);
    mpz_set(a_temp, a);
    mpz_set(m_temp, m);
    mpz_set_ui(s[0], 1); mpz_set_ui(s[1], 0);
    mpz_set_ui(t[0], 0); mpz_set_ui(t[1], 1);

    euclid_ext(m_temp, a_temp, s, t, q);

    mpz_set(r, t[0]);
    mpz_mod(r, r, m);

    mpz_clears(a_temp, m_temp, s[0], s[1], t[0], t[1], q, NULL);
}

// recursive implementation of euclid's algorithm
void euclid_gcd(mpz_t a, mpz_t b){
    if (mpz_cmp(a, b) < 0) mpz_swap(a, b); // assert a > b
    if (mpz_cmp_si(b, 0) > 0){
        mpz_mod(a, a, b);                  // b = a % b
        
        // given above code, b and a have swapped roles
        mpz_swap(a, b); 
        euclid_gcd(a, b);
    } 
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

int PRIMES[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}; 

int rsa_prime_test(mpz_t test){
    int i, return_val;
    mpz_t prime, test_dcrmt, result;
    mpz_inits(prime, test_dcrmt, result, NULL);
    return_val = 1;
    for (i = 0; i < 10; i ++){
        mpz_set_ui(prime, PRIMES[i]);
        mpz_set(test_dcrmt, test);
        mpz_sub_ui(test_dcrmt, test_dcrmt, 1);
        rsa_mod_pow(result, prime, test_dcrmt, test);
        if (mpz_cmp_si(result, 1)) return_val = 0; // result != 1
    }
    mpz_clears(prime, test_dcrmt, result, NULL);
    return return_val;
}

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

