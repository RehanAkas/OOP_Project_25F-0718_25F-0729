#ifndef CHESS_H
#define CHESS_H
#include <cmath>
// forward declaration
class board;
enum color { white, black };
//base class: piece
class piece {
protected:
    color piece_color;
public:
    piece(color c) : piece_color(c) {}
    virtual ~piece() {}

    color get_color() const { return piece_color; }

    virtual char get_symbol()   const = 0;
    virtual bool is_valid_move(board& b, int from_row, int from_col,
        int to_row, int to_col) = 0;
};
// piece subclasses
class pawn : public piece {
public:
    pawn(color c) : piece(c) {}
    char get_symbol() const override;
    bool is_valid_move(board& b, int from_row, int from_col,
        int to_row, int to_col) override;
};

class rook : public piece {
public:
    rook(color c) : piece(c) {}
    char get_symbol() const override;
    bool is_valid_move(board& b, int from_row, int from_col,
        int to_row, int to_col) override;
};
class knight : public piece {
public:
    knight(color c) : piece(c) {}
    char get_symbol() const override;
    bool is_valid_move(board& b, int from_row, int from_col,
        int to_row, int to_col) override;
};
class bishop : public piece {
public:
    bishop(color c) : piece(c) {}
    char get_symbol() const override;
    bool is_valid_move(board& b, int from_row, int from_col,
        int to_row, int to_col) override;
};
class queen : public piece {
public:
    queen(color c) : piece(c) {}
    char get_symbol() const override;
    bool is_valid_move(board& b, int from_row, int from_col,
        int to_row, int to_col) override;
};
class king : public piece {
public:
    king(color c) : piece(c) {}
    char get_symbol() const override;
    bool is_valid_move(board& b, int from_row, int from_col,
        int to_row, int to_col) override;
};

// board class
class board {
private:
    piece* squares[8][8];

public:
    board();
    ~board();

    piece* get_piece(int row, int col) const;
    bool   is_inside(int row, int col) const;
    bool   is_empty(int row, int col) const;

    bool is_path_clear(int from_row, int from_col, int to_row, int to_col);
    void move_piece(int from_row, int from_col, int to_row, int to_col);

    bool is_king_in_check(color turn);
    bool is_legal_move(int from_row, int from_col, int to_row, int to_col, color turn);
    bool make_move(int from_row, int from_col, int to_row, int to_col, color turn);

    void display();
};
#endif // CHESS_H
