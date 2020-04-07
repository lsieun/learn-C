#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

static const char HEX_CHARS[16] = {
        '0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
};

unsigned char get_val(char ch) {
    return (ch <= '9') ? (ch - '0') : ((tolower(ch)) - 'a' + 10);
}

/**
* Check to see if the input starts with “0x”; if it does, return the decoded
* bytes of the following data (presumed to be hex coded). If not, just return
* the contents. This routine allocates memory, so has to be free'd.
*/
int hex_decode(const unsigned char *input, unsigned char **decoded) {
    int len = 0;

    if (strncmp("0x", input, 2)) {
        len = strlen(input) + 1;
        *decoded = malloc(len);
        strcpy(*decoded, input);
        len--;
    } else {
        len = (strlen(input) >> 1) - 1;
        *decoded = malloc(len);
        for (int i = 2; i < strlen(input); i += 2) {
            unsigned char hi = get_val(input[i]);
            unsigned char lo = get_val(input[i + 1]);
            (*decoded)[((i / 2) - 1)] = (hi << 4) | (lo);
        }
    }
    return len;
}


void show_hex(const unsigned char *array, int length) {
    char str[length * 2 + 1];
    for (int i = 0; i < length; ++i) {
        unsigned char ch = array[i];
        int quotient = ch / 16;
        int remainder = ch % 16;
        str[2 * i] = HEX_CHARS[quotient];
        str[2 * i + 1] = HEX_CHARS[remainder];
    }
    str[length * 2] = '\0';
    printf("%s\n", str);
}
