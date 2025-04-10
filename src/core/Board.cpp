//System Headers
#include <iostream>

//defining bitboard types
#define U64 unsigned long long

//board squares using enums for better accessibility and readability
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
//sides to play(black and white to differentiate between pieces)
enum{
    WHITE,BLACK
};

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
// defining set/get/pop macros (bitboard operations using bit manipulation)
#define getBit(bitBoard,square) (bitBoard & (1ULL << square))
#define setBit(bitBoard,square) (bitBoard |= (1ULL << square))
#define popBit(bitBoard,square) (getBit(bitBoard,square)? bitBoard ^= (1ULL << square) : 0)


//counting bits in a bitBoard
static inline int count_bits(U64 bitBoard){
    int count = 0;
    //resetting least significant bits
    while(bitBoard){
        bitBoard &= (bitBoard-1);
        count++;
    }
    return count;
}

// get least significant 1st bit index
static inline int getLeastSignificant1stBitIndex(U64 bitBoard){
    if(bitBoard){
        //coubnt the bits before the least significant bit
        return count_bits((bitBoard & -bitBoard) - 1);
    }
    else{
        //not valid index
        return -1;
    }
}
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

//not A  file so that we should not go out of the board while generating mask attacks
U64 notAFile = 18374403900871474942ULL;
//not H  file so that we should not go out of the board while generating mask attacks
U64 notHFile = 9187201950435737471ULL;
// not HG  file so that we should not go out of the board while generating mask attacks
U64 notHGFile = 4557430888798830399ULL;
//not AB  file so that we should not go out of the board while generating mask attacks
U64 notABFile = 18229723555195321596ULL;

// relevancy occupancy bit count for every square on the board
const int bishopRelevantBits[64] = {
    6,5,5,5,5,5,5,6,
    5,5,5,5,5,5,5,5,
    5,5,7,7,7,7,5,5,
    5,5,7,9,9,7,5,5,
    5,5,7,9,9,7,5,5,
    5,5,7,7,7,7,5,5,
    5,5,5,5,5,5,5,5,
    6,5,5,5,5,5,5,6

};

const int rookRelevantBits[64] = {
    12,11,11,11,11,11,11,12,
    11,10,10,10,10,10,10,11,
    11,10,10,10,10,10,10,11,
    11,10,10,10,10,10,10,11,
    11,10,10,10,10,10,10,11,
    11,10,10,10,10,10,10,11,
    11,10,10,10,10,10,10,11,
    12,11,11,11,11,11,11,12
};



//Attacks
    //Pawn attacks
    U64 pawnAttacks[2][64];
    //Knight attacks
    U64 knightAttacks[64]; 
    //king attacks
    U64 kingAttacks[64];
    //bishop attacks
    U64 bishopAttacks[64];
    //rook attacks
    U64 rookAttacks[64];
    //queen attacks
    U64 queenAttacks[64];
    //masking the attacks(pedicting all the possible attacks from that position)
    //generating pawn attacks by masking the pawn position(iterating over the board and setting the bit to 1 where the pawn can attack)
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
    //generating knight attacks by masking the knight position (iterating over the board and setting the bit to 1 where the knight can attack)
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
    //generating king attacks by masking the king position (iterating over the board and setting the bit to 1 where the king can attack)
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
    //generating bishop attacks by masking the bishop position (iterating over the board and setting the bit to 1 where the bishop can attack)
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
    //generating rook attacks by masking the rook position (iterating over the board and setting the bit to 1 where the rook can attack)
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

    //generate bishop on fly(limiting the bishop attacks to the blockers(other pieces if present on the board))
    U64 BishopAttacksOnTheFly(int square, U64 block) {
        U64 attacks = 0ULL;
        int rank, file;
        int targetRank = square / 8;
        int targetFile = square % 8;
    
        for (rank = targetRank + 1, file = targetFile + 1; rank <= 7 && file <= 7; rank++, file++) {
            attacks |= (1ULL << (rank * 8 + file));
            if (block & (1ULL << (rank * 8 + file))) break;  // Stop at blocker
        }
    
        for (rank = targetRank - 1, file = targetFile - 1; rank >= 0 && file >= 0; rank--, file--) {
            attacks |= (1ULL << (rank * 8 + file));
            if (block & (1ULL << (rank * 8 + file))) break;  // Stop at blocker
        }
    
        for (rank = targetRank + 1, file = targetFile - 1; rank <= 7 && file >= 0; rank++, file--) {
            attacks |= (1ULL << (rank * 8 + file));
            if (block & (1ULL << (rank * 8 + file))) break;  // Stop at blocker
        }
    
        for (rank = targetRank - 1, file = targetFile + 1; rank >= 0 && file <= 7; rank--, file++) {
            attacks |= (1ULL << (rank * 8 + file));
            if (block & (1ULL << (rank * 8 + file))) break;  // Stop at blocker
        }
    
        return attacks;
    }
    //generate rook on fly(limiting the rook attacks to the blockers(other pieces if present on the board))
    U64 RookAttacksOnTheFly(int square, U64 block) {
        U64 attacks = 0ULL;
        int ranks,files;
        int tragetRank = square/8;
        int tragetFile = square%8;
        for(ranks = tragetRank+1;ranks<=7;ranks++){
            attacks |= (1ULL << (ranks*8+tragetFile));
            if (block & (1ULL << (ranks*8+tragetFile))) break;// Stop at blocker

        }
        for(ranks = tragetRank-1;ranks>=0;ranks--){
            attacks |= (1ULL << (ranks*8+tragetFile));
            if (block & (1ULL << (ranks*8+tragetFile))) break;// Stop at blocker
        }
        for(files = tragetFile+1;files<=7;files++){
            attacks |= (1ULL << (tragetRank*8+files));
            if (block & (1ULL << (tragetRank*8+files))) break;// Stop at blocker
        }
        for(files = tragetFile-1;files>=0;files--){
            attacks |= (1ULL << (tragetRank*8+files));
            if (block & (1ULL << (tragetRank*8+files))) break;// Stop at blocker
        }
        return attacks;
    }
    U64 queenAttacksOnTheFly(int square, U64 block) {
        return RookAttacksOnTheFly(square, block) | BishopAttacksOnTheFly(square, block);
    }

//setting occupancies by iterating over the bits in the mask,popping the bit from the attack mask and setting the occupancy to 1 if the bit is set in the index
U64 setOccupancy(int index,int bitsInMask,U64 attackMask){
    U64 occupancy = 0ULL;
    for(int count = 0;count<bitsInMask;count++){
        int square = getLeastSignificant1stBitIndex(attackMask);
        popBit(attackMask,square);
        if(index & (1<<count)){
            setBit(occupancy,square);
        }
    }

    return occupancy;
}

//using XORWOW to generate random numbers(declaring 5 states  and using bit manipulation to generate random numbers also updating the state values)
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

//Main driver function
int main(){
    //testing the bitboard
    // printBitBoard(maskQueenAttacks(d5));
    // U64 block = 0ULL;
    // setBit(block, d4);
    // setBit(block, e5);
    // setBit(block, g2);
    // printBitBoard(block);
    // std::cout << squareToCoordinates[getLeastSignificant1stBitIndex(block)] << std::endl;
    // U64 test = 0ULL;
    // setBit(test, 28);
    // printBitBoard(test);
    // U64 occupancy = setOccupancy(4095,count_bits(maskQueenAttacks(d5)),maskQueenAttacks(d5));
    // printBitBoard(occupancy);

    for(int i = 0; i < 10; i++) {
        std::cout << xorwow() << std::endl;
    }
    
    return 0;
}
