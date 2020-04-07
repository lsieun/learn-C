/* binbit.c -- using bit operations to display binary */
#include <stdio.h>
#include <limits.h> // for CHAR_BIT, # of bits per char

const static int INT_BIT_SIZE = sizeof(int) * CHAR_BIT;

void int_to_bits(int, char *);
void show_binary_str(const char *);

int main(void) {
    char bin_str[INT_BIT_SIZE + 1];
    int number;
    puts("Enter integers and see them in binary.");
    puts("Non-numeric input terminates program.");
    while (scanf("%d", &number) == 1) {
        int_to_bits(number, bin_str);
        printf("%d is:\n", number);
        show_binary_str(bin_str);
        putchar('\n');
    }
    puts("Bye!");
    return 0;
}

void int_to_bits(int n, char *ps) {
    for (int i = INT_BIT_SIZE - 1; i >= 0; i--) {
        ps[i] = '0' + (n & 0x01); // assume ASCII or similar
        n >>= 1;
    }

    ps[INT_BIT_SIZE] = '\0';
}

/* show binary string in blocks of 4 */
void show_binary_str(const char *str) {
    int i = 0;
    while (str[i]) /* not the null character */
    {
        putchar(str[i]);
        if (++i % 4 == 0 && str[i]) {
            putchar(' ');
        }
    }
}

