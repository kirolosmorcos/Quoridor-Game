
#include "Best Move.h"

//
// Created by kiro3 on 12/10/2025.
//
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
vector <GameState> legalMoves= getAllLegalMoves(state, true);
for(GameState move : legalMoves) {

    int score = alphaBeta(move, depth - 1, INT_MIN, INT_MAX, true);

    if (score > bestScore) {
        bestScore = score;
        bestState = move;
    }
}
return bestState;

}