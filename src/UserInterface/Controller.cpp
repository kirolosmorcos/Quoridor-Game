//
// Created by kiro3 on 12/18/2025.
//
#include "Controller.h"


#include <bits/stdc++.h>
using namespace std;
vector<int> getPawnLegalMoves(GameState state){
  bool turn = state.turn;
  vector<GameState> moves;
  moves=normalPawnMoves(state,turn);
  for(auto move:jumpMoves(state,turn)){
      moves.push_back(move);
  }
    vector<int> legalPositions;
  for(auto move:moves)
  {

        if(turn){
            legalPositions.push_back(move.player1_pos);
        }
        else{
            legalPositions.push_back(move.player0_pos);
        }
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