#include <iostream>
#include <vector>
#include <cstring>

#include "Models/GameState.h"
#include "Game Logic/Legal Moves.h"
#include "Game Logic/BFS.h"

using namespace std;

/*
ASSUMPTIONS (LOCKED):
--------------------------------
horizontal_walls[row][col] : blocks (row,col) <-> (row+1,col)
vertical_walls[row][col]   : blocks (row,col) <-> (row,col+1)
*/

// ------------------------------------------------------------
// EMPTY STATE
// ------------------------------------------------------------
GameState emptyState()
{
    GameState s{};
    s.turn = false;
    s.player0_pos = 4;      // (0,4)
    s.player1_pos = 76;     // (8,4)
    s.p0_walls = 10;
    s.p1_walls = 10;

    memset(s.horizontal_walls, false, sizeof(s.horizontal_walls));
    memset(s.vertical_walls, false, sizeof(s.vertical_walls));

    return s;
}

// ------------------------------------------------------------
// DRAW STATE
// ------------------------------------------------------------
void drawState(const GameState& s)
{
    cout << "\n========================================\n";

    for (int r = 0; r < 9; r++)
    {
        // Cells + vertical walls
        for (int c = 0; c < 9; c++)
        {
            int pos = r * 9 + c;

            if (pos == s.player0_pos)      cout << " 0 ";
            else if (pos == s.player1_pos) cout << " 1 ";
            else                           cout << " . ";

            if (c < 8)
            {
                if (s.vertical_walls[r][c])
                    cout << "|";
                else
                    cout << " ";
            }
        }
        cout << "\n";

        // Horizontal walls
        if (r < 8)
        {
            for (int c = 0; c < 9; c++)
            {
                if (s.horizontal_walls[r][c])
                    cout << "===";
                else
                    cout << "   ";

                if (c < 8) cout << " ";
            }
            cout << "\n";
        }
    }

    cout << "----------------------------------------\n";
    cout << "BFS P0 = " << bfs(s, false)
         << " | BFS P1 = " << bfs(s, true) << "\n";
}

// ------------------------------------------------------------
// BASE TEST STATE (maze-like)
// ------------------------------------------------------------
GameState baseTestState()
{
    GameState s = emptyState();

    // Some existing walls to make it interesting
    for(int c = 0; c < 8; c++) {
        s.horizontal_walls[2][c] = true;

    }

    s.vertical_walls[3][7] = true;
    s.vertical_walls[2][7] = true;



    return s;
}

// ------------------------------------------------------------
// MAIN
// ------------------------------------------------------------
int main()
{
    GameState base = baseTestState();

    cout << "\n===== BASE STATE =====\n";
    drawState(base);

    // --------------------------------------------------------
    // GENERATE WALL MOVES
    // --------------------------------------------------------
    auto hMoves = horizontalWallMoves(base, false);
    auto vMoves = verticalWallMoves(base, false);

    // --------------------------------------------------------
    // PRINT HORIZONTAL WALL MOVES
    // --------------------------------------------------------
    cout << "\n===== HORIZONTAL WALL MOVES =====\n";
    cout << "Total: " << hMoves.size() << "\n";

    for (size_t i = 0; i < hMoves.size(); i++)
    {
        cout << "\n--- Horizontal Move #" << i << " ---\n";
        drawState(hMoves[i]);
    }

    // --------------------------------------------------------
    // PRINT VERTICAL WALL MOVES
    // --------------------------------------------------------
    cout << "\n===== VERTICAL WALL MOVES =====\n";
    cout << "Total: " << vMoves.size() << "\n";

    for (size_t i = 0; i < vMoves.size(); i++)
    {
        cout << "\n--- Vertical Move #" << i << " ---\n";
        drawState(vMoves[i]);
    }

    return 0;
}
