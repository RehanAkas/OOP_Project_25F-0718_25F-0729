#include <iostream>
#include <string>
#include "board.h"  
using namespace std;
bool Parse(string in, int& r, int& c) {
    if (in.length() != 2) return false;
    c = in[0] - 'a';        // 'a'=0, 'b'=1, ... 'h'=7
    r = 8 - (in[1] - '0'); // '8'=0, '7'=1, ... '1'=7
    return (c >= 0 && c < 8 && r >= 0 && r < 8);
}
int main() {
    Board game;
    Color turn = White;
    string pos1, pos2;
    cout << "Chess Game - C++ OOP Project\n";
    cout << "Enter moves like 'e2 e4'. Type 'exit' to quit.\n";
    while (true) {
        game.Display();
        cout << (turn == White ? "White's Turn: " : "Black's Turn: ");
        cin >> pos1;
        if (pos1 == "exit") break;
        cin >> pos2;
        int fR, fC, tR, tC;
        if (Parse(pos1, fR, fC) && Parse(pos2, tR, tC)) {
            if (game.MakeMove(fR, fC, tR, tC, turn)) {
                // ── PAWN PROMOTION CHECK ──────────────────────────────────
                if (game.NeedsPromotion(turn)) {
                    int backRank = (turn == White) ? 0 : 7; // White=row 0, Black=row 7
                    cout << "** Pawn Promotion! Choose a piece:\n";
                    cout << "   q = Queen   r = Rook   b = Bishop   n = Knight\n";
                    cout << "Your choice: ";
                    char choice;
                    cin >> choice;
                    while (choice != 'q' && choice != 'r'
                        && choice != 'b' && choice != 'n') {
                        cout << "!! Invalid choice. Enter q, r, b, or n: ";
                        cin >> choice;
                    }
                    game.PromotePawn(backRank, tC, choice);
                    cout << "** Pawn promoted to ";
                    switch (choice) {
                    case 'r': cout << "Rook!\n";   break;
                    case 'b': cout << "Bishop!\n"; break;
                    case 'n': cout << "Knight!\n"; break;
                    default:  cout << "Queen!\n";  break;
                    }
                }
               turn = (turn == White) ? Black : White; // switch turn only after promotion is done
            }
            else {
                cout << "!! Invalid Move !!\n";
            }
        }
        else {
            cout << "!! Invalid Input Format (e.g., a2 a4) !!\n";
        }
    }
    return 0;
}
