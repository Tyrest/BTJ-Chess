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
        const int BISHOP_OFFSETS[4] = {-9, -7, 7, 9};
        const int ROOK_OFFSETS[4] = {-8, -1, 1, 8};
        const int QUEEN_OFFSETS[8] = {-9, -8, -7, -1, 1, 7, 8, 9};
        const int KNIGHT_OFFSETS[8] = {-17, -15, -10, -6, 6, 10, 15, 17};
        // Idea is computing the spaces the knight can jump to in constant time
        const unsigned char KNIGHT_LEGAL[64] =
        {
            5,  7,   15,  15,  15,  15,  11,  10,
            21, 23,  63,  63,  63,  63,  43,  42,
            85, 215, 255, 255, 255, 255, 235, 170,
            85, 215, 255, 255, 255, 255, 235, 170,
            85, 215, 255, 255, 255, 255, 235, 170,
            85, 215, 255, 255, 255, 255, 235, 170,
            84, 212, 252, 252, 252, 252, 232, 168,
            80, 208, 240, 240, 240, 240, 224, 160
        };

        const bool BOARD_EDGE[64] =
        {
            1, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 0, 1
        };

        // by switching the ally and enemy sets, the danger squares can be identified
        unordered_set<int> pawn_attack(vector<int> positions);

        map<int, vector<int>> pawn_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy, bool turn);
        map<int, vector<int>> bishop_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy);
        map<int, vector<int>> knight_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy);
        map<int, vector<int>> rook_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy);
        map<int, vector<int>> queen_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy);
        map<int, vector<int>> sliding_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy,
                                             const int *offsets, size_t offsets_size);
        pair<unordered_set<int>, unordered_set<int>> ally_enemy(Board board, bool turn);
        map<int, vector<int>> king_moves(int pos, unordered_set<int> ally, unordered_set<int> enemy, unordered_set<int> danger={});
        string pos_to_uci(int from, int to);
    public:
        map<char, vector<int>> piece_centric(Board board, bool turn);
        map<int, vector<int>> gen(Board board);
        vector<string> uci_moves(map<int, vector<int>> moves);
    };
}

#endif // MOVEGEN_H Guard