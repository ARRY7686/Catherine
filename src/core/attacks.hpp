#pragma once
#include "bitboard.hpp"

extern const int bishopRelevantBits[64];
extern const int rookRelevantBits[64];

extern U64 pawnAttacks[2][64];
extern U64 knightAttacks[64]; 
extern U64 kingAttacks[64];
extern U64 bishopAttacks[64];
extern U64 rookAttacks[64];
extern U64 queenAttacks[64];

U64 maskPawnAttacks(int square,int side);
U64 maskKnightAttacks(int square);
U64 maskKingAttacks(int square);
U64 maskBishopAttacks(int square);
U64 maskRookAttacks(int square);
U64 maskQueenAttacks(int square);
U64 BishopAttacksOnTheFly(int square, U64 block);
U64 RookAttacksOnTheFly(int square, U64 block);
U64 queenAttacksOnTheFly(int square, U64 block);
U64 setOccupancy(int index,int bitsInMask,U64 attackMask);
void init_leapers_attacks();
U64 generateMagicNumber();