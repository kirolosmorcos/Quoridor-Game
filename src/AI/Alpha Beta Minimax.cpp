//
// Created by kiro3 on 12/10/2025.
//
int alphaBeta(GameState gameState, int depth, int alpha, int beta, bool maximizingPlayer){

//if depth == 0 or gameOver(state):
//return evaluateBoard(state)   // heuristic score
//
//legalMoves = getAllLegalMoves(state, currentPlayer(maximizingPlayer))
//
//if maximizingPlayer:
//maxEval = -infinity
//for move in legalMoves:
//newState = applyMove(state, move)
//eval = alphaBeta(newState, depth - 1, alpha, beta, false)
//maxEval = max(maxEval, eval)
//alpha = max(alpha, eval)
//if beta <= alpha:
//break   // prune remaining moves
//return maxEval
//else:
//minEval = +infinity
//for move in legalMoves:
//newState = applyMove(state, move)
//eval = alphaBeta(newState, depth - 1, alpha, beta, true)
//minEval = min(minEval, eval)
//beta = min(beta, eval)
//if beta <= alpha:
//break   // prune remaining moves
//return minEval
}