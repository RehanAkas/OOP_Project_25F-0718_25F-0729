#include <iostream>
#include <cmath>
#include "chess.h"

using namespace std;

// pawn 
char pawn::get_symbol() const {
    return (piece_color == white) ? 'P' : 'p';
}

bool pawn::is_valid_move(board& b, int from_row, int from_col, int to_row, int to_col) {
    int dir = (piece_color == white) ? -1 : 1;
    int start_row = (piece_color == white) ? 6 : 1;

    // forward move
    if (from_col == to_col && b.is_empty(to_row, to_col)) {
        if (to_row == from_row + dir) return true;
        if (from_row == start_row && to_row == from_row + 2 * dir
            && b.is_empty(from_row + dir, from_col)) return true;
    }

    // diagonal move k liay
    if (abs(to_col - from_col) == 1 && to_row == from_row + dir) {
        piece* target = b.get_piece(to_row, to_col);
        if (target != nullptr && target->get_color() != piece_color) return true;
    }

    return false;
}

// rook 

char rook::get_symbol() const {
    return (piece_color == white) ? 'R' : 'r';
}

bool rook::is_valid_move(board& b, int from_row, int from_col, int to_row, int to_col) {
    if (from_row != to_row && from_col != to_col) return false;
    return b.is_path_clear(from_row, from_col, to_row, to_col);
}

// knight 
char knight::get_symbol() const {
    return (piece_color == white) ? 'N' : 'n';
}

bool knight::is_valid_move(board& b, int from_row, int from_col, int to_row, int to_col) {
    (void)b;
    return (abs(to_row - from_row) == 2 && abs(to_col - from_col) == 1)
        || (abs(to_row - from_row) == 1 && abs(to_col - from_col) == 2);
}

//bishop 

char bishop::get_symbol() const {
    return (piece_color == white) ? 'B' : 'b';
}

bool bishop::is_valid_move(board& b, int from_row, int from_col, int to_row, int to_col) {
    if (abs(to_row - from_row) != abs(to_col - from_col)) return false;
    return b.is_path_clear(from_row, from_col, to_row, to_col);
}

// queen 

char queen::get_symbol() const {
    return (piece_color == white) ? 'Q' : 'q';
}

bool queen::is_valid_move(board& b, int from_row, int from_col, int to_row, int to_col) {
    if (from_row == to_row || from_col == to_col
        || abs(to_row - from_row) == abs(to_col - from_col))
        return b.is_path_clear(from_row, from_col, to_row, to_col);
    return false;
}

// king 

char king::get_symbol() const {
    return (piece_color == white) ? 'K' : 'k';
}

bool king::is_valid_move(board& b, int from_row, int from_col, int to_row, int to_col) {
    (void)b;
    return abs(to_row - from_row) <= 1 && abs(to_col - from_col) <= 1;
}

//  board constructor / destructor 

board::board() {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            squares[i][j] = nullptr;

    color colors[2] = { black, white };
    int   rows[2] = { 0, 7 };
    int   pawn_rows[2] = { 1, 6 };

    for (int i = 0; i < 2; i++) {
        squares[rows[i]][0] = new rook(colors[i]);
        squares[rows[i]][7] = new rook(colors[i]);
        squares[rows[i]][1] = new knight(colors[i]);
        squares[rows[i]][6] = new knight(colors[i]);
        squares[rows[i]][2] = new bishop(colors[i]);
        squares[rows[i]][5] = new bishop(colors[i]);
        squares[rows[i]][3] = new queen(colors[i]);
        squares[rows[i]][4] = new king(colors[i]);
        for (int j = 0; j < 8; j++)
            squares[pawn_rows[i]][j] = new pawn(colors[i]);
    }
}

board::~board() {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            delete squares[i][j];
}

// board utility methods 

piece* board::get_piece(int row, int col) const {
    return squares[row][col];
}

bool board::is_inside(int row, int col) const {
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}

bool board::is_empty(int row, int col) const {
    return squares[row][col] == nullptr;
}

bool board::is_path_clear(int from_row, int from_col, int to_row, int to_col) {
    int row_step = (to_row > from_row) ? 1 : (to_row < from_row ? -1 : 0);
    int col_step = (to_col > from_col) ? 1 : (to_col < from_col ? -1 : 0);

    int curr_row = from_row + row_step;
    int curr_col = from_col + col_step;

    while (curr_row != to_row || curr_col != to_col) {
        if (!is_empty(curr_row, curr_col)) return false;
        curr_row += row_step;
        curr_col += col_step;
    }
    return true;
}

void board::move_piece(int from_row, int from_col, int to_row, int to_col) {
    if (squares[to_row][to_col] != nullptr)
        delete squares[to_row][to_col];
    squares[to_row][to_col] = squares[from_row][from_col];
    squares[from_row][from_col] = nullptr;
}

// board game logic k liay

bool board::is_king_in_check(color turn) {
    int king_row = -1, king_col = -1;

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            piece* p = get_piece(r, c);
            if (p && p->get_color() == turn
                && (p->get_symbol() == 'K' || p->get_symbol() == 'k')) {
                king_row = r;
                king_col = c;
                break;
            }
        }
    }

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            piece* p = get_piece(r, c);
            if (p && p->get_color() != turn
                && p->is_valid_move(*this, r, c, king_row, king_col))
                return true;
        }
    }
    return false;
}

bool board::is_legal_move(int from_row, int from_col, int to_row, int to_col, color turn) {
    if (!is_inside(from_row, from_col) || !is_inside(to_row, to_col)) return false;

    piece* p = get_piece(from_row, from_col);
    if (!p || p->get_color() != turn) return false;

    piece* target = get_piece(to_row, to_col);
    if (target && target->get_color() == turn) return false;

    if (!p->is_valid_move(*this, from_row, from_col, to_row, to_col)) return false;

    // simulate move to verify king safety
    piece* saved = squares[to_row][to_col];
    squares[to_row][to_col] = squares[from_row][from_col];
    squares[from_row][from_col] = nullptr;

    bool in_check = is_king_in_check(turn);

    // undo simulation
    squares[from_row][from_col] = squares[to_row][to_col];
    squares[to_row][to_col] = saved;

    return !in_check;
}

bool board::make_move(int from_row, int from_col, int to_row, int to_col, color turn) {
    if (is_legal_move(from_row, from_col, to_row, to_col, turn)) {
        move_piece(from_row, from_col, to_row, to_col);
        return true;
    }
    return false;
}

//  pawn promotion 
bool board::needs_promotion(color turn) const {
    int back_rank = (turn == white) ? 0 : 7;
    for (int c = 0; c < 8; c++) {
        piece* p = squares[back_rank][c];
        if (p && p->get_color() == turn
            && (p->get_symbol() == 'P' || p->get_symbol() == 'p'))
            return true;
    }
    return false;
}

void board::promote_pawn(int row, int col, char choice) {
    piece* p = squares[row][col];
    if (!p) return;

    color c = p->get_color();
    delete squares[row][col];

    switch (choice) {
    case 'r': squares[row][col] = new rook(c); break;
    case 'b': squares[row][col] = new bishop(c); break;
    case 'n': squares[row][col] = new knight(c); break;
    case 'q': 
    default:  squares[row][col] = new queen(c); break;
    }
}

void board::display() {
    cout << "\n    a   b   c   d   e   f   g   h\n";
    cout << "  +---+---+---+---+---+---+---+---+\n";
    for (int i = 0; i < 8; i++) {
        cout << 8 - i << " |";
        for (int j = 0; j < 8; j++) {
            if (squares[i][j])
                cout << " " << squares[i][j]->get_symbol() << " |";
            else
                cout << "   |";
        }
        cout << " " << 8 - i << "\n  +---+---+---+---+---+---+---+---+\n";
    }
    cout << "    a   b   c   d   e   f   g   h\n";
}
