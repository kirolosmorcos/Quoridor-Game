

#include "Best Move.h"
#include "Alpha Beta Minimax.h"

//
// Created by kiro3 on 12/10/2025.
//

void drawState2(const GameState& s)
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


GameState  chooseBestMove(GameState state, int depth){

//difficulty level
//bestScore = -infinity
//bestMove = null
// GameState temp;
//for move in getAllLegalMoves(state, AIPlayer):
//newState = applyMove(state, move)
//score = alphaBeta(newState, depth - 1, -infinity, +infinity, false)
//if score > bestScore:
//bestScore = score
//bestMove = move

GameState bestState;
int bestScore = INT_MIN;
vector <GameState> legalMoves= getDescendingHeuristicMoves(state, true,5);

//for(GameState move : legalMoves) {
////    cout<<"heurestic--> "<<heuresticDistanceToGoalDifference(move)<<endl;
////    drawState2(move);
//    int score = AlphaBetaMinimax(move, depth - 1, INT_MIN, INT_MAX, false);
////    cout<<"Score--> " <<score<<endl;
//    if (score > bestScore) {
//        bestScore = score;
//        bestState = move;
//
//
//    }

    int alpha = INT_MIN;
    int beta = INT_MAX;
    for (const GameState& nextState : legalMoves) {
        int eval = AlphaBetaMinimax(nextState, depth - 1, alpha, beta, false);

        if (eval > bestScore) {
            bestScore = eval;
            bestState = nextState;
        }

        alpha   = std::max(alpha, eval);

        if (beta <= alpha) {
            break; //  Alpha–Beta pruning
        }
    }


return bestState;

}