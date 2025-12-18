//
// Created by kiro3 on 12/18/2025.
//
#include "Controller.h"
#include "../AI/Best Move.h"

using namespace std;
QVector<QPoint> getPawnLegalMoves(GameState state){
  bool turn = state.turn;
  vector<GameState> moves;
  moves=normalPawnMoves(state,turn);
  for(auto move:jumpMoves(state,turn)){
      moves.push_back(move);
  }
    QVector<QPoint> legalPositions;
  for(auto move:moves)
  {
      QPoint p;
        if(turn){

           p.setX(move.player1_pos/9);
           p.setY(move.player1_pos%9);
        }
        else{

              p.setX(move.player0_pos/9);
              p.setY(move.player0_pos%9);
        }
        legalPositions.push_back(p);
  }
    return legalPositions;
}
void hoverWall(GameState state)
{
    memset(hoverHorizontal,0,sizeof(hoverHorizontal));
    memset(hoverVertical,0,sizeof(hoverVertical));

    horizontalWallMoves(state,state.turn);
    verticalWallMoves(state,state.turn);


}
GameState AIMove(GameState state){
  return chooseBestMove(state,4);
}