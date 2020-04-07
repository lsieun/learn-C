#include "rsa.c"

int main(void) {
    huge e, d, n, m, c;
    set_huge(&e, 79);
    set_huge(&d, 1019);
    set_huge(&n, 3337);
    set_huge(&m, 688);

    display_huge(&e);
    display_huge(&d);
    display_huge(&n);
    display_huge(&m);

    set_huge(&c, 0);
//    rsa_compute(&m, &e, &n, &c);
    mod_pow(&m, &e, &n, &c);
    printf("Encrypted to: %d\n", get_huge(&c));

    set_huge(&m, 0);
//    rsa_compute(&c, &d, &n, &m);
    mod_pow(&c, &d, &n, &m);
    printf("Decrypted to: %d\n", get_huge(&m));
}

