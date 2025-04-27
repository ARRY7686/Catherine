#include "attacks.hpp"
#include <cstring>


const int bishopRelevantBits[64] = {
    6, 5, 5, 5, 5, 5, 5, 6, 
    5, 5, 5, 5, 5, 5, 5, 5, 
    5, 5, 7, 7, 7, 7, 5, 5, 
    5, 5, 7, 9, 9, 7, 5, 5, 
    5, 5, 7, 9, 9, 7, 5, 5, 
    5, 5, 7, 7, 7, 7, 5, 5, 
    5, 5, 5, 5, 5, 5, 5, 5, 
    6, 5, 5, 5, 5, 5, 5, 6
};

const int rookRelevantBits[64] = {
    12, 11, 11, 11, 11, 11, 11, 12, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    12, 11, 11, 11, 11, 11, 11, 12
};

 U64 pawnAttacks[2][64];
 U64 knightAttacks[64]; 
 U64 kingAttacks[64];
 U64 bishopAttacks[64][512];
 U64 rookAttacks[64][4096];
 U64 queenAttacks[64];
 U64 bishopMasks[64];
 U64 rookMasks[64];



// Generate pawn attacks
U64 maskPawnAttacks(int square, int side) {
    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;
    setBit(bitboard, square);

    if (side == 0) { // White
        if ((bitboard >> 7) & notAFile) attacks |= (bitboard >> 7);
        if ((bitboard >> 9) & notHFile) attacks |= (bitboard >> 9);
    } else { // Black
        if ((bitboard << 7) & notHFile) attacks |= (bitboard << 7);
        if ((bitboard << 9) & notAFile) attacks |= (bitboard << 9);
    }

    return attacks;
}

// Generate knight attacks
U64 maskKnightAttacks(int square) {
    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;
    setBit(bitboard, square);

    if ((bitboard >> 17) & notHFile) attacks |= (bitboard >> 17);
    if ((bitboard >> 15) & notAFile) attacks |= (bitboard >> 15);
    if ((bitboard >> 10) & notHGFile) attacks |= (bitboard >> 10);
    if ((bitboard >> 6) & notABFile) attacks |= (bitboard >> 6);
    if ((bitboard << 17) & notAFile) attacks |= (bitboard << 17);
    if ((bitboard << 15) & notHFile) attacks |= (bitboard << 15);
    if ((bitboard << 10) & notABFile) attacks |= (bitboard << 10);
    if ((bitboard << 6) & notHGFile) attacks |= (bitboard << 6);

    return attacks;
}

// Generate king attacks
U64 maskKingAttacks(int square) {
    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;
    setBit(bitboard, square);

    if (bitboard >> 8) attacks |= (bitboard >> 8);
    if ((bitboard >> 9) & notHFile) attacks |= (bitboard >> 9);
    if ((bitboard >> 7) & notAFile) attacks |= (bitboard >> 7);
    if ((bitboard >> 1) & notHFile) attacks |= (bitboard >> 1);
    if (bitboard << 8) attacks |= (bitboard << 8);
    if ((bitboard << 9) & notAFile) attacks |= (bitboard << 9);
    if ((bitboard << 7) & notHFile) attacks |= (bitboard << 7);
    if ((bitboard << 1) & notAFile) attacks |= (bitboard << 1);

    return attacks;
}

// Mask bishop attacks (relevant occupancy bits)
U64 maskBishopAttacks(int square) {
    U64 attacks = 0ULL;

    int r, f;
    int tr = square / 8, tf = square % 8;

    for (r = tr + 1, f = tf + 1; r <= 6 && f <= 6; r++, f++) attacks |= (1ULL << (r * 8 + f));
    for (r = tr - 1, f = tf + 1; r >= 1 && f <= 6; r--, f++) attacks |= (1ULL << (r * 8 + f));
    for (r = tr + 1, f = tf - 1; r <= 6 && f >= 1; r++, f--) attacks |= (1ULL << (r * 8 + f));
    for (r = tr - 1, f = tf - 1; r >= 1 && f >= 1; r--, f--) attacks |= (1ULL << (r * 8 + f));

    return attacks;
}

// Mask rook attacks (relevant occupancy bits)
U64 maskRookAttacks(int square) {
    U64 attacks = 0ULL;

    int r, f;
    int tr = square / 8, tf = square % 8;

    for (r = tr + 1; r <= 6; r++) attacks |= (1ULL << (r * 8 + tf));
    for (r = tr - 1; r >= 1; r--) attacks |= (1ULL << (r * 8 + tf));
    for (f = tf + 1; f <= 6; f++) attacks |= (1ULL << (tr * 8 + f));
    for (f = tf - 1; f >= 1; f--) attacks |= (1ULL << (tr * 8 + f));

    return attacks;
}

// Mask queen attacks
U64 maskQueenAttacks(int square) {
    return maskBishopAttacks(square) | maskRookAttacks(square);
}

// Generate bishop attacks on the fly
U64 BishopAttacksOnTheFly(int square, U64 block) {
    U64 attacks = 0ULL;

    int r, f;
    int tr = square / 8, tf = square % 8;

    for (r = tr + 1, f = tf + 1; r <= 7 && f <= 7; r++, f++) {
        attacks |= (1ULL << (r * 8 + f));
        if (block & (1ULL << (r * 8 + f))) break;
    }
    for (r = tr - 1, f = tf + 1; r >= 0 && f <= 7; r--, f++) {
        attacks |= (1ULL << (r * 8 + f));
        if (block & (1ULL << (r * 8 + f))) break;
    }
    for (r = tr + 1, f = tf - 1; r <= 7 && f >= 0; r++, f--) {
        attacks |= (1ULL << (r * 8 + f));
        if (block & (1ULL << (r * 8 + f))) break;
    }
    for (r = tr - 1, f = tf - 1; r >= 0 && f >= 0; r--, f--) {
        attacks |= (1ULL << (r * 8 + f));
        if (block & (1ULL << (r * 8 + f))) break;
    }

    return attacks;
}

// Generate rook attacks on the fly
U64 RookAttacksOnTheFly(int square, U64 block) {
    U64 attacks = 0ULL;

    int r, f;
    int tr = square / 8, tf = square % 8;

    for (r = tr + 1; r <= 7; r++) {
        attacks |= (1ULL << (r * 8 + tf));
        if (block & (1ULL << (r * 8 + tf))) break;
    }
    for (r = tr - 1; r >= 0; r--) {
        attacks |= (1ULL << (r * 8 + tf));
        if (block & (1ULL << (r * 8 + tf))) break;
    }
    for (f = tf + 1; f <= 7; f++) {
        attacks |= (1ULL << (tr * 8 + f));
        if (block & (1ULL << (tr * 8 + f))) break;
    }
    for (f = tf - 1; f >= 0; f--) {
        attacks |= (1ULL << (tr * 8 + f));
        if (block & (1ULL << (tr * 8 + f))) break;
    }

    return attacks;
}

// Generate queen attacks on the fly
U64 queenAttacksOnTheFly(int square, U64 block) {
    return BishopAttacksOnTheFly(square, block) | RookAttacksOnTheFly(square, block);
}

// Set occupancy map for attack mask
U64 setOccupancy(int index, int bitsInMask, U64 attackMask) {
    U64 occupancy = 0ULL;

    for (int i = 0; i < bitsInMask; i++) {
        int square = getLeastSignificant1stBitIndex(attackMask);
        popBit(attackMask, square);

        if (index & (1 << i))
            occupancy |= (1ULL << square);
    }

    return occupancy;
}

// Initialize leaper piece attacks (pawn, knight, king)
void init_leapers_attacks() {
    for (int square = 0; square < 64; square++) {
        pawnAttacks[0][square] = maskPawnAttacks(square, 0); // White
        pawnAttacks[1][square] = maskPawnAttacks(square, 1); // Black
        knightAttacks[square] = maskKnightAttacks(square);
        kingAttacks[square] = maskKingAttacks(square);
    }
}

// Generate a random magic number
U64 generateMagicNumber() {
    return randomU64() & randomU64() & randomU64();
}

// Initialize slider piece attack tables (bishop or rook)
void initSliderAttacks(int bishop) {
    for (int square = 0; square < 64; square++) {
        // Init bishop and rook masks
        bishopMasks[square] = maskBishopAttacks(square);
        rookMasks[square] = maskRookAttacks(square);

        // Init current attack mask
        U64 attackMask = bishop ? bishopMasks[square] : rookMasks[square];

        // Init relevant occupancy bit count
        int relevantBits = countBits(attackMask);

        // Init occupancy indices
        int occupancyIndices = 1 << relevantBits;

        // Loop over occupancy indices
        for (int index = 0; index < occupancyIndices; index++) {
            U64 occupancy = setOccupancy(index, relevantBits, attackMask);

            if (bishop) {
                int magicIndex = (occupancy * bishopMagicNumbers[square]) >> (64 - bishopRelevantBits[square]);
                bishopAttacks[square][magicIndex] = BishopAttacksOnTheFly(square, occupancy);
            } else {
                int magicIndex = (occupancy * rookMagicNumbers[square]) >> (64 - rookRelevantBits[square]);
                rookAttacks[square][magicIndex] = RookAttacksOnTheFly(square, occupancy);
            }
        }
    }
}


// Get bishop attacks given occupancy
U64 getBishopAttacks(int square, U64 occupancy) {
    occupancy &= bishopMasks[square];
    occupancy *= bishopMagicNumbers[square];
    occupancy >>= (64 - bishopRelevantBits[square]);

    return bishopAttacks[square][occupancy];
}

// Get rook attacks given occupancy
U64 getRookAttacks(int square, U64 occupancy) {
    occupancy &= rookMasks[square];
    occupancy *= rookMagicNumbers[square];
    occupancy >>= (64 - rookRelevantBits[square]);

    return rookAttacks[square][occupancy];
}