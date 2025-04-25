#include "bitboard.hpp"
#include "attacks.hpp"
#include "random.hpp"
#include "Magics.hpp"
#include <iostream>
#include <iomanip>

int main(){ 


for (int square = 0; square < 64; square++) {
    std::cout << "0x" 
              << std::hex << std::setw(16) << std::setfill('0') 
              << rookMagicNumbers[square] << "ULL," << std::endl;
}

std::cout << std::endl << std::endl;

for (int square = 0; square < 64; square++) {
    std::cout << "0x" 
              << std::hex << std::setw(16) << std::setfill('0') 
              << bishopMagicNumbers[square] << "ULL," << std::endl;
}
}