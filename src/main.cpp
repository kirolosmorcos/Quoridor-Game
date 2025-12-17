//
// Created by kiro3 on 12/10/2025.
//

#include "Models/GameState.h"
#include "Game Logic/Legal Moves.h"
#include <bits/stdc++.h>

using namespace std;

GameState createTestState()
{
    GameState s{};
    s.turn = true;
    s.player0_pos = 4;
    s.player1_pos = 76;

    memset(s.horizontal_walls, false, sizeof(s.horizontal_walls));
    memset(s.vertical_walls, false, sizeof(s.vertical_walls));

    s.p0_walls = 10;
    s.p1_walls = 10;

    // Existing walls (for conflict testing)
    s.horizontal_walls[3][4] = true;
    s.horizontal_walls[3][5] = true; // full horizontal wall

    s.vertical_walls[4][3] = true;
    s.vertical_walls[5][3] = true;   // full vertical wall

    return s;
}

// Detect which *2-unit* horizontal wall was added
void printAddedHorizontal(const GameState& before, const GameState& after)
{
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            if (!before.horizontal_walls[r][c] &&
                !before.horizontal_walls[r][c + 1] &&
                after.horizontal_walls[r][c] &&
                after.horizontal_walls[r][c + 1])
            {
                cout << "Horizontal wall at [(" << r << "," << c
                     << ") + (" << r << "," << c + 1 << ")]\n";
            }
        }
    }
}

// Detect which *2-unit* vertical wall was added
void printAddedVertical(const GameState& before, const GameState& after)
{
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            if (!before.vertical_walls[r][c] &&
                !before.vertical_walls[r + 1][c] &&
                after.vertical_walls[r][c] &&
                after.vertical_walls[r + 1][c])
            {
                cout << "Vertical wall at [(" << r << "," << c
                     << ") + (" << r + 1 << "," << c << ")]\n";
            }
        }
    }
}

// ---------------- main ----------------

int main()
{
    GameState state = createTestState();

    cout << "=== Horizontal Wall Moves (Quoridor) ===\n";
    auto hMoves = horizontalWallMoves(state, true);

    cout << "Total: " << hMoves.size() << "\n";
    for (const auto& s : hMoves)
        printAddedHorizontal(state, s);

    cout << "\n=== Vertical Wall Moves (Quoridor) ===\n";
    auto vMoves = verticalWallMoves(state, true);

    cout << "Total: " << vMoves.size() << "\n";
    for (const auto& s : vMoves)
        printAddedVertical(state, s);

    return 0;
}