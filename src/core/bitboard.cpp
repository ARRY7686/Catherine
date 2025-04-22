#include "bitboard.hpp"

const char *squareToCoordinates[]={
    "a8","b8","c8","d8","e8","f8","g8","h8",
    "a7","b7","c7","d7","e7","f7","g7","h7",
    "a6","b6","c6","d6","e6","f6","g6","h6",
    "a5","b5","c5","d5","e5","f5","g5","h5",
    "a4","b4","c4","d4","e4","f4","g4","h4",
    "a3","b3","c3","d3","e3","f3","g3","h3",
    "a2","b2","c2","d2","e2","f2","g2","h2",
    "a1","b1","c1","d1","e1","f1","g1","h1"
};

U64 notAFile = 18374403900871474942ULL;
U64 notHFile = 9187201950435737471ULL;
U64 notHGFile = 4557430888798830399ULL;
U64 notABFile = 18229723555195321596ULL;

int count_bits(U64 bitBoard){
    int count = 0;
    while(bitBoard){
        bitBoard &= (bitBoard-1);
        count++;
    }
    return count;
}

int getLeastSignificant1stBitIndex(U64 bitBoard){
    if(bitBoard){
        return count_bits((bitBoard & -bitBoard) - 1);
    }
    else{
        return -1;
    }
}

void printBitBoard(U64 bitBoard){
    std::cout << std::endl;
    for(int rank =0;rank<8;rank++){
        for(int file = 0;file<8;file++){
            int square = rank*8+file;
            if(!file){
                std::cout<<(8-rank)<<"  ";
            }
            std::cout << (getBit(bitBoard,square)? 1 : 0)<<" ";
        }
        std::cout << std::endl;
    }
    std::cout<<std::endl<< "   "<<"a b c d e f g h"<<std::endl<<std::endl;
    std::cout << "     Bitboard: " << bitBoard << "\n\n";
}