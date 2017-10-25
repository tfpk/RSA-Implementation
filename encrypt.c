#include "rsa.h"
#include "rsa_math.h"
#include <stdio.h>
#include <string.h>
#include "gmp.h"

void get_public_file(char* filename, mpz_t pub_mult, mpz_t pub_mmi){
     FILE *pub_key;
     pub_key = fopen(filename, "r");
     gmp_fscanf(pub_key, "---BEGIN RSA PUBLIC (@tfpk) KEY ---\n%Zx\n%Zx", pub_mult, pub_mmi);
}

void encrypt(char *filename, char *message){
    mpz_t     pub_mult, pub_mmi, message_int, result;
    mpz_inits(pub_mult, pub_mmi, message_int, result, NULL);

    get_public_file(filename, pub_mult, pub_mmi);

    // write char to int: output, length to write, direction of write, size of limb, endian-ness, ignore space, input
    mpz_import(message_int, strlen(message), 1, sizeof(message[0]), 1, 1, message);

    // actual rsa calculation
    rsa_mod_pow(result, message_int, pub_mmi, pub_mult); // result = message_int ^ pub_mmi % pub_mult

    gmp_printf("%Zx\n", result);

    mpz_clears(pub_mult, pub_mmi, message_int, result, NULL);
}
