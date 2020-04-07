#ifndef CRYPTO_DIGEST_H
#define CRYPTO_DIGEST_H
typedef struct {
    unsigned int *hash;
    int hash_len;
    unsigned int input_len;

    void (*block_operate)(const unsigned char *input, unsigned int hash[]);

    void (*block_finalize)(const unsigned char *block, int length);

    // Temporary storage
    unsigned char block[DIGEST_BLOCK_SIZE];
    int block_len;
} digest_ctx;
#endif //CRYPTO_DIGEST_H
