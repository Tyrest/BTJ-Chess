#include "movegen.hpp"

using namespace std;

#define all(x) begin(x), end(x)

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

// map<int, vector<int>> MoveGen::pawn_moves(vector<int> positions, vector<int> ally, vector<int> enemy)
// {
//     for (auto pos : positions)
//     {

//     }
// }

map<int, vector<int>> MoveGen::sliding_pieces(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy,
                                              const int *offsets, size_t offsets_size)
{
    map<int, vector<int>> moves;
    for (auto pos : positions)
    {
        for (int i = 0; i < offsets_size; i++)
        {
            int offset = offsets[i];
            int cpos = pos;
            bool collision = false;
            while (!(BOARD_EDGE[cpos] && BOARD_EDGE[cpos+offset]) && !collision &&
                    cpos+offset >= 0 && cpos+offset < 64)
            {
                cpos += offset;
                if (ally.count(cpos))
                    collision = true;
                else
                {
                    moves[pos].push_back(cpos);
                    if (enemy.count(cpos))
                        collision = true;
                }
            }
        }
    }
    return moves;
}

map<int, vector<int>> MoveGen::bishop_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy)
{
    return sliding_pieces(positions, ally, enemy, BISHOP_OFFSETS, 4);
}

map<int, vector<int>> MoveGen::knight_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy)
{
    map<int, vector<int>> moves;
    for (auto pos : positions)
        for (int i = 0; i < 8; i++)
            if (((KNIGHT_LEGAL[pos] & ( 1 << 8-i )) >> 8-i) && !ally.count(pos+KNIGHT_OFFSETS[i]))
                moves[pos].push_back(pos+KNIGHT_OFFSETS[i]);
    return moves;
}

map<int, vector<int>> MoveGen::rook_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy)
{
    return sliding_pieces(positions, ally, enemy, ROOK_OFFSETS, 4);
}

map<int, vector<int>> MoveGen::queen_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy)
{
    return sliding_pieces(positions, ally, enemy, QUEEN_OFFSETS, 8);
}

// map<int, vector<int>> MoveGen::king_moves(int pos, vector<int> ally, vector<int> enemy)
// {
    
// }

string MoveGen::pos_to_uci(int from, int to)
{
    string uci;
    uci += char(97 + from % 8);
    uci += char(56 - from / 8);
    uci += char(97 + to % 8);
    uci += char(56 - to / 8);
    return uci;
}

map<char, vector<int>> MoveGen::piece_centric(Board board, bool turn)
{
    map<char, vector<int>> positions;
    for (int i = 0; i < 64; i++)
    {
        char piece = board.mailbox[i];
        if (piece != NON && int(piece) > 96 != turn)
        {
            if (turn) positions[char(int(piece)+32)].push_back(i);
            else positions[piece].push_back(i);
        }
    }
    return positions;
}

/*
Generates two lists of vectors that reveal the ally and enemy
positions on the board for quick access during move generation

First vector is a list of all the ally positions on the board,
second is a list of all the enemy positions on the board
*/
pair<unordered_set<int>, unordered_set<int>> MoveGen::ally_enemy(Board board, bool turn)
{
    unordered_set<int> ally, enemy;
    for (int i = 0; i < 64; i++)
    {
        char piece = board.mailbox[i];
        if (piece != NON)
        {
            if (int(piece) > 96 != turn)
                ally.insert(i);
            else
                enemy.insert(i);
            
        }
    }
    return make_pair(ally, enemy);
}

map<int, vector<int>> MoveGen::gen(Board board)
{
    map<int, vector<int>> moves;

    map<char, vector<int>> positions = piece_centric(board, !board.turn);
    unordered_set<int> ally, enemy;

    tie(ally, enemy) = ally_enemy(board, !board.turn);
    
    // moves.insert(all(pawn_moves(positions['p'], board)));
    map<int, vector<int>> b_moves = bishop_moves(positions['b'], ally, enemy);
    map<int, vector<int>> n_moves = knight_moves(positions['n'], ally, enemy);
    map<int, vector<int>> r_moves = rook_moves(positions['r'], ally, enemy);
    map<int, vector<int>> q_moves = queen_moves(positions['q'], ally, enemy);
    // moves.insert(all(king_moves(positions['k'][0], board)));

    moves.insert(all(b_moves));
    moves.insert(all(n_moves));
    moves.insert(all(r_moves));
    moves.insert(all(q_moves));

    // vector<string> uci_moves = convert_to_uci(moves);

    return moves;
}

vector<string> MoveGen::uci_moves(map<int, vector<int>> moves)
{
    vector<string> uci_moves;
    for (auto it : moves)
        for (auto to : it.second)
            uci_moves.push_back(pos_to_uci(it.first, to));
    return uci_moves;
}