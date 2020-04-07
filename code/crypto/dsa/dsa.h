#include "../math/huge.h"

#ifndef CRYPTO_DSA_H
#define CRYPTO_DSA_H
typedef struct {
    huge g;
    huge p;
    huge q;
} dsa_params;

typedef struct {
    huge r;
    huge s;
} dsa_signature;
#endif //CRYPTO_DSA_H
