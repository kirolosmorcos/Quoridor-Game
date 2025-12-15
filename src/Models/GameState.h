//
// Created by kiro3 on 12/10/2025.
//

#ifndef QUORIDOR_GAMESTATE_H
#define QUORIDOR_GAMESTATE_H


class GameState
{
public:

    bool turn;
    int player0_pos;
    int player1_pos; //ai player
    bool horizontal_walls[8][9];
    bool vertical_walls[9][8];
    int p0_walls;
    int p1_walls;

    int getrow(int pos)
    {
        return pos / 9;
    }
    int getcol(int pos)
    {
        return pos % 9;
    }
};


#endif //QUORIDOR_GAMESTATE_H
