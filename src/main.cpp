#include <iostream>
#include <string>
#include "chess.h"
using namespace std;
bool parse_input(const string& in, int& row, int& col) {
    if (in.length() != 2) return false;
    col = in[0] - 'a';
    row = 8 - (in[1] - '0');
    return (col >= 0 && col < 8 && row >= 0 && row < 8);
}

int main() {
    board game;
    color turn = white;
    string pos1, pos2;

    cout << "chess game - c++ oop project\n";
    cout << "enter moves like 'e2 e4'. type 'exit' to quit.\n";

    while (true) {
        game.display();
        cout << (turn == white ? "white's turn: " : "black's turn: ");
        cin >> pos1;
        if (pos1 == "exit") break;
        cin >> pos2;

        int from_row, from_col, to_row, to_col;
        if (parse_input(pos1, from_row, from_col) && parse_input(pos2, to_row, to_col)) {
            if (game.make_move(from_row, from_col, to_row, to_col, turn)) {

                // check if a pawn reached the back rank and needs promotion
                if (game.needs_promotion(turn)) {
                    int back_rank = (turn == white) ? 0 : 7;

                    // to find that on which column the pawn landed on
                    int promo_col = to_col;

                    cout << "** pawn promotion! choose piece (q=queen, r=rook, b=bishop, n=knight): ";
                    char choice;
                    cin >> choice;

                    // keep asking until a valid choice is given
                    while (choice != 'q' && choice != 'r' && choice != 'b' && choice != 'n') {
                        cout << "!! invalid choice. enter q, r, b, or n: ";
                        cin >> choice;
                    }

                    game.promote_pawn(back_rank, promo_col, choice);
                    cout << "** pawn promoted to ";
                    switch (choice) {
                    case 'r': cout << "rook\n";   break;
                    case 'b': cout << "bishop\n"; break;
                    case 'n': cout << "knight\n"; break;
                    default:  cout << "queen\n";  break;
                    }
                }

                turn = (turn == white) ? black : white;
            }
            else {
                cout << "!! invalid move !!\n";
            }
        }
        else {
            cout << "!! invalid input format (e.g., a2 a4) !!\n";
        }
    }

    system("pause");
    return 0;
}
