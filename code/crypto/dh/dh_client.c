#include<stdio.h>
#include "../math/huge.h"
#include "dh.c"

void send_to_server(huge *h) {
    //
}

void receive_from_server(huge *h) {
    //
}

int main(void) {
    huge Ys, Yc, Z;
    huge *p, *g, *b;

    dh_agree(p, g, b, &Yc);
    send_to_server(&Yc);
    receive_from_server(&Ys);
    dh_finalize(p, &Ys, b, &Z);
    // ... use “Z” as shared key
}
