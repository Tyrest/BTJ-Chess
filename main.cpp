#include <iostream>

#include "board.h"
#include "movegen.h"

using namespace std;

void test_gen(string fen)
{
    Board board = Board();
    board.set_fen(fen);
    MoveGen gen;
    board.print();
    
    // for (auto it : gen.piece_centric(board, board.turn))
    // {
    //     cout << it.first << '\n';
    //     for (auto pos : it.second)
    //         cout << pos << ' ';
    //     cout << '\n';
    // }

    map<int, vector<int>> moves = gen.gen(board);
    // for (auto it : moves)
    //     for (auto to : it.second)
    //         cout << it.first << " " << to << '\n';
    for (auto move : gen.uci_moves(moves))
        cout << move << '\n';
}

int main()
{
    // test_gen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    // testing a vertical pin
    test_gen("3k4/8/3q4/3r4/8/3N4/8/3K4 w - - 0 1");
}   
