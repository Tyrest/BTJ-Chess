#include "movegen.hpp"

using namespace std;

#define all(x) begin(x), end(x)

vector<string> MoveGen::pawn_moves(vector<int> positions, Board board)
{
    for (auto pos : positions)
    {

    }
}

vector<string> MoveGen::bishop_moves(vector<int> positions, Board board)
{
    for (auto pos : positions)
    {
        
    }
}

vector<string> MoveGen::knight_moves(vector<int> positions, Board board)
{
    for (auto pos : positions)
    {
        
    }
}

vector<string> MoveGen::rook_moves(vector<int> positions, Board board)
{
    for (auto pos : positions)
    {
        
    }
}

vector<string> MoveGen::queen_moves(vector<int> positions, Board board)
{
    for (auto pos : positions)
    {
        
    }
}

vector<string> MoveGen::king_moves(int pos, Board board)
{
    
}

map<char, vector<int>> MoveGen::piece_centric(Board board)
{
    map<char, vector<int>> positions;
    for (int i = 0; i < 64; i++)
    {
        char piece = board.mailbox[i/8][i%8];
        if (piece != NON && int(piece) > 96 != board.turn)
        {
            if (board.turn) positions[char(int(piece)+32)].push_back(i);
            else positions[piece].push_back(i);
        }
    }
    return positions;
}

vector<string> MoveGen::gen(Board board)
{
    vector<string> moves;

    map<char, vector<int>> positions = piece_centric(board);
    
    vector<string> moves_p = pawn_moves(positions['p'], board);
    vector<string> moves_b = bishop_moves(positions['b'], board);
    vector<string> moves_n = knight_moves(positions['n'], board);
    vector<string> moves_r = rook_moves(positions['r'], board);
    vector<string> moves_q = queen_moves(positions['q'], board);
    vector<string> moves_k = king_moves(positions['k'][0], board);
    
    moves.insert(moves.end(), all(moves_p));
    moves.insert(moves.end(), all(moves_b));
    moves.insert(moves.end(), all(moves_n));
    moves.insert(moves.end(), all(moves_r));
    moves.insert(moves.end(), all(moves_q));
    moves.insert(moves.end(), all(moves_k));

    return moves;
}