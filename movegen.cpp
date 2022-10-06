#include "movegen.h"

using namespace std;

#define all(x) begin(x), end(x)

unordered_set<int> MoveGen::pawn_attack(vector<int> positions, bool turn)
{
    unordered_set<int> moves;

    int dir;
    if (turn)
        dir = -1;
    else
        dir = 1;

    for (auto pos : positions)
    {
        if (pos % 8)
            moves.insert(pos + 8 * dir - 1);
        if (!(pos % 8 == 7))
            moves.insert(pos + 8 * dir + 1);
    }
    return moves;
}

unordered_set<int> MoveGen::check_pins(Board board, int king, unordered_set<int> ally, unordered_set<int> enemy)
{
    unordered_set<int> pinned;
    for (auto offset : BISHOP_OFFSETS)
    {
        int pos = king + offset;
        while (pos >= 0 && pos < 64 && !BOARD_EDGE[pos] &&
               board.mailbox[pos] == NON)
            pos += offset;

        if (pos >= 0 && pos < 64 && !BOARD_EDGE[pos] &&
            ally.find(pos) != ally.end())
        {
            int pos2 = pos + offset;
            while (pos2 >= 0 && pos2 < 64 && !BOARD_EDGE[pos] && board.mailbox[pos2] == NON)
                pos2 += offset;
            if (pos2 >= 0 && pos2 < 64 && enemy.find(pos2) != enemy.end())
                if (tolower(board.mailbox[pos2]) == B_B || tolower(board.mailbox[pos2]) == B_Q)
                    pinned.insert(pos);
        }
    }

    for (auto offset : ROOK_OFFSETS)
    {
        int pos = king + offset;
        while (pos >= 0 && pos < 64 && !BOARD_EDGE[pos] &&
               board.mailbox[pos] == NON)
            pos += offset;

        if (pos >= 0 && pos < 64 && !BOARD_EDGE[pos] &&
            ally.find(pos) != ally.end())
        {
            int pos2 = pos + offset;
            while (pos2 >= 0 && pos2 < 64 && !BOARD_EDGE[pos] && board.mailbox[pos2] == NON)
                pos2 += offset;
            if (pos2 >= 0 && pos2 < 64 && enemy.find(pos2) != enemy.end())
                if (tolower(board.mailbox[pos2]) == B_R || tolower(board.mailbox[pos2]) == B_Q)
                    pinned.insert(pos);
        }
    }

    return pinned;
}

// Doesn't deal with promotions yet so have to encode that somehow
map<int, vector<int>> MoveGen::pawn_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy, bool turn)
{
    map<int, vector<int>> moves;
    int dir;
    int low, high;
    if (turn)
    {
        low = 47;
        high = 55;
        dir = -1;
    }
    else
    {
        low = 7;
        high = 15;
        dir = 1;
    }
    for (auto pos : positions)
    {
        // If the pawn is still on the home row
        if (pos > low && pos <= high)
            if (!ally.count(pos + 16 * dir) && !enemy.count(pos + 16 * dir) &&
                !ally.count(pos + 8 * dir) && !enemy.count(pos + 8 * dir))
                moves[pos].push_back(pos + 16 * dir);

        // Not on the left side of the board
        if (pos % 8)
            if (enemy.count(pos + 8 * dir - 1))
                moves[pos].push_back(pos + 8 * dir - 1);

        // Not on the right side of the board
        if (!(pos % 8 == 7))
            if (enemy.count(pos + 8 * dir + 1))
                moves[pos].push_back(pos + 8 * dir + 1);

        if (!enemy.count(pos + 8 * dir) && !ally.count(pos + 8 * dir))
            moves[pos].push_back(pos + 8 * dir);
    }
    return moves;
}

map<int, vector<int>> MoveGen::sliding_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy,
                                             const int *offsets, size_t offsets_size)
{
    map<int, vector<int>> moves;
    for (auto pos : positions)
    {
        for (size_t i = 0; i < offsets_size; i++)
        {
            int offset = offsets[i];
            int cpos = pos;
            bool collision = false;
            while (!(BOARD_EDGE[cpos] && BOARD_EDGE[cpos + offset]) && !collision &&
                   cpos + offset >= 0 && cpos + offset < 64)
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
    return sliding_moves(positions, ally, enemy, BISHOP_OFFSETS, 4);
}

map<int, vector<int>> MoveGen::knight_moves(vector<int> positions, unordered_set<int> ally)
{
    map<int, vector<int>> moves;
    for (auto pos : positions)
        for (int i = 0; i < 8; i++)
            // WTF does this even mean?
            if (((KNIGHT_LEGAL[pos] & (1 << (7 - i))) >> (7 - i)) && !ally.count(pos + KNIGHT_OFFSETS[i]))
                moves[pos].push_back(pos + KNIGHT_OFFSETS[i]);
    return moves;
}

map<int, vector<int>> MoveGen::rook_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy)
{
    return sliding_moves(positions, ally, enemy, ROOK_OFFSETS, 4);
}

map<int, vector<int>> MoveGen::queen_moves(vector<int> positions, unordered_set<int> ally, unordered_set<int> enemy)
{
    return sliding_moves(positions, ally, enemy, QUEEN_OFFSETS, 8);
}

map<int, vector<int>> MoveGen::king_moves(int pos, unordered_set<int> ally, unordered_set<int> danger /*= {}*/)
{
    map<int, vector<int>> moves;
    for (auto offset : QUEEN_OFFSETS)
        if (!(BOARD_EDGE[pos] && BOARD_EDGE[pos + offset]) &&
            (pos + offset >= 0 && pos + offset < 64) &&
            !ally.count(pos + offset) && !danger.count(pos + offset))
            moves[pos].push_back(pos + offset);
    return moves;
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

map<char, vector<int>> MoveGen::piece_centric(Board board, bool turn)
{
    map<char, vector<int>> positions;
    for (int i = 0; i < 64; i++)
    {
        char piece = board.mailbox[i];
        if (piece != NON && (int(piece) > 96) != turn)
        {
            if (turn)
                positions[char(int(piece) + 32)].push_back(i);
            else
                positions[piece].push_back(i);
        }
    }
    return positions;
}

/*
   Generates two lists of vectors that reveal the ally and enemy
   positions on the board for quick access during move generation

   First set is a list of all the ally positions on the board,
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
            if ((int(piece) > 96) != turn)
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

    // Use the same ally and enemy vectors to generate danger and moves
    tie(ally, enemy) = ally_enemy(board, board.turn);

    unordered_set<int> danger = pawn_attack(positions['p'], board.turn);
    vector<map<int, vector<int>>> attacks;
    attacks.push_back(bishop_moves(positions['b'], ally, enemy));
    attacks.push_back(knight_moves(positions['n'], ally));
    attacks.push_back(rook_moves(positions['r'], ally, enemy));
    attacks.push_back(queen_moves(positions['q'], ally, enemy));
    attacks.push_back(king_moves(positions['k'][0], ally)); // No danger squares
    for (auto attack : attacks)
        for (auto piece : attack)
            for (auto move : piece.second)
                danger.insert(move);

    // change positions to the color that is going to move
    positions = piece_centric(board, board.turn);

    // To do:
    // Check for check and how to get out of it (or checkmate)
    // Check for pins and put them in a list
    // If moving a piece in the pins set, run the king_danger method
    unordered_set<int> pins = check_pins(board, positions['k'][0], ally, enemy);

    map<int, vector<int>> p_moves = pawn_moves(positions['p'], ally, enemy, board.turn);
    map<int, vector<int>> b_moves = bishop_moves(positions['b'], ally, enemy);
    map<int, vector<int>> n_moves = knight_moves(positions['n'], ally);
    map<int, vector<int>> r_moves = rook_moves(positions['r'], ally, enemy);
    map<int, vector<int>> q_moves = queen_moves(positions['q'], ally, enemy);
    map<int, vector<int>> k_moves = king_moves(positions['k'][0], ally, danger);

    moves.insert(all(p_moves));
    moves.insert(all(b_moves));
    moves.insert(all(n_moves));
    moves.insert(all(r_moves));
    moves.insert(all(q_moves));
    moves.insert(all(k_moves));

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
