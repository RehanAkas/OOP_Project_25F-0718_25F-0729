# Chess Game — C++ OOP Project

A fully playable two-player terminal chess game written in C++, built around core Object-Oriented Programming principles. Both players share the same keyboard on the same machine, taking turns entering moves.

---

## Table of Contents

- [Features](#features)
- [File Structure](#file-structure)
- [How to Compile](#how-to-compile)
- [How to Play](#how-to-play)
- [Piece Movement Rules](#piece-movement-rules)
- [Pawn Promotion](#pawn-promotion)
- [OOP Concepts Used](#oop-concepts-used)
- [Code Architecture](#code-architecture)
- [Known Limitations](#known-limitations)

---

## Features

- Two-player turn-based gameplay (White vs Black) in the terminal
- All 6 standard chess pieces with correct movement rules
- Path-clear validation for Rook, Bishop, and Queen (blocked pieces cannot jump)
- King-in-check detection — any move that leaves your own King in check is rejected
- Move simulation — before committing a move, the game temporarily applies it and checks King safety, then undoes it
- Pawn promotion — when a pawn reaches the back rank, the player chooses a replacement piece
- Clean board display after every move with column labels `a–h` and row numbers `1–8`
- Invalid move and invalid input detection with helpful error messages

---

## File Structure

```
chess/
├── pieces.h      # Color enum, Piece base class, all 6 subclass declarations
├── pieces.cpp    # All 6 subclass method bodies (GetSymbol, IsValidMove)
├── board.h       # Board class declaration
├── board.cpp     # All Board method bodies (logic, promotion, display)
└── main.cpp      # Parse() helper and the game loop
```

### Why this split?

`pieces.h` only **forward declares** `Board` (`class Board;`) so that `Piece::IsValidMove(Board& b, ...)` compiles without a circular include. The full `Board` definition is only needed in `pieces.cpp` where the method bodies actually call `b.IsEmpty()` and `b.GetPiece()`, so `board.h` is included there. `board.h` then safely includes `pieces.h` because all piece classes are already fully declared at that point.

Include chain:
```
main.cpp   →  board.h  →  pieces.h
board.cpp  →  board.h  →  pieces.h
pieces.cpp →  board.h  →  pieces.h
```

---

## How to Compile

**Linux / Mac:**
```bash
g++ -std=c++11 -o chess main.cpp pieces.cpp board.cpp
./chess
```

**Windows:**
```bash
g++ -std=c++11 -o chess.exe main.cpp pieces.cpp board.cpp
chess.exe
```

Any C++11-compatible compiler works (g++, clang++, MSVC).

---

## How to Play

After launching, the board is displayed and the game prompts for White's move first.

**Input format:** type the source square followed by a space and the destination square, then press Enter.

```
White's Turn: e2 e4
```

- Columns are labeled `a` through `h` (left to right)
- Rows are labeled `1` through `8` (bottom to top)
- Square `e2` means column e, row 2

Type `exit` at any prompt to quit the game.

### Board Display

```
    a   b   c   d   e   f   g   h
  +---+---+---+---+---+---+---+---+
8 | r | n | b | q | k | b | n | r | 8
  +---+---+---+---+---+---+---+---+
7 | p | p | p | p | p | p | p | p | 7
  +---+---+---+---+---+---+---+---+
6 |   |   |   |   |   |   |   |   | 6
  ...
```

**Uppercase** letters = White pieces. **Lowercase** letters = Black pieces.

| Symbol | Piece  |
|--------|--------|
| `P` / `p` | Pawn   |
| `R` / `r` | Rook   |
| `N` / `n` | Knight |
| `B` / `b` | Bishop |
| `Q` / `q` | Queen  |
| `K` / `k` | King   |

---

## Piece Movement Rules

### Pawn (`P` / `p`)
- Moves **one square forward** (White moves up toward row 8, Black moves down toward row 1)
- Can move **two squares forward** from its starting row (row 2 for White, row 7 for Black), but only if both squares ahead are empty
- Captures **one square diagonally forward** — can only capture an enemy piece this way, never move diagonally to an empty square

### Rook (`R` / `r`)
- Moves any number of squares **horizontally or vertically**
- Cannot jump over pieces — the entire path must be clear

### Knight (`N` / `n`)
- Moves in an **L-shape**: two squares in one direction then one square perpendicular (or vice versa)
- The **only piece that can jump** over other pieces — path obstruction does not apply

### Bishop (`B` / `b`)
- Moves any number of squares **diagonally**
- Cannot jump over pieces — the entire diagonal path must be clear
- Each Bishop stays on its own color of square for the entire game

### Queen (`Q` / `q`)
- Combines the Rook and Bishop — moves any number of squares **horizontally, vertically, or diagonally**
- Cannot jump over pieces — the entire path must be clear

### King (`K` / `k`)
- Moves exactly **one square in any direction** (horizontal, vertical, or diagonal)
- Cannot move into a square that would put it in check
- Any move that leaves the King in check is automatically rejected

---

## Pawn Promotion

When a Pawn reaches the **opposite end of the board** (row 8 for White, row 1 for Black), it must be promoted to a more powerful piece. The game detects this automatically after the move and prompts the current player:

```
** Pawn Promotion! Choose a piece:
   q = Queen   r = Rook   b = Bishop   n = Knight
Your choice: q
** Pawn promoted to Queen!
```

- The player must enter one of: `q`, `r`, `b`, or `n`
- The game keeps asking until a valid character is entered
- The pawn is removed from the board and replaced by the chosen piece of the same color
- The opponent's turn begins only after promotion is complete
- Queen is also the fallback if something unexpected is entered

---

## OOP Concepts Used

### Abstraction
`Piece` is an **abstract base class** with two pure virtual functions:
```cpp
virtual char GetSymbol() const = 0;
virtual bool IsValidMove(Board& board, int fromRow, int fromCol, int toRow, int toCol) = 0;
```
No `Piece` object can be created directly — it exists only to define the interface every piece must follow.

### Inheritance
All 6 piece classes — `Pawn`, `Rook`, `Knight`, `Bishop`, `Queen`, `King` — inherit from `Piece` and provide their own implementation of `GetSymbol()` and `IsValidMove()`.

### Polymorphism
The `Board` class stores all pieces as `Piece*` pointers. When calling `p->IsValidMove(...)` or `p->GetSymbol()`, C++ automatically calls the correct version for whichever piece type is actually stored at that pointer — Pawn rules for pawns, Rook rules for rooks, and so on. This happens through the **virtual function mechanism** at runtime.

### Composition
`Board` **owns** an 8×8 array of `Piece*` pointers (`squares[8][8]`). The board is composed of pieces — it manages their lifetime, creates them in the constructor with `new`, and destroys them in the destructor with `delete`.

### Encapsulation
`Board::squares` is private. All interaction with the board happens through public methods like `GetPiece()`, `MakeMove()`, and `Display()`. No code outside `Board` can directly touch the internal grid.

---

## Code Architecture

### Move Validation Flow

Every move goes through this chain before being applied:

```
MakeMove()
    └── IsLegalMove()
            ├── IsInside()             — coordinates are on the board
            ├── GetPiece()             — a piece exists at the source square
            ├── GetColor()             — the piece belongs to the current player
            ├── GetColor() on target   — not capturing own piece
            ├── IsValidMove()          — piece-specific movement rule (Polymorphism)
            └── Simulate + IsKingInCheck() — move does not leave King in check
                        └── Undo simulation
```

### Check Detection

`IsKingInCheck(Color turn)` works in two passes:
1. Scans the entire board to find the King of the given color
2. Scans the entire board again — for every enemy piece, calls `IsValidMove()` toward the King's square. If any enemy piece can legally reach it, the King is in check.

### Memory Management

Every piece is created on the heap with `new` inside `Board::Board()`. This keeps pieces alive for the duration of the game regardless of scope. `Board::~Board()` loops through all 64 squares and calls `delete` on each non-null pointer. Captured pieces are also deleted inside `MovePiece()` when a destination square is overwritten. Promoted pawns are deleted inside `PromotePawn()` before the new piece is allocated.

---

## Known Limitations

The following standard chess rules are not yet implemented:

- **Castling** — the King-and-Rook special move
- **En passant** — the special pawn capture
- **Checkmate detection** — the game does not announce when a player has no legal moves remaining
- **Stalemate detection** — the game does not detect a draw when a player has no legal moves but is not in check
- **Draw conditions** — fifty-move rule, threefold repetition, and insufficient material are not tracked

---

## Requirements

- C++11 or later
- Any standard C++ compiler: g++, clang++, or MSVC
