#include "hex.c"

int main(void) {
    unsigned char *input = "0xcafebabe";
//    unsigned char *input = "65536";
    unsigned char **decoded;

    int len = hex_decode(input, decoded);
    show_hex(*decoded, len);
}