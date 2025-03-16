//System Headers
#include <iostream>

//defining bitboard types
#define U64 unsigned long long

// defining set/get/pop macros
#define getBit(bitBoard,square) (bitBoard & (1ULL << square))


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
    U64 bitboard = 1ULL;
    printBitBoard(bitboard);
    return 0;
}
