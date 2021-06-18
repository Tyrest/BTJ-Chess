#ifndef MOVEGEN_H
#define MOVEGEN_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>

#include "board.hpp"

namespace std
{
    class MoveGen
    {
    private:
        map<int, vector<int>> pawn_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy);
        map<int, vector<int>> bishop_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy);
        map<int, vector<int>> knight_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy);
        map<int, vector<int>> rook_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy);
        map<int, vector<int>> queen_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy);
        pair<unordered_set<int>, unordered_set<int>> ally_enemy(Board board, bool turn);
        map<int, vector<int>> king_moves(int pos, unordered_set<int> ally, unordered_set<int> enemy);
        string pos_to_uci(int from, int to);
    public:
        map<char, vector<int>> piece_centric(Board board, bool turn);
        map<int, vector<int>> gen(Board board);
        vector<string> uci_moves(map<int, vector<int>> moves);
    };
}

#endif // MOVEGEN_H Guard