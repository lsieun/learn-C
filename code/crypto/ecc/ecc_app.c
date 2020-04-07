#include<stdio.h>
#include "ecc_int.h"
#include "ecc_int.c"

int main(void) {
    int val = gcd(105, 252);
    printf("val = %d\n", val);

    int val2 = ext_euclid(5, 13);
    printf("val2 = %d\n", val2);

    domain_parameters T;
    key_pair A;
    key_pair B;
    point Z1, Z2;

    T.p = 23;
    T.a = 1;
    T.b = 1;
    T.G.x = 5;
    T.G.y = 19;

    A.private_key = 4;
    B.private_key = 2;

    A.public_key.x = T.G.x;
    A.public_key.y = T.G.y;
    multiply_point(&A.public_key, A.private_key, T.a, T.p);
    B.public_key.x = T.G.x;
    B.public_key.y = T.G.y;
    multiply_point(&B.public_key, B.private_key, T.a, T.p);

    Z1.x = A.public_key.x;
    Z1.y = A.public_key.y;
    multiply_point(&Z1, B.private_key, T.a, T.p);
    Z2.x = B.public_key.x;
    Z2.y = B.public_key.y;
    multiply_point(&Z2, A.private_key, T.a, T.p);

    return 0;
}