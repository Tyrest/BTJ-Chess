#include "board.h"
#include "movegen.h"

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

    size_t i;
    for (i = 0; i < fen.length(); i++)
    {
        if (fen[i] != '/')
        {
            if (fen[i] == ' ')
                break;
            else if (int(fen[i]) < 58)
                index += int(fen[i]) - 48;
            else
            {
                mailbox[index] = fen[i];
                index++;
            }
        }
    }
    // if turn is true, it is white's move
    if (fen[i + 1] == 'w')
        turn = true;
    else
        turn = false;
    i += 3;

    // Add some more stuff (castling, en passant, 50 halfmove clock, fullmove number)
}

void Board::push_move(int from, int to)
{
    MoveGen gen;
    map<int, vector<int>> moves = gen.gen(*this);
    if (moves.find(from) != moves.end())
    {
        for (auto it : moves[from])
        {
            if (it == to)
            {
                mailbox[to] = mailbox[from];
                mailbox[from] = NON;
                turn = !turn;
                return;
            }
        }
    }

    cout << "Illegal move\n";
}

void Board::print()
{
    for (int i = 0; i < 64; i++)
    {
        cout << mailbox[i];
        if ((i + 1) % 8 == 0)
            cout << '\n';
    }
}

void Board::render_htmml(string outfile)
{
    map<char, string> pieces = {
        {B_K, "♚"},
        {B_Q, "♛"},
        {B_B, "♝"},
        {B_N, "♞"},
        {B_R, "♜"},
        {B_P, "♟"},
        {NON, " "},
        {W_P, "♙"},
        {W_R, "♖"},
        {W_N, "♘"},
        {W_B, "♗"},
        {W_Q, "♕"},
        {W_K, "♔"}};

    ofstream out(outfile);
    out << "<!DOCTYPE html>\n";
    out << "<html>\n";
    out << "<head>\n";
    out << "<meta charset=\"UTF-8\">\n";
    out << "<style>\n";
    out << ".chess-board { border-spacing: 0; border-collapse: collapse; }\n";
    out << ".chess-board th { padding: .5em; }\n";
    out << ".chess-board th + th { border-bottom: 1px solid #000; }\n";
    out << ".chess-board th:first-child,\n";
    out << ".chess-board td:last-child { border-right: 1px solid #000; }\n";
    out << ".chess-board tr:last-child td { border-bottom: 1px solid; }\n";
    out << ".chess-board th:empty { border: none; }\n";
    out << ".chess-board td { width: 1.5em; height: 1.5em; text-align: center; font-size: 32px; line-height: 0;}\n";
    out << ".chess-board .light { background: #eee; }\n";
    out << ".chess-board .dark { background: #aaa; }\n";
    out << "</style>";
    out << "</head>\n";
    out << "<body>\n";
    out << "<table class=\"chess-board\">\n";
    out << "<tbody>\n";
    out << "<tr>\n";
    out << "<th></th>\n";
    out << "<th>a</th>\n";
    out << "<th>b</th>\n";
    out << "<th>c</th>\n";
    out << "<th>d</th>\n";
    out << "<th>e</th>\n";
    out << "<th>f</th>\n";
    out << "<th>g</th>\n";
    out << "<th>h</th>\n";
    out << "</tr>\n";
    for (int i = 0; i < 8; i++)
    {

    }
    for (int i = 0; i < 8; i++)
    {
        out << "<tr>\n";
        out << "<th>" << 8 - i << "</th>\n";
        for (int j = 0; j < 8; j++)
        {
            if (mailbox[i * 8 + j] == NON)
                out << "<td class=\"" << ((i + j) % 2 == 0 ? "light" : "dark") << "\"></td>\n";
            else
                out << "<td class=\"" << ((i + j) % 2 == 0 ? "light" : "dark") << "\">" << pieces[mailbox[i * 8 + j]] << "</td>\n";
        }
        out << "</tr>\n";
    }
    out << "</tbody>\n";
    out << "</table>\n";
    out << "</body>\n";
    out << "</html>\n";
}