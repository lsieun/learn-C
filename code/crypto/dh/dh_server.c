#include<stdio.h>
#include "../math/huge.h"
#include "dh.c"

void send_to_client(huge *h) {
    //
}

void receive_from_client(huge *h) {
    //
}

int main(void) {
    huge Ys, Yc, Z;
    huge *p, *g, *a;

    dh_agree(p, g, a, &Ys);
    send_to_client(&Ys);
    receive_from_client(&Yc);
    dh_finalize(p, &Yc, a, &Z);
    // ... use “Z” as shared key
}
