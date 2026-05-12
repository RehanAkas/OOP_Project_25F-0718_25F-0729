#include <iostream>
#include "board.h"
using namespace std;
Board::Board() {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            squares[i][j] = nullptr;
    Color colors[2] = { Black, White };
    int   rows[2] = { 0, 7 };       
    int   pawnRows[2] = { 1, 6 };      
    for (int i = 0; i < 2; i++) {
        squares[rows[i]][0] = new Rook(colors[i]);
        squares[rows[i]][7] = new Rook(colors[i]);
        squares[rows[i]][1] = new Knight(colors[i]);
        squares[rows[i]][6] = new Knight(colors[i]);
        squares[rows[i]][2] = new Bishop(colors[i]);
        squares[rows[i]][5] = new Bishop(colors[i]);
        squares[rows[i]][3] = new Queen(colors[i]);
        squares[rows[i]][4] = new King(colors[i]);
        for (int j = 0; j < 8; j++)
            squares[pawnRows[i]][j] = new Pawn(colors[i]);
    }
}
Board::~Board() {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            delete squares[i][j];
}
Piece* Board::GetPiece(int row, int col) const {
    return squares[row][col];
}
bool Board::IsInside(int row, int col) const {
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}
bool Board::IsEmpty(int row, int col) const {
    return squares[row][col] == nullptr;
}
bool Board::IsPathClear(int fromRow, int fromCol, int toRow, int toCol) {
    int rowStep = (toRow > fromRow) ? 1 : (toRow < fromRow ? -1 : 0);
    int colStep = (toCol > fromCol) ? 1 : (toCol < fromCol ? -1 : 0);
    int currRow = fromRow + rowStep;
    int currCol = fromCol + colStep;
    while (currRow != toRow || currCol != toCol) {
        if (!IsEmpty(currRow, currCol)) return false;  // something is blocking the path
        currRow += rowStep;
        currCol += colStep;
    }
    return true;
}
void Board::MovePiece(int fromRow, int fromCol, int toRow, int toCol) {
    if (squares[toRow][toCol] != nullptr)
        delete squares[toRow][toCol];          // delete captured piece from heap
    squares[toRow][toCol] = squares[fromRow][fromCol];
    squares[fromRow][fromCol] = nullptr;
}
bool Board::NeedsPromotion(Color turn) const {
    int backRank = (turn == White) ? 0 : 7;   // White promotes at row 0, Black at row 7
    for (int c = 0; c < 8; c++) {
        Piece* p = squares[backRank][c];
        if (p && p->GetColor() == turn
            && (p->GetSymbol() == 'P' || p->GetSymbol() == 'p'))
            return true;
    }
    return false;
}
void Board::PromotePawn(int row, int col, char choice) {
    Piece* p = squares[row][col];
    if (!p) return;                    // safety check: nothing to promote

    Color c = p->GetColor();           // save color before deleting the pawn
    delete squares[row][col];          // free the pawn from heap memory
    switch (choice) {
    case 'r': squares[row][col] = new Rook(c); break;
    case 'b': squares[row][col] = new Bishop(c); break;
    case 'n': squares[row][col] = new Knight(c); break;
    case 'q': // fall through — Queen is default
    default:  squares[row][col] = new Queen(c); break;
    }
}
bool Board::IsKingInCheck(Color turn) {
    int kR = -1, kC = -1;  // -1 = not found yet (-1 is impossible on a 0-7 board)
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece* p = GetPiece(r, c);
            if (p && p->GetColor() == turn
                && (p->GetSymbol() == 'K' || p->GetSymbol() == 'k')) {
                // p square is not empty
                // p->GetColor() == turn belongs to current player
                // GetSymbol() == K/k it is actually the King
                kR = r; kC = c; break;
            }
        }
    }
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece* p = GetPiece(r, c);
            if (p && p->GetColor() != turn
                && p->IsValidMove(*this, r, c, kR, kC)) return true;
            // p->GetColor() != turn            — enemy piece
            // IsValidMove(..., kR, kC)         — can legally reach King's square
        }
    }
    return false;  // King is safe
}
bool Board::IsLegalMove(int fR, int fC, int tR, int tC, Color turn) {
    if (!IsInside(fR, fC) || !IsInside(tR, tC)) return false;
    Piece* p = GetPiece(fR, fC);
    if (!p || p->GetColor() != turn) return false;       // no piece or wrong color
    Piece* target = GetPiece(tR, tC);
    if (target && target->GetColor() == turn) return false;  // can't capture own piece
    if (!p->IsValidMove(*this, fR, fC, tR, tC)) return false;
    // Simulate the move temporarily to verify the King is not left in check
    Piece* saved = squares[tR][tC];
    squares[tR][tC] = squares[fR][fC];
    squares[fR][fC] = nullptr;
    bool inCheck = IsKingInCheck(turn);
    // Undo the simulation
    squares[fR][fC] = squares[tR][tC];
    squares[tR][tC] = saved;
    return !inCheck;   // move is legal only if kimg is not in check afterward
}
bool Board::MakeMove(int fR, int fC, int tR, int tC, Color turn) {
    if (IsLegalMove(fR, fC, tR, tC, turn)) {
        MovePiece(fR, fC, tR, tC);
        return true;
    }
    return false;
}
void Board::Display() {
    cout << "\n    a   b   c   d   e   f   g   h\n";
    cout << "  +---+---+---+---+---+---+---+---+\n";
    for (int i = 0; i < 8; i++) {
        cout << 8 - i << " |";
        for (int j = 0; j < 8; j++) {
            if (squares[i][j]) cout << " " << squares[i][j]->GetSymbol() << " |";
            else                cout << "   |";
        }
        cout << " " << 8 - i << "\n  +---+---+---+---+---+---+---+---+\n";
    }
    cout << "    a   b   c   d   e   f   g   h\n";
}
