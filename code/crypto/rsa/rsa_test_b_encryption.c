#include "rsa.c"
#include "rsa_sample.h"
#include "../utils/hex.c"

int main(void) {
    unsigned char *modulus = TestModulus;
    int modulus_len = sizeof(TestModulus);

    unsigned char *exponent = TestPublicKey;
    int exponent_len = sizeof(TestPublicKey);

    rsa_key public_key;
    public_key.modulus = (huge *) malloc(sizeof(huge));
    public_key.exponent = (huge *) malloc(sizeof(huge));
    load_huge(public_key.modulus, modulus, modulus_len);
    load_huge(public_key.exponent, exponent, exponent_len);

    show_huge(public_key.modulus, "public_key.modulus");
    show_huge(public_key.exponent, "public_key.exponent");

    unsigned char *input = "abc";
    unsigned char *data;
    int data_len = hex_decode(input, &data);

    show_chars(data, data_len, "input");

    unsigned char *encrypted;
    int encrypted_len = rsa_encrypt(data, data_len, &encrypted, &public_key);

    show_hex(encrypted, encrypted_len);

    free(encrypted);
    free(data);
    free(public_key.modulus);
    free(public_key.exponent);
}

