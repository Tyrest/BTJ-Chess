# const int KNIGHT_OFFSETS[8] = {-17, -15, -10, -6, 6, 10, 15, 17};
board = []
for index in range(64):
    moves = 0
    if index < 48:
        if index % 8 < 7:
            moves += 1
        if index % 8 > 0:
            moves += 2
    if index < 56:
        if index % 8 < 6:
            moves += 4
        if index % 8 > 1:
            moves += 8
    if index >= 8:
        if index % 8 < 6:
            moves += 16
        if index % 8 > 1:
            moves += 32
    if index >= 16:
        if index % 8 < 7:
            moves += 64
        if index % 8 > 0:
            moves += 128
    board.append(moves)
for i in range(8):
    print(board[8*i:8*(i+1)])
