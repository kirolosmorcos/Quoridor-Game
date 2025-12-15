#include "../Models/GameState.h"
/**
 * Alpha-Beta Minimax evaluation function for Quoridor AI.
 *
 * This function evaluates a given GameState by simulating future moves
 * using the Minimax algorithm enhanced with Alpha-Beta pruning.
 * It recursively explores possible pawn moves and wall placements up to
 * a fixed depth and returns a heuristic score representing how favorable
 * the position is for the AI player.
 *
 * Parameters:
 *  - gameState: A copy of the current game state used for safe simulation.
 *  - depth: Remaining search depth that limits how many future turns
 *           are explored.
 *  - alpha: The best (maximum) score guaranteed so far for the
 *           maximizing player.
 *  - beta: The best (minimum) score guaranteed so far for the
 *          minimizing player.
 *  - maximizingPlayer: Indicates whose turn it is in the minimax tree.
 *          true  -> AI (maximizing player)
 *          false -> Opponent (minimizing player)
 *
 * Return Value:
 *  - An integer heuristic score:
 *        > 0  : favorable position for the AI
 *        < 0  : favorable position for the opponent
 *        = 0  : neutral position
 *
 * Notes:
 *  - Uses Alpha-Beta pruning to skip branches that cannot affect the
 *    final decision, improving performance.
 *  - Terminates when the search depth reaches zero or when the game
 *    reaches a terminal state.
 *  - This function evaluates positions only and does not select a move.
 */
#include "alph_beta_minimax.h"

#include <limits> 

static const int INF = std::numeric_limits<int>::max();

int alphaBeta(GameState gameState,int depth,int alpha,int beta,bool maximizingPlayer){
    // 1. Terminal condition
    if (depth == 0 || gameState.isGameOver()) {
        return gameState.evaluateBoard();
    }

    // 2. Generate legal moves
    std::vector<Move> legalMoves = gameState.getAllLegalMoves(maximizingPlayer);

    // 3. Maximizing player
    if (maximizingPlayer) {
        int maxEval = -INF;

        for (const Move& move : legalMoves) {
            GameState newState = gameState;
            newState.applyMove(move);
          
            int eval = alphaBeta(newState, depth - 1,alpha,beta,false);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);

            if (beta <= alpha)  break; // Alpha–Beta pruning
             }
        return maxEval;
    }

    // 4. Minimizing player
    else {
        int minEval = INF;
        for (const Move& move : legalMoves) {
            GameState newState = gameState;
            newState.applyMove(move);

            int eval = alphaBeta(newState,depth - 1,alpha, beta,true);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);

            if (beta <= alpha)  break; // Alpha–Beta pruning
            }
        return minEval;
    }
}  
