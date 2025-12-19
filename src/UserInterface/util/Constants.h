//
// Created by ramez on 12/15/2025.
//

#ifndef QUORIDOR_GAME_CONSTANTS_H
#define QUORIDOR_GAME_CONSTANTS_H
#pragma once

const int PAWN_RADIUS = 20;
static constexpr int BOARD_SIZE = 9;
static constexpr int CELL_SIZE = 60;
static constexpr int WALL_THICK = 14;
constexpr int WALL_GAP  = 10;
constexpr int STEP      = CELL_SIZE + WALL_GAP;
constexpr int WALL_OFFSET = (WALL_GAP - WALL_THICK) / 2;

static constexpr int WALL_LEN = CELL_SIZE * 2 + WALL_THICK;

enum class GameMode { PvP, PvAI };
enum class Difficulty { Easy, Medium, Hard };
// enum class Turn { White, Black };
enum  class ori {Horizontal, Vertical};
enum class HoverType {
    Cell,
    VerticalEdge,
    HorizontalEdge,
    None
};
#endif //QUORIDOR_GAME_CONSTANTS_H