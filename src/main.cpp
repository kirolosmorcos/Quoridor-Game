//#include <iostream>
//#include <vector>
//#include <cstring>
//
//#include "Models/GameState.h"
//#include "Game Logic/Legal Moves.h"
//#include "Game Logic/BFS.h"
//#include "AI/Best Move.h"
//
//using namespace std;
//
///*
//ASSUMPTIONS (LOCKED):
//--------------------------------
//horizontal_walls[row][col] : blocks (row,col) <-> (row+1,col)
//vertical_walls[row][col]   : blocks (row,col) <-> (row,col+1)
//*/
//
//// ------------------------------------------------------------
//// EMPTY STATE
//// ------------------------------------------------------------
//GameState emptyState()
//{
//    GameState s{};
//    s.turn = false;
//    s.player0_pos = 76;      // (0,4)
//    s.player1_pos = 4;     // (8,4)
//    s.p0_walls = 10;
//    s.p1_walls = 10;
//
//    memset(s.horizontal_walls, false, sizeof(s.horizontal_walls));
//    memset(s.vertical_walls, false, sizeof(s.vertical_walls));
//
//    return s;
//}
//
//// ------------------------------------------------------------
//// DRAW STATE
//// ------------------------------------------------------------
//  void drawState(const GameState& s)
//{
//    cout << "\n========================================\n";
//
//    for (int r = 0; r < 9; r++)
//    {
//        // Cells + vertical walls
//        for (int c = 0; c < 9; c++)
//        {
//            int pos = r * 9 + c;
//
//            if (pos == s.player0_pos)      cout << " 0 ";
//            else if (pos == s.player1_pos) cout << " 1 ";
//            else                           cout << " . ";
//
//            if (c < 8)
//            {
//                if (s.vertical_walls[r][c])
//                    cout << "|";
//                else
//                    cout << " ";
//            }
//        }
//        cout << "\n";
//
//        // Horizontal walls
//        if (r < 8)
//        {
//            for (int c = 0; c < 9; c++)
//            {
//                if (s.horizontal_walls[r][c])
//                    cout << "===";
//                else
//                    cout << "   ";
//
//                if (c < 8) cout << " ";
//            }
//            cout << "\n";
//        }
//    }
//
//    cout << "----------------------------------------\n";
//    cout << "BFS P0 = " << bfs(s, false)
//         << " | BFS P1 = " << bfs(s, true) << "\n";
//}
//
//// ------------------------------------------------------------
//// BASE TEST STATE (maze-like)
//// ------------------------------------------------------------
//GameState baseTestState()
//{
//    GameState s = emptyState();
//
//    // Player 0 (opponent) — looks fast
//    s.player1_pos = 4*9+5;   // (2,4)
//
//    // Player 1 (AI)
//    s.player0_pos = 7*9+8;   // (7,4)
//
//    // Walls form a deceptive corridor
//    // Horizontal funnel
////    for (int c = 1; c < 9; c++) {
////        if (c != 3&&c!=4)
////            s.horizontal_walls[0][c] = true;
////    }
//
//   s.p1_walls=0;
//
//    // Vertical side locks
////    for (int r = 1; r < 9; r++) {
////        s.vertical_walls[r][2] = true;
////
////    }
//    s.vertical_walls[5][4] = true;
//    s.vertical_walls[6][4] = true;
//
////    for (int r = 3; r < 7; r++)
////    s.vertical_walls[r][6] = true;
////
////    s.vertical_walls[6][5]=1;
////    s.vertical_walls[7][5]=1;
//
//
//    // Additional misleading walls
//    for (int r = 3; r < 7; r++)
//        s.horizontal_walls[4][r] = true;
////
////    s.horizontal_walls[6][6] = true;
////    s.horizontal_walls[6][7] = true;
////
////    s.horizontal_walls[7][7] = true;
////    s.horizontal_walls[7][8] = true;
//
//
//    return s;
//}
//
//// ------------------------------------------------------------
//// MAIN
//// ------------------------------------------------------------
//int main()
//{
//    GameState base = baseTestState();
//
//    cout << "\n===== BASE STATE =====\n";
//    drawState(base);
//
//    // --------------------------------------------------------
//    // GENERATE WALL MOVES
//    // --------------------------------------------------------
//     int t=2;
//    //PRINT VERTICAL WALL MOVES
//    // --------------------------------------------------------
////    auto desc = getAllLegalMoves(base, 1);
////
////    cout << "\n=====Descending MOVES =====\n";
////    cout << "Total: " << desc.size() << "\n";
////
////    for (size_t i = 0; i < desc.size(); i++)
////    {
////        cout << "\n--- Vertical Move #" << i << " ---\n";
////        drawState(desc[i]);
////    }
//
//
//while(t--)
//    {
//         auto aiMove = chooseBestMove(base, 2,5);
//
//
//         cout << "\n--- Ai Move #" << " ---\n";
//         drawState(aiMove);
//            base = aiMove;
//     }
//
//
//    return 0;
//}