# Catherine Chess Engine

Catherine is a chess engine written in C++ that focuses on efficient bitboard-based move generation and attack calculations. The project is currently in development, with the following features implemented so far:

## Features Implemented

### Bitboard Representation
- The chessboard is represented using a 64-bit integer (`U64`), where each bit corresponds to a square on the board.
- Bit manipulation techniques are used for efficient move generation and attack calculations.

### Attack Masks
- Functions to generate attack masks for various pieces:
  - **Pawn Attacks**: Calculates possible pawn attacks based on the side (white or black).
  - **Knight Attacks**: Generates all possible knight moves from a given square.
  - **King Attacks**: Generates all possible king moves from a given square.
  - **Bishop Attacks**: Calculates diagonal attacks for bishops.
  - **Rook Attacks**: Calculates horizontal and vertical attacks for rooks.
  - **Queen Attacks**: Combines bishop and rook attacks to calculate queen moves.

### On-the-Fly Attack Generation
- Functions to calculate attacks dynamically, considering blockers (other pieces on the board):
  - **BishopAttacksOnTheFly**
  - **RookAttacksOnTheFly**
  - **QueenAttacksOnTheFly**

### Utility Functions
- **Bit Manipulation Macros**:
  - `getBit`, `setBit`, and `popBit` for efficient bitboard operations.
- **Bit Counting**:
  - `count_bits` to count the number of set bits in a bitboard.
- **Least Significant Bit Index**:
  - `getLeastSignificant1stBitIndex` to find the index of the least significant set bit.
- **Occupancy Calculation**:
  - `setOccupancy` to generate occupancy bitboards based on attack masks.

### Random Number Generation
- A custom implementation of the XORWOW algorithm for generating random numbers, which can be used for Zobrist hashing in the future.

### Debugging and Visualization
- A `printBitBoard` function to visualize bitboards in a human-readable format.


## Next Steps
- Refactor the code to separate attack tables and on-the-fly attack generation into their respective files for better modularity.
- Implement move generation and validation.
- Add Zobrist hashing for board state representation.
- Develop a search algorithm (e.g., Minimax with Alpha-Beta pruning).
- Create a user interface for playing against the engine.

## License
This project is currently under development and does not have a license yet.

## Contributing
Contributions are welcome! Feel free to fork the repository and submit pull requests.

---

