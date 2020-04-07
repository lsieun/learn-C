#include "../math/huge.h"
#include "../math/huge.c"

static void dh_agree(huge *p, huge *g, huge *e, huge *Y) {
    mod_pow(g, &e, p, Y);
}

static void dh_finalize(huge *p, huge *Y, huge *e, huge *Z) {
    mod_pow(Y, &e, p, &Z);
}

