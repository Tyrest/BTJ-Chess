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
        map<int, vector<int>> pawn_moves(vector<int> positions, Board board);
        map<int, vector<int>> bishop_moves(vector<int> positions, Board board);
        map<int, vector<int>> knight_moves(vector<int> positions, Board board);
        map<int, vector<int>> rook_moves(vector<int> positions, Board board);
        map<int, vector<int>> queen_moves(vector<int> positions, Board board);
        map<int, vector<int>> king_moves(int pos, Board board);
        string pos_to_uci(int from, int to);
    public:
        map<char, vector<int>> piece_centric(Board board);
        map<int, vector<int>> gen(Board board);
        vector<string> uci_moves(map<int, vector<int>> moves);
    };
}

#endif // MOVEGEN_H Guard