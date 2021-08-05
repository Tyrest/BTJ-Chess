#include <iostream>

#include "board.hpp"
#include "movegen.hpp"

using namespace std;

int main()
{
    Board board = Board();
    board.set_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    MoveGen gen;
    board.print();
    
    for (auto it : gen.piece_centric(board, board.turn))
    {
        cout << it.first << '\n';
        for (auto pos : it.second)
            cout << pos << ' ';
        cout << '\n';
    }

    map<int, vector<int>> moves = gen.gen(board);
    for (auto it : moves)
        for (auto to : it.second)
            cout << it.first << " " << to << '\n';
    for (auto move : gen.uci_moves(moves))
        cout << move << '\n';
}   