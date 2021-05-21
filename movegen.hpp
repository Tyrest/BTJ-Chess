#ifndef MOVEGEN_H
#define MOVEGEN_H

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "board.hpp"

namespace std
{
    class MoveGen
    {
    private:
        vector<string> pawn_moves(vector<int> positions, Board board);
        vector<string> bishop_moves(vector<int> positions, Board board);
        vector<string> knight_moves(vector<int> positions, Board board);
        vector<string> rook_moves(vector<int> positions, Board board);
        vector<string> queen_moves(vector<int> positions, Board board);
        vector<string> king_moves(int pos, Board board);
    public:
        map<char, vector<int>> piece_centric(Board board);
        vector<string> gen(Board board);
    };
}

#endif // MOVEGEN_H Guard