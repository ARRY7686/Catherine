#pragma once
#include "bitboard.hpp"
#include "attacks.hpp"
#include <string.h>

extern U64 rookMagicNumbers[64];
extern U64 bishopMagicNumbers[64];

U64 findMagicNumber(int square,int relevantBits, int bishop);
void initMagicNumbers();
void initAll();