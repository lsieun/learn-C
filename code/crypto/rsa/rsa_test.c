#include "rsa.c"
#include "../utils/hex.c"
#include "rsa_sample.h"

int main(int argc, char *argv[]) {
    int exponent_len;
    int modulus_len;
    int data_len;
    unsigned char *exponent;
    unsigned char *modulus;
    unsigned char *data;
    rsa_key public_key;
    rsa_key private_key;
    if (argc < 3) {
        printf(stderr, "Usage: rsa [-e|-d] [<modulus> <exponent>] <data>\n");
        exit(0);
    }
    if (argc == 5) {
        modulus_len = hex_decode(argv[2], &modulus);
        exponent_len = hex_decode(argv[3], &exponent);
        data_len = hex_decode(argv[4], &data);
    } else {
        data_len = hex_decode(argv[2], &data);
        modulus_len = sizeof(TestModulus);
        modulus = TestModulus;
        if (!strcmp("-e", argv[1])) {
            exponent_len = sizeof(TestPublicKey);
            exponent = TestPublicKey;
        } else {
            exponent_len = sizeof(TestPrivateKey);
            exponent = TestPrivateKey;
        }
    }
    public_key.modulus = (huge *) malloc(sizeof(huge));
    public_key.exponent = (huge *) malloc(sizeof(huge));
    private_key.modulus = (huge *) malloc(sizeof(huge));
    private_key.exponent = (huge *) malloc(sizeof(huge));
    if (!strcmp(argv[1], "-e")) {
        unsigned char *encrypted;
        int encrypted_len;
        load_huge(public_key.modulus, modulus, modulus_len);
        load_huge(public_key.exponent, exponent, exponent_len);
        encrypted_len = rsa_encrypt(data, data_len, &encrypted, &public_key);
        show_hex(encrypted, encrypted_len);
        free(encrypted);
    } else if (!strcmp(argv[1], "-d")) {
        int decrypted_len;
        unsigned char *decrypted;
        load_huge(private_key.modulus, modulus, modulus_len);
        load_huge(private_key.exponent, exponent, exponent_len);
        decrypted_len = rsa_decrypt(data, data_len, &decrypted, &private_key);
        show_hex(decrypted, decrypted_len);
        free(decrypted);
    } else {
        printf("unrecognized option flag ‘%s’\n", argv[1]);
    }
    free(data);
    if (argc == 5) {
        free(modulus);
        free(exponent);
    }
}

