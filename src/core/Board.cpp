//System Headers
#include <iostream>

//defining bitboard types
#define U64 unsigned long long

//board squares
enum{
    a8,b8,c8,d8,e8,f8,g8,h8,
    a7,b7,c7,d7,e7,f7,g7,h7,
    a6,b6,c6,d6,e6,f6,g6,h6,
    a5,b5,c5,d5,e5,f5,g5,h5,
    a4,b4,c4,d4,e4,f4,g4,h4,
    a3,b3,c3,d3,e3,f3,g3,h3,
    a2,b2,c2,d2,e2,f2,g2,h2,
    a1,b1,c1,d1,e1,f1,g1,h1
};

// defining set/get/pop macros
#define getBit(bitBoard,square) (bitBoard & (1ULL << square))
#define setBit(bitBoard,square) (bitBoard |= (1ULL << square))
#define popBit(bitBoard,square) (getBit(bitBoard,square)? bitBoard ^= (1ULL << square) : 0)

//printing bitboard function(looping over files and ranks)

void printBitBoard(U64 bitBoard){
    std::cout << std::endl;

    for(int rank =0;rank<8;rank++){
        for(int file = 0;file<8;file++){
            int square = rank*8+file;
            //printing ranks
            if(!file){
                std::cout<<(8-rank)<<"  ";
            }
            //checking square if it is occupied or not
            std::cout << (getBit(bitBoard,square)? 1 : 0)<<" ";
        }
        std::cout << std::endl;
    }
    //printing files
    std::cout<<std::endl<< "   "<<"a b c d e f g h"<<std::endl<<std::endl;

}


//Main driver function
int main(){
    //defining bitboard
    U64 bitBoard = 0ULL;
    //using the macros manipulating it and printing it
    setBit(bitBoard,e2);
    setBit(bitBoard,e4);
    popBit(bitBoard,e2);
    printBitBoard(bitBoard);
    return 0;
}
