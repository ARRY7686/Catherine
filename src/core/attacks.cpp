#include "attacks.hpp"

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

U64 pawnAttacks[2][64];
U64 knightAttacks[64]; 
U64 kingAttacks[64];
U64 bishopAttacks[64];
U64 rookAttacks[64];
U64 queenAttacks[64];

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

U64 maskQueenAttacks(int square){
    return maskBishopAttacks(square) | maskRookAttacks(square);
}

U64 BishopAttacksOnTheFly(int square, U64 block) {
    U64 attacks = 0ULL;
    int rank, file;
    int targetRank = square / 8;
    int targetFile = square % 8;

    for (rank = targetRank + 1, file = targetFile + 1; rank <= 7 && file <= 7; rank++, file++) {
        attacks |= (1ULL << (rank * 8 + file));
        if (block & (1ULL << (rank * 8 + file))) break;
    }

    for (rank = targetRank - 1, file = targetFile - 1; rank >= 0 && file >= 0; rank--, file--) {
        attacks |= (1ULL << (rank * 8 + file));
        if (block & (1ULL << (rank * 8 + file))) break;
    }

    for (rank = targetRank + 1, file = targetFile - 1; rank <= 7 && file >= 0; rank++, file--) {
        attacks |= (1ULL << (rank * 8 + file));
        if (block & (1ULL << (rank * 8 + file))) break;
    }

    for (rank = targetRank - 1, file = targetFile + 1; rank >= 0 && file <= 7; rank--, file++) {
        attacks |= (1ULL << (rank * 8 + file));
        if (block & (1ULL << (rank * 8 + file))) break;
    }
    return attacks;
}

U64 RookAttacksOnTheFly(int square, U64 block) {
    U64 attacks = 0ULL;
    int ranks,files;
    int tragetRank = square/8;
    int tragetFile = square%8;
    for(ranks = tragetRank+1;ranks<=7;ranks++){
        attacks |= (1ULL << (ranks*8+tragetFile));
        if (block & (1ULL << (ranks*8+tragetFile))) break;
    }
    for(ranks = tragetRank-1;ranks>=0;ranks--){
        attacks |= (1ULL << (ranks*8+tragetFile));
        if (block & (1ULL << (ranks*8+tragetFile))) break;
    }
    for(files = tragetFile+1;files<=7;files++){
        attacks |= (1ULL << (tragetRank*8+files));
        if (block & (1ULL << (tragetRank*8+files))) break;
    }
    for(files = tragetFile-1;files>=0;files--){
        attacks |= (1ULL << (tragetRank*8+files));
        if (block & (1ULL << (tragetRank*8+files))) break;
    }
    return attacks;
}

U64 queenAttacksOnTheFly(int square, U64 block) {
    return RookAttacksOnTheFly(square, block) | BishopAttacksOnTheFly(square, block);
}

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

void init_leapers_attacks()
{
    for (int square = 0; square < 64; square++)
    {
        pawnAttacks[WHITE][square] = maskPawnAttacks(WHITE, square);
        pawnAttacks[BLACK][square] = maskPawnAttacks(BLACK, square);
        knightAttacks[square] = maskKnightAttacks(square);
        kingAttacks[square] = maskKingAttacks(square);
    }
}

U64 generateMagicNumber(){
    extern U64 randomU64();
    return randomU64()&randomU64()&randomU64();
}