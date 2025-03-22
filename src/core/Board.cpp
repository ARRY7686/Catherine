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
//sides to play
enum{
    WHITE,BLACK
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

//not A file
U64 notAFile = 18374403900871474942ULL;
//not H file
U64 notHFile = 9187201950435737471ULL;
// not HG file
U64 notHGFile = 4557430888798830399ULL;
//not AB file
U64 notABFile = 18229723555195321596ULL;
//Attacks
    //Pawn attacks
    U64 pawnAttacks[2][64];
    //Knight attacks
    U64 knightAttacks[64]; 
    //king attacks
    U64 kingAttacks[64];
    //generating pawn attacks by masking the pawn position
    U64 maskPawnAttacks(int square,int side){
        U64 bitBoard = 0ULL;
        U64 Attacks = 0ULL;
        setBit(bitBoard,square);
        if(side == WHITE){
            if((bitBoard>>7) & notAFile){
                Attacks |= (bitBoard >> 7);
            }
            if((bitBoard >> 9) & notHFile){
                Attacks |= (bitBoard >> 9);
            }
        }else{
            if((bitBoard << 7) & notHFile){
                Attacks |= (bitBoard << 7);
            }
            if((bitBoard << 9) & notAFile){
                Attacks |= (bitBoard << 9);
            }
        }
        return Attacks;
    }
    //generating knight attacks by masking the knight position
    U64 maskKnightAttacks(int square){
        U64 attacks = 0ULL;
        U64 bitBoard = 0ULL;
        setBit(bitBoard,square);
        if((bitBoard >> 17) & notHFile){
            attacks |= (bitBoard >> 17);
        }
        if((bitBoard >> 15) & notAFile){
            attacks |= (bitBoard >> 15);
        }
        if((bitBoard >> 10) & notHGFile){
            attacks |= (bitBoard >> 10);
        }
        if((bitBoard >> 6) & notABFile){
            attacks |= (bitBoard >> 6);
        }
        if((bitBoard << 17) & notAFile){
            attacks |= (bitBoard << 17);
        }
        if((bitBoard << 15) & notHFile){
            attacks |= (bitBoard << 15);
        }
        if((bitBoard << 10) & notABFile){
            attacks |= (bitBoard << 10);
        }
        if((bitBoard << 6) & notHGFile){
            attacks |= (bitBoard << 6);
        }
        return attacks;

    }
    //generating king attacks by masking the king position
    U64 maskKingAttacks(int square){
        U64 attacks = 0ULL;
        U64 bitBoard = 0ULL;
        setBit(bitBoard,square);
        if((bitBoard >> 1) & notHFile){
            attacks |= (bitBoard >> 1);
        }
        if((bitBoard >> 9) & notHFile){
            attacks |= (bitBoard >> 9);
        }
        if((bitBoard >> 8)){
            attacks |= (bitBoard >> 8);
        }
        if((bitBoard >> 7) & notAFile){
            attacks |= (bitBoard >> 7);
        }
        if((bitBoard << 1) & notAFile){
            attacks |= (bitBoard << 1);
        }
        if((bitBoard << 9) & notAFile){
            attacks |= (bitBoard << 9);
        }
        if((bitBoard << 8)){
            attacks |= (bitBoard << 8);
        }
        if((bitBoard << 7) & notHFile){
            attacks |= (bitBoard << 7);
        }
        return attacks;
    }
    U64 maskBishopAttacks(int square){
        U64 attacks = 0ULL;

        int ranks,files;
        int tragetRank = square/8;
        int tragetFile = square%8;
        for(ranks = tragetRank+1,files = tragetFile+1;ranks<=7 && files<=7;ranks++,files++){
            attacks |= (1ULL << (ranks*8+files));
        }
        for(ranks = tragetRank-1,files = tragetFile-1;ranks>=0 && files>=0;ranks--,files--){
            attacks |= (1ULL << (ranks*8+files));
        }
        for(ranks = tragetRank+1,files = tragetFile-1;ranks<=7 && files>=0;ranks++,files--){
            attacks |= (1ULL << (ranks*8+files));
        }
        for(ranks = tragetRank-1,files = tragetFile+1;ranks>=0 && files<=7;ranks--,files++){
            attacks |= (1ULL << (ranks*8+files));
        }
        return attacks;
    }
    U64 maskRookAttacks(int square){
        U64 attacks = 0ULL;
        int ranks,files;
        int tragetRank = square/8;
        int tragetFile = square%8;
        for(ranks = tragetRank+1;ranks<=7;ranks++){
            attacks |= (1ULL << (ranks*8+tragetFile));
        }
        for(ranks = tragetRank-1;ranks>=0;ranks--){
            attacks |= (1ULL << (ranks*8+tragetFile));
        }
        for(files = tragetFile+1;files<=7;files++){
            attacks |= (1ULL << (tragetRank*8+files));
        }
        for(files = tragetFile-1;files>=0;files--){
            attacks |= (1ULL << (tragetRank*8+files));
        }
        return attacks;
    }
    //using the upper two functions to generate queen attacks
    U64 maskQueenAttacks(int square){
        return maskBishopAttacks(square) | maskRookAttacks(square);
    }
//Main driver function
int main(){
    printBitBoard(maskQueenAttacks(d5));
    return 0;
}
