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
        map<char, vector<pair<int, int>>> MoveGen::piece_centric(Board board);
        vector<string> pawn_moves(vector<pair<int, int>> positions, Board board);
        vector<string> bishop_moves(vector<pair<int, int>> positions, Board board);
        vector<string> knight_moves(vector<pair<int, int>> positions, Board board);
        vector<string> rook_moves(vector<pair<int, int>> positions, Board board);
        vector<string> queen_moves(vector<pair<int, int>> positions, Board board);
        vector<string> king_moves(pair<int, int> pos, Board board);
    public:
        vector<string> gen(Board board);
    };
}

#endif // MOVEGEN_H Guard