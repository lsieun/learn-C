#include "rsa.c"
#include "rsa_sample.h"
#include "../utils/hex.c"

int main(void) {
    unsigned char *modulus = TestModulus;
    int modulus_len = sizeof(TestModulus);

    unsigned char *exponent = TestPrivateKey;
    int exponent_len = sizeof(TestPrivateKey);

    rsa_key private_key;
    private_key.modulus = (huge *) malloc(sizeof(huge));
    private_key.exponent = (huge *) malloc(sizeof(huge));
    load_huge(private_key.modulus, modulus, modulus_len);
    load_huge(private_key.exponent, exponent, exponent_len);


    unsigned char *input = "0x40f73315d3f74703904e51e1c72686801de06a55417110e56280f1f8471a3802406d2110011e1f387f7b4c43258b0a1eedc558a3aac5aa2d20cf5e0d65d80db3";
    unsigned char *data;
    int data_len = hex_decode(input, &data);


    unsigned char *decrypted;
    int decrypted_len = rsa_decrypt(data, data_len, &decrypted, &private_key);

    show_hex(decrypted, decrypted_len);

    free(decrypted);
    free(data);
    free(private_key.modulus);
    free(private_key.exponent);
}



