#include "bitboard.hpp"
#include "attacks.hpp"
#include "random.hpp"
#include "Magics.hpp"
#include <iostream>
#include <iomanip>

int main(){ 
    initAll();
    U64 occupancy = 0ULL;
    setBit(occupancy,c5);
    setBit(occupancy,f2);
    printBitBoard(occupancy);
    printBitBoard(getBishopAttacks(d4,occupancy));

}