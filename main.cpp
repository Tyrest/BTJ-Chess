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

void play()
{
    Board board = Board();
    MoveGen gen;
    string move;
    while (true)
    {
        board.print();
        board.render_htmml("index.html");
        cout << "Enter move (" << (board.turn ? "white" : "black") << "): ";
        cin >> move;
        pair<int, int> pos_move = gen.uci_to_pos(move);
        board.push_move(pos_move.first, pos_move.second);
        cout << '\n';
    }
}

int main(int argc, char *argv[])
{
    if (argc == 2 && argv[1] == string("play"))
    {
        play();
    }
    else if (argc == 3 && argv[1] == string("test"))
    {
        test_gen(argv[2]);
    }
    else
    {
        cout << "Usage: " << argv[0] << " <MODE> <FEN>\n";
        return 0;
    }

    // test_gen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    // testing a vertical pin
    // test_gen("3k4/8/3q4/3r4/8/3N4/8/3K4 w - - 0 1");
    // test_gen("3k4/8/5b2/3r2Bb/q7/3R1B2/2Q5/3K4 b - - 0 1");
}   
