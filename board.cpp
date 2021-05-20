#include "board.hpp"

using namespace std;

Board::Board()
{
    for (int i = 0; i < 64; i++)
        mailbox[i/8][i%8] = NON;
    (*this).set_fen(START_FEN);
}

void Board::set_fen(string fen)
{
    int row = 0;
    int col = 0;

    int i;
    for (i = 0; i < fen.length(); i++)
    {
        if (fen[i] == '/') {row++; col = 0;}
        else if (fen[i] == ' ') break;
        else if (int(fen[i]) < 58) col += int(fen[i]) - 48;
        else {mailbox[row][col] = fen[i]; col++;}
    }
    // if turn is true, it is white's move
    if (fen[i+1] == 'w') turn = true;
    else turn = false;
    i += 3;

    // Add some more stuff (castling, en passant, 50 halfmove clock, fullmove number)
}

void Board::print()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            cout << mailbox[i][j];
        cout << '\n';
    }
}

vector<string> Board::generate_moves()
{

}