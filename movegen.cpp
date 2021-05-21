#include "movegen.hpp"

using namespace std;

#define all(x) begin(x), end(x)

const int ROOK_OFFSETS[4] = {-8, -1, 1, 8};
const int BISHOP_OFFSETS[4] = {-9, -7, 7, 9};
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

map<int, vector<int>> MoveGen::pawn_moves(vector<int> positions, Board board)
{
    for (auto pos : positions)
    {

    }
}

map<int, vector<int>> MoveGen::bishop_moves(vector<int> positions, Board board)
{
    for (auto pos : positions)
    {
        
    }
}

map<int, vector<int>> MoveGen::knight_moves(vector<int> positions, Board board)
{
    map<int, vector<int>> moves;
    for (auto pos : positions)
        for (int i = 0; i < 8; i++)
            if ((KNIGHT_LEGAL[pos] & ( 1 << 8-i )) >> 8-i)
                moves[pos].push_back(pos+KNIGHT_OFFSETS[i]);
    return moves;
}

map<int, vector<int>> MoveGen::rook_moves(vector<int> positions, Board board)
{
    for (auto pos : positions)
    {
        
    }
}

map<int, vector<int>> MoveGen::queen_moves(vector<int> positions, Board board)
{
    for (auto pos : positions)
    {
        
    }
}

map<int, vector<int>> MoveGen::king_moves(int pos, Board board)
{
    
}

string MoveGen::pos_to_uci(int from, int to)
{
    string uci;
    uci += char(97 + from % 8);
    uci += char(56 - from / 8);
    uci += char(97 + to % 8);
    uci += char(56 - to / 8);
    return uci;
}

map<char, vector<int>> MoveGen::piece_centric(Board board)
{
    map<char, vector<int>> positions;
    for (int i = 0; i < 64; i++)
    {
        char piece = board.mailbox[i];
        if (piece != NON && int(piece) > 96 != board.turn)
        {
            if (board.turn) positions[char(int(piece)+32)].push_back(i);
            else positions[piece].push_back(i);
        }
    }
    return positions;
}

map<int, vector<int>> MoveGen::gen(Board board)
{
    map<int, vector<int>> moves;

    map<char, vector<int>> positions = piece_centric(board);
    
    // moves.insert(all(pawn_moves(positions['p'], board)));
    // moves.insert(all(bishop_moves(positions['b'], board)));
    map<int, vector<int>> n_moves = knight_moves(positions['n'], board);
    moves.insert(all(n_moves));
    // moves.insert(all(rook_moves(positions['r'], board)));
    // moves.insert(all(queen_moves(positions['q'], board)));
    // moves.insert(all(king_moves(positions['k'][0], board)));

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