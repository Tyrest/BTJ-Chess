#ifndef MOVEGEN_H
#define MOVEGEN_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <algorithm>

#include "board.h"

#define BISHOP_OFFSETS {-9, -7, 7, 9}
#define ROOK_OFFSETS {-8, -1, 1, 8}
#define QUEEN_OFFSETS {-9, -8, -7, -1, 1, 7, 8, 9}
#define KNIGHT_OFFSETS {-17, -15, -10, -6, 6, 10, 15, 17}

namespace std
{
    class MoveGen
    {
    private:
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

        bool is_edge(int index) const { return (index % 8 == 0 || index % 8 == 7); }

        // by switching the ally and enemy sets, the danger squares can be identified
        unordered_set<int> pawn_attack(vector<int> positions, bool turn);
        vector<pair<int, int>> check_pins(Board board, int king, unordered_set<int> ally, unordered_set<int> enemy);
        bool king_danger(Board board, int king, unordered_set<int> ally, unordered_set<int> enemy);

        map<int, vector<int>> pawn_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy, bool turn);
        map<int, vector<int>> bishop_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy);
        map<int, vector<int>> knight_moves(vector<int> positions, unordered_set<int> ally);
        map<int, vector<int>> rook_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy);
        map<int, vector<int>> queen_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy);
        map<int, vector<int>> sliding_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy,
                                             const int *offsets, size_t offsets_size);
        pair<unordered_set<int>, unordered_set<int>> ally_enemy(Board board, bool turn);
        map<int, vector<int>> king_moves(int pos, unordered_set<int> ally, unordered_set<int> danger={});
    public:
        map<char, vector<int>> piece_centric(Board board, bool turn);
        map<int, vector<int>> gen(Board board);
        vector<string> uci_moves(map<int, vector<int>> moves);
        string pos_to_uci(int from, int to);
        pair<int, int> uci_to_pos(string uci);
    };
}

#endif // MOVEGEN_H Guard
