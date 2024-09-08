#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <pbc/pbc.h>
#include <string.h>

int main() {
    FILE *input_file = fopen("./input", "r");
    if (!input_file) {
        fprintf(stderr, "Error opening input file.\n");
        return 1;
    }

    // Read the generator g1, message m, and private key sk from the input file
    char g1_str[1024], message[1024], sk_str[1024];
    if (!fgets(g1_str, sizeof(g1_str), input_file) ||
        !fgets(message, sizeof(message), input_file) ||
        !fgets(sk_str, sizeof(sk_str), input_file)) {
        fprintf(stderr, "Error reading input.\n");
        fclose(input_file);
        return 1;
    }
    fclose(input_file);

    // Hardcoded pairing parameters
    char param[] = "type a\n"
                   "q 8780710799663312522437781984754049815806883199414208211028653399266475630880222957078625179422662221423155858769582317459277713367317481324925129998224791\n"
                   "h 12016012264891146079388821366740534204802954401251311822919615131047207289359704531102844802183906537786776\n"
                   "r 730750818665451621361119245571504901405976559617\n"
                   "exp2 159\n"
                   "exp1 107\n"
                   "sign1 1\n"
                   "sign0 1";

    pairing_t pairing;
    if (pairing_init_set_buf(pairing, param, strlen(param))) {
        fprintf(stderr, "Pairing initialization failed.\n");
        return 1;
    }

    // Set up the elements
    element_t g1, sk, h, sigma;
    mpz_t g1_mpz, sk_mpz;
    mpz_init(g1_mpz);
    mpz_init(sk_mpz);
    mpz_set_str(g1_mpz, g1_str, 10);  // Assuming decimal input
    mpz_set_str(sk_mpz, sk_str, 10);  // Assuming decimal input

    element_init_G1(g1, pairing);
    element_init_Zr(sk, pairing);
    element_init_G1(h, pairing);
    element_init_G1(sigma, pairing);

    element_set_mpz(g1, g1_mpz);
    element_set_mpz(sk, sk_mpz);

    // Hash the message into an element of G1
    element_from_hash(h, message, strlen(message));

    // Sign the message
    element_pow_zn(sigma, h, sk); // sigma = h^sk

    // Output the signature
    FILE *output_file = fopen("./output", "w+");    
    if (!output_file) {
        fprintf(stderr, "Error opening output file.\n");
        return 1;
    }
    element_fprintf(output_file, "%B\n", sigma);
    fclose(output_file);


    // Clean up
    element_clear(g1);
    element_clear(sk);
    element_clear(h);
    element_clear(sigma);
    pairing_clear(pairing);
    mpz_clear(g1_mpz);
    mpz_clear(sk_mpz);

    return 0;
}
