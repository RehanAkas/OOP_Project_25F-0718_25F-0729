#include <cmath>
#include "pieces.h"
#include "board.h"   
char Pawn::GetSymbol() const {
    return (pieceColor == White) ? 'P' : 'p';
}
bool Pawn::IsValidMove(Board& b, int fR, int fC, int tR, int tC) {
    int dir = (pieceColor == White) ? -1 : 1;
    int startRow = (pieceColor == White) ? 6 : 1;
    if (fC == tC && b.IsEmpty(tR, tC)) {
        if (tR == fR + dir) return true;                                          // one step forward
        if (fR == startRow && tR == fR + 2 * dir && b.IsEmpty(fR + dir, fC))
            return true;                                                           // two steps from starting row
    }
    if (abs(tC - fC) == 1 && tR == fR + dir) {
        Piece* target = b.GetPiece(tR, tC);
        if (target != nullptr && target->GetColor() != pieceColor) return true;
    }
    return false;
}
char Rook::GetSymbol() const {
    return (pieceColor == White) ? 'R' : 'r';
}
bool Rook::IsValidMove(Board& b, int fR, int fC, int tR, int tC) {
    if (fR != tR && fC != tC) return false;   // must move in a straight line
    return b.IsPathClear(fR, fC, tR, tC);
}
char Knight::GetSymbol() const {
    return (pieceColor == White) ? 'N' : 'n';
}
bool Knight::IsValidMove(Board& b, int fR, int fC, int tR, int tC) {
    (void)b;  // Knight jumps over pieces — no path check needed
    return (abs(tR - fR) == 2 && abs(tC - fC) == 1)
        || (abs(tR - fR) == 1 && abs(tC - fC) == 2);
}
char Bishop::GetSymbol() const {
    return (pieceColor == White) ? 'B' : 'b';
}
bool Bishop::IsValidMove(Board& b, int fR, int fC, int tR, int tC) {
    if (abs(tR - fR) != abs(tC - fC)) return false;   // must move diagonally
    return b.IsPathClear(fR, fC, tR, tC);
}
char Queen::GetSymbol() const {
    return (pieceColor == White) ? 'Q' : 'q';
}
bool Queen::IsValidMove(Board& b, int fR, int fC, int tR, int tC) {
    if (fR == tR || fC == tC || abs(tR - fR) == abs(tC - fC))
        return b.IsPathClear(fR, fC, tR, tC);
    return false;
}
char King::GetSymbol() const {
    return (pieceColor == White) ? 'K' : 'k';
}
bool King::IsValidMove(Board& b, int fR, int fC, int tR, int tC) {
    (void)b;  // King moves one square in any direction — no path check needed
    return abs(tR - fR) <= 1 && abs(tC - fC) <= 1;
}
