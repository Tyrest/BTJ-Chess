#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#define B_K   'k'
#define B_Q   'q'
#define B_B   'b'
#define B_N   'n'
#define B_R   'r'
#define B_P   'p'
#define NON   '.'
#define W_P   'P'
#define W_R   'R'
#define W_N   'N'
#define W_B   'B'
#define W_Q   'Q'
#define W_K   'K'
#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

namespace std
{
    class Board
    {
    public:
        char mailbox[64];
        bool turn; // White is true
        int enpassant;
        Board();
        Board(string fen);
        void set_fen(string fen);
        void print();
        char result();
        void push_move(int from, int to);
        void render_htmml(string outfile);
    };
}

#endif // BOARD_H Guard