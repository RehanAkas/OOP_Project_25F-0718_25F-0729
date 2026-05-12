#ifndef PIECES_H
#define PIECES_H
class Board;
enum Color { White, Black };
class Piece {
protected:
    Color pieceColor;
public:
    Piece(Color color) : pieceColor(color) {}
    virtual ~Piece() {}
    Color GetColor() const { return pieceColor; }
    virtual char GetSymbol() const = 0;
    virtual bool IsValidMove(Board& board, int fromRow, int fromCol,
        int toRow, int toCol) = 0;
};
class Pawn : public Piece {
public:
    Pawn(Color c) : Piece(c) {}
    char GetSymbol() const override;
    bool IsValidMove(Board& b, int fR, int fC, int tR, int tC) override;
};

class Rook : public Piece {
public:
    Rook(Color c) : Piece(c) {}
    char GetSymbol() const override;
    bool IsValidMove(Board& b, int fR, int fC, int tR, int tC) override;
};
class Knight : public Piece {
public:
    Knight(Color c) : Piece(c) {}
    char GetSymbol() const override;
    bool IsValidMove(Board& b, int fR, int fC, int tR, int tC) override;
};
class Bishop : public Piece {
public:
    Bishop(Color c) : Piece(c) {}
    char GetSymbol() const override;
    bool IsValidMove(Board& b, int fR, int fC, int tR, int tC) override;
};
class Queen : public Piece {
public:
    Queen(Color c) : Piece(c) {}
    char GetSymbol() const override;
    bool IsValidMove(Board& b, int fR, int fC, int tR, int tC) override;
};
class King : public Piece {
public:
    King(Color c) : Piece(c) {}
    char GetSymbol() const override;
    bool IsValidMove(Board& b, int fR, int fC, int tR, int tC) override;
};
#endif // PIECES_H
