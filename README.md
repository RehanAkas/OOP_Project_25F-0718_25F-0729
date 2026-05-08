# OOP_Project_25F-0718_25F-0729
# Chess Game — C++ OOP Project

A fully playable two-player chess game running in the terminal, written in C++ using core Object-Oriented Programming principles.

---

## Features

- Two-player turn-based gameplay (White vs Black)
- All standard pieces with correct movement rules: Pawn, Rook, Knight, Bishop, Queen, King
- Move validation including path-clear checks
- King-in-check detection — illegal moves that leave the king in check are blocked
- Clean 8×8 board rendered in the terminal after every move

---

## OOP Concepts Demonstrated

| Concept | Where Used |
|---|---|
| **Abstraction** | `piece` is an abstract base class with pure virtual functions |
| **Inheritance** | `pawn`, `rook`, `knight`, `bishop`, `queen`, `king` all inherit from `piece` |
| **Polymorphism** | `is_valid_move()` and `get_symbol()` are overridden in each subclass |
| **Composition** | `board` owns and manages an 8×8 array of `piece` pointers |
| **Encapsulation** | Board internals are private; interaction happens through public methods |

---

## File Structure

```
chess/
├── chess.h       # All class declarations (piece, subclasses, board)
├── chess.cpp     # All method implementations
└── main.cpp      # Game loop and entry point
```

---

## How to Compile & Run

**Using g++:**
```bash
g++ -o chess main.cpp chess.cpp
./chess
```

**On Windows:**
```bash
g++ -o chess.exe main.cpp chess.cpp
chess.exe
```

---

## How to Play

- The board is displayed after every move with column labels `a–h` and row numbers `1–8`
- Enter moves in the format `[from] [to]`, for example:

```
white's turn: e2 e4
```

- Uppercase letters represent White pieces, lowercase represent Black pieces

| Symbol | Piece |
|---|---|
| `P` / `p` | Pawn |
| `R` / `r` | Rook |
| `N` / `n` | Knight |
| `B` / `b` | Bishop |
| `Q` / `q` | Queen |
| `K` / `k` | King |

- Type `exit` at any time to quit the game

---

## Requirements

- C++11 or later
- Any C++ compiler (g++, clang++, MSVC)

---

## Limitations

The following standard chess rules are not yet implemented:

- Castling
- En passant
- Pawn promotion
- Checkmate / stalemate detection

---

## License

This project is open source and free to use for educational purposes.
