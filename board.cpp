#include "board.hpp"

using namespace std;

Board::Board()
{
    set_fen(START_FEN);
}

Board::Board(string fen)
{
    set_fen(fen);
}

void Board::set_fen(string fen)
{
    for (int i = 0; i < 64; i++)
        mailbox[i] = NON;
        
    int index = 0;

    int i;
    for (i = 0; i < fen.length(); i++)
    {
        if (fen[i] != '/')
        {
            if (fen[i] == ' ') break;
            else if (int(fen[i]) < 58) index += int(fen[i]) - 48;
            else {mailbox[index] = fen[i]; index++;}
        }
    }
    // if turn is true, it is white's move
    if (fen[i+1] == 'w') turn = true;
    else turn = false;
    i += 3;

    // Add some more stuff (castling, en passant, 50 halfmove clock, fullmove number)
}

void Board::print()
{
    for (int i = 0; i < 64; i++)
    {
        cout << mailbox[i];
        if ((i+1) % 8 == 0)
            cout << '\n';
    }
}