#include <iostream>
#include <string>
#include "chess.h"
using namespace std;
// parse a chess coordinate string like "e2" into row and column indices
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
    cout << "Chess game [c++ oop project] \n";
    cout << "INSTRUCTIONS: " << endl;
    cout << "->Capital letters represent WHITE " << endl;
    cout << "->Small letters represent BLACK " << endl;
    cout << "->Enter moves like 'e2 e4'"<<endl;
    cout<<"->Type 'exit' to quit.\n";

    while (true) {
        game.display();
        cout << (turn == white ? "white's turn: " : "black's turn: ");
        cin >> pos1;
        if (pos1 == "exit") break;
        cin >> pos2;

        int from_row, from_col, to_row, to_col;
        if (parse_input(pos1, from_row, from_col) && parse_input(pos2, to_row, to_col)) {
            if (game.make_move(from_row, from_col, to_row, to_col, turn)) {
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
