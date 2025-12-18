#include "Alpha Beta Minimax.h"
#include "../Models/GameState.h"
#include "../Game Logic/Legal Moves.h"
#include <limits>
#include <vector>
#include <algorithm>

static const int INF = std::numeric_limits<int>::max();

/**
 * Alpha-Beta Minimax evaluation function using heuristic move ordering.
 *
 * Purpose:
 * Implements the Alpha-Beta Pruning Minimax algorithm to evaluate a game tree.
 * Used for AI decision-making in turn-based games.
 *
 * Parameters:
 * - GameState gameState: The current state of the game.
 * - int depth: Maximum search depth. Stops recursion when 0.
 * - int alpha: Best value that the maximizer can guarantee.
 * - int beta: Best value that the minimizer can guarantee.
 * - bool maximizingPlayer: true if it's the AI's turn (maximizing), false if opponent's turn (minimizing).
 *
 * How It Works:
 * 1. Terminal Condition:
 *    - Stops recursion if depth == 0 or game is over.
 *    - Evaluates the board using gameState.evaluateBoard().
 *
 * 2. Generate Successor States:
 *    - Uses heuristic move ordering to increase pruning efficiency.
 *    - Limits number of moves considered (NUMBER_OF_MOVES) to control branching factor.
 *    - getDescendingHeuristicMoves() for maximizing player (AI) → best moves first.
 *    - getAscendingHeuristicMoves() for minimizing player (opponent) → worst moves first.
 *
 * 3. Maximizing Player:
 *    - Iterates through possible moves and recursively evaluates them.
 *    - Updates alpha and prunes branches where beta <= alpha.
 *
 * 4. Minimizing Player:
 *    - Similar to maximizing, but updates beta and prunes where beta <= alpha.
 *
 * Return Value:
 * - Returns the evaluation score of the best move found considering depth and pruning.
 *
 * Benefits:
 * - Reduces number of nodes evaluated compared to plain minimax.
 * - Heuristic move ordering further improves efficiency.
 */
int AlphaBetaMinimax(GameState gameState, int depth, int alpha, int beta, bool maximizingPlayer)
{
    // 1. Terminal condition
    if (depth == 0 || gameState.isGameOver()) {
        return evaluateBoard(gameState);
    }

    // 2. Generate heuristic-ordered successor states
    // Limit number of moves to control branching factor
    const int NUMBER_OF_MOVES = 3;  // change this to be more difficult ai
    
    /*
        enum AIDifficulty {
    EASY,
    MEDIUM,
    HARD,
    EXPERT
};
struct AIConfig {
    int depth;
    int numberOfMoves;
};

AIConfig getAIConfig(AIDifficulty difficulty) {
    switch (difficulty) {
        case EASY:   return {2, 5};
        case MEDIUM: return {3, 10};
        case HARD:   return {4, 15};
        case EXPERT: return {5, INT_MAX}; // all moves
    }
    return {3, 10};
}
example of changes in the code 

AIConfig config = getAIConfig(MEDIUM);

int score = alphaBeta( currentState,config.depth, -INF, INF,true);

nextStates = getDescendingHeuristicMoves( gameState, maximizingPlayer, config.numberOfMoves);

*/
    std::vector<GameState> nextStates;

    if (maximizingPlayer) {
        // Best moves first → increase alpha faster
        nextStates = getDescendingHeuristicMoves( gameState, maximizingPlayer, NUMBER_OF_MOVES );
    }
    else {
        // Worst moves first → decrease beta faster
        nextStates = getAscendingHeuristicMoves(gameState, maximizingPlayer, NUMBER_OF_MOVES );
    }

    // 3. Maximizing player (AI)
    if (maximizingPlayer) {
        int maxEval = -INF;

        for (const GameState& nextState : nextStates) {
            int eval = AlphaBetaMinimax(nextState, depth - 1, alpha, beta, false);

            maxEval = std::max(maxEval, eval);
            alpha   = std::max(alpha, eval);

            if (beta <= alpha) {
                break; //  Alpha–Beta pruning
            }
        }
        return maxEval;
    }

    // 4. Minimizing player (Opponent)
    else {
        int minEval = INF;

        for (const GameState& nextState : nextStates) {
            int eval = AlphaBetaMinimax(nextState, depth - 1, alpha, beta, true);

            minEval = std::min(minEval, eval);
            beta    = std::min(beta, eval);

            if (beta <= alpha) {
                break; // Alpha–Beta pruning
            }
        }
        return minEval;
    }
}
