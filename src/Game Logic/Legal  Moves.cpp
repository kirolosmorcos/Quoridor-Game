//
// Created by kiro3 on 12/10/2025.
//

#include "../Models/GameState.h"
#include <bits/stdc++.h>

using namespace std;
vector<GameState>  normalPawnMoves(GameState gamestate)
{
    // Implement the logic to calculate normal pawn moves up,right ,left, down
    /*  if nextCell is outside the board:
      continue

      if wall exists between pawnPosition and nextCell:
      continue

      if nextCell == opponentPosition:
      continue*/

}

vector<GameState> jumpMoves(GameState gamestate){
//moves = empty list
//
//if opponent is adjacent to myPawn:
//direction = directionFrom(myPawn to opponentPawn)
//jumpCell = cellBehind(opponentPawn, direction)
//
//if jumpCell exists AND no wall between opponentPawn and jumpCell:
//add jumpCell to moves
//else:
//for diagonal in diagonalCellsAround(opponentPawn):
//if diagonal exists AND no wall blocks diagonal:
//add diagonal to moves

}
vector<GameState> horizontalWallMoves(GameState gamestate){
//moves = empty list
//
//if wallsRemaining == 0:
//return moves
//
//for each horizontal slot on board: inside the board

//if slot is occupied:
//continue
//if slot crosses vertical wall:
//continue
//
//temporarily place wall at slot
//
//if player1 has path AND player2 has path:
//add slot to moves//bfs
//
//remove temporary wall
}
vector<GameState> verticalWallMoves(GameState gamestate){}