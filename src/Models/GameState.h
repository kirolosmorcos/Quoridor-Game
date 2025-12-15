#ifndef QUORIDOR_GAMESTATE_H
#define QUORIDOR_GAMESTATE_H


class GameState
{
public:

    bool turn;
    int player0_pos;
    int player1_pos;
    bool horizontal_walls[8][9];
    bool vertical_walls[9][8];
    int p0_walls;
    int p1_walls;

    static int getrow(int pos)
    {
        return pos / 9;
    }
    static int getcol(int pos)
    {
        return pos % 9;
    }
};


#endif //QUORIDOR_GAMESTATE_H
