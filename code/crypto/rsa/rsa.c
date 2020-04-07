#include<stdio.h>
#include "../math/huge.c"
#include "rsa.h"

/**
* Compute c = m^e mod n.
*/
void rsa_compute(huge *m, huge *e, huge *n, huge *c) {
    huge counter;
    huge one;

    copy_huge(c, m);
    set_huge(&counter, 1);
    set_huge(&one, 1);

    while (compare(&counter, e) < 0) {
        multiply(c, m);
        add(&counter, &one);
    }

    divide(c, n, NULL);

    free_huge(&counter);
    free_huge(&one);
    // Remainder (result) is now in c
}


/**
* The input should be broken up into n-bit blocks, where n is the
* length in bits of the modulus. The output will always be n bits
* or less. Per RFC 2313, there must be at least 8 bytes of padding
* to prevent an attacker from trying all possible padding bytes.
*
* output will be allocated by this routine, must be freed by the
* caller.
*
* returns the length of the data encrypted in output
*/
int rsa_encrypt(unsigned char *input,
                unsigned int len,
                unsigned char **output,
                rsa_key *public_key) {
    // 计算结束之后，最终的返回结果
    int encrypted_size = 0;
    *output = NULL;

    // 计算过程当中，所使用的变量
    int modulus_length = public_key->modulus->size;
    unsigned char *padded_block = (unsigned char *) malloc(modulus_length);

    // 主要计算过程
    while (len) {
        encrypted_size += modulus_length;
        int block_size = (len < modulus_length - 11) ? len : (modulus_length - 11);

        // 第一步，填充数据
        memset(padded_block, 0, modulus_length);
        memcpy(padded_block + (modulus_length - block_size), input, block_size);
        padded_block[1] = 0x02; // set block type
        for (int i = 2; i < (modulus_length - block_size - 1); i++) {
            padded_block[i] = i; // TODO make these random
        }
        show_chars(padded_block, modulus_length, "padded_block");

        // 第二步，加密数据
        huge c, m;
        load_huge(&m, padded_block, modulus_length);
        show_huge(&m, "message");
        mod_pow(&m, public_key->exponent, public_key->modulus, &c);

        // 第三步，存储数据
        *output = (unsigned char *) realloc(*output, encrypted_size);
        unload_huge(&c, *output + (encrypted_size - modulus_length), modulus_length);

        // 第四步，更新变量
        len -= block_size;
        input += block_size;
        free_huge(&m);
        free_huge(&c);
    }

    free(padded_block);

    return encrypted_size;
}

/**
* Convert the input into key-length blocks and decrypt, unpadding
* each time.
* Return -1 if the input is not an even multiple of the key modulus
* length or if the padding type is not “2”, otherwise return the
* length of the decrypted data.
*/
int rsa_decrypt(unsigned char *input,
                unsigned int len,
                unsigned char **output,
                rsa_key *private_key) {
    int i, out_len = 0;
    huge c, m;
    int modulus_length = private_key->modulus->size;

    unsigned char *padded_block = (unsigned char *) malloc(modulus_length);

    *output = NULL;
    while (len) {
        if (len < modulus_length) {
            printf("Error - input must be an even multiple of key modulus %d (got %d)\n",
                   private_key->modulus->size,
                   len);
            free(padded_block);
            return -1;
        }

        load_huge(&c, input, modulus_length);
        mod_pow(&c, private_key->exponent, private_key->modulus, &m);

        unload_huge(&m, padded_block, modulus_length);

        if (padded_block[1] > 0x02) {
            printf("Decryption error or unrecognized block type %d.\n",
                   padded_block[1]);
            free_huge(&c);
            free_huge(&m);
            free(padded_block);
            return -1;
        }

        // Find next 0 byte after the padding type byte; this signifies
        // start-of-data
        i = 2;
        while (padded_block[i++]);

        out_len += modulus_length - i;
        *output = realloc(*output, out_len);

        memcpy(*output + (out_len - (modulus_length - i)),
               padded_block + i,
               modulus_length - i);

        len -= modulus_length;
        input += modulus_length;

        free_huge(&c);
        free_huge(&m);
    }

    free(padded_block);

    return out_len;
}
