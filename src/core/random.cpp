#include "random.hpp"

unsigned int xstate = 1789330918;
unsigned int ystate = 3760899688;
unsigned int zstate = 3671987436;
unsigned int wstate = 703422639;
unsigned int vstate = 1750193339;
unsigned int dstate = 1336784410;

unsigned int xorwow() {
    unsigned int t = xstate ^ (xstate >> 2);
    xstate = ystate;
    ystate = zstate;
    zstate = wstate;
    wstate = vstate;
    vstate = vstate ^ (vstate << 4) ^ (t ^ (t << 1));
    dstate += 362437;
    return ((vstate + dstate)&0xFFFFFFFF);
}

unsigned int randomU32() {
    return xorwow();
}

U64 randomU64() {
    U64 n1,n2,n3,n4;
    n1 = (U64)(xorwow()&0xFFFFFFFF);
    n2 = (U64)(xorwow()&0xFFFFFFFF);
    n3 = (U64)(xorwow()&0xFFFFFFFF);
    n4 = (U64)(xorwow()&0xFFFFFFFF);
    return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
}