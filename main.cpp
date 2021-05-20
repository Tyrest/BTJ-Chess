#include <iostream>

#include "board.hpp"
#include "movegen.hpp"

using namespace std;

int main()
{
    Board board = Board();
    MoveGen gen;
    board.print();
    for (auto move : gen.gen(board))
        cout << move << '\n';
}