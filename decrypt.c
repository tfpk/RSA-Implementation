#include "rsa.h"
#include <stdio.h>
#include <string.h>
#include "gmp.h"

void get_private_file(char* filename, mpz_t pub_mult, mpz_t priv_mmi){
     FILE *pub_key;
     pub_key = fopen(filename, "r");
     gmp_fscanf(pub_key, "---BEGIN RSA PRIVATE (@tfpk) KEY ---\n%Zx\n%Zx", pub_mult, priv_mmi);
}

void decrypt(char *filename){
    char message[1024];
    size_t message_size;
    
    mpz_t     pub_mult, priv_mmi, cipher_int, result;
    mpz_inits(pub_mult, priv_mmi, cipher_int, result, NULL);

    get_private_file(filename, pub_mult, priv_mmi);

    if (!quiet) gmp_printf("decrypt: ");
    gmp_scanf("%Zx", cipher_int);

    // result = cipher_int ^ priv_mmi % pub_mult
    rsa_mod_pow(result, cipher_int, priv_mmi, pub_mult);

    // write int to char: output, write length, direction of write, size of limb, endian-ness, ignore space, input
    mpz_export(message, &message_size, 1, sizeof(message[0]), 1, 1, result);
    message[message_size] = '\x0';

    printf("%s\n", message);

    mpz_clears(pub_mult, priv_mmi, cipher_int, result, NULL);
}
