#ifndef BOARD_H
#define BOARD_H
#include "pieces.h"   
class Board {
private:
    Piece* squares[8][8];   

public:
    Board();    // sets up all pieces at their starting positions
    ~Board();   // deletes all heap-allocated pieces to avoid memory leaks
    Piece* GetPiece(int row, int col) const;
    bool   IsInside(int row, int col) const;   // checks if (row,col) is on the board
    bool   IsEmpty(int row, int col) const;   // checks if square has no piece
    bool IsPathClear(int fromRow, int fromCol, int toRow, int toCol);  // no pieces in between
    void MovePiece(int fromRow, int fromCol, int toRow, int toCol);  // physically moves piece
    bool NeedsPromotion(Color turn) const;           // checks if pawn reached back rank
    void PromotePawn(int row, int col, char choice);  // swaps pawn for chosen piece
    bool IsKingInCheck(Color turn);
    bool IsLegalMove(int fromRow, int fromCol, int toRow, int toCol, Color turn);
    bool MakeMove(int fromRow, int fromCol, int toRow, int toCol, Color turn);
    void Display();
};
#endif
