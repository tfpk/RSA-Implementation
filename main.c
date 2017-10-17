#include "rsa.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int quiet; // if true, don't print 

void PRINT_INFO(){
    printf("RSA System\nDesigned by @tfpk\nNOTE: IMPLEMENTATION NOT INTENDED FOR SECURITY\n\n");
}

int main(int argc, char** argv){
    char opt, mode, filename[100], message[64];

    if (argc == 0){
        printf("ERROR: Program requires filename and instruction.\n");
        return 1;
    }
    if (argc == 1){
        strcpy(filename, "default");
    }

    strcpy(filename, argv[argc - 1]);
    while((opt = getopt(argc, argv, "qkedh")) != -1){
        switch(opt){
            case 'k': // keygen
                mode = 'k';
                break;
            case 'e': // encrypt
                mode = 'e';
                break;
            case 'd': // decrypt
                mode = 'd';
                break;
            case 'q': // quiet mode
                quiet = 1;
                break;
            case 'h':
                PRINT_INFO();
            default:
                return 1;
        }
    }
    switch (mode){
        case 'k': // keygen
            key_gen(filename);
            if(!quiet) printf("Files Created Successfully.\n");
            break;
        case 'e': // encrypt
            if (!quiet) printf("message (max. 64 bytes): ");
            scanf("%64s", message);
            encrypt(filename, message);
            break;
        case 'd': // decrypt
            strcat(filename, ".priv"); 
            decrypt(filename);
            break;
    }
    
    

}
