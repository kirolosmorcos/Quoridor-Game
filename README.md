# Quoridor-Game
# 🧠 Quoridor Game — AI Term Project

A full implementation of the classic abstract strategy board game **Quoridor**, developed in **C++ using Qt** as a term project for the course:

> **CSE472s – Artificial Intelligence (Fall 2025)**

This project focuses on correct game mechanics, an intuitive graphical interface, and an AI opponent with multiple difficulty levels powered by game-tree search.

---

## 📖 Game Description

**Quoridor** is a strategy board game invented by Mirko Marchesi.  
Each player controls a pawn and a limited number of walls. On each turn, a player either moves their pawn or places a wall to block the opponent — without ever fully blocking all paths to the goal.

🎯 **Objective:** Be the first player to reach any square on the opposite side of the board.

---

## 🎯 Project Goals

- Implement the complete 2-player Quoridor rules.
- Build a user-friendly GUI using Qt.
- Support Human vs Human and Human vs AI gameplay.
- Implement AI with different difficulty levels.
- Apply pathfinding to validate wall placements.
- Write clean, modular, and maintainable C++ code.

---

## ✨ Features

- ✅ Complete Quoridor rules implementation
- 🖥️ Graphical user interface using **Qt**
- 🎮 Human vs Human mode
- 🤖 Human vs AI mode
- 🧠 AI difficulty levels: **Easy, Medium, Hard**
- 🧱 Wall placement with legality highlighting on hover
- 🧭 Valid pawn move highlighting
- 🚫 Illegal move prevention
- 🔄 **Undo / Redo** functionality
- 📊 Turn indicator and wall counters
- 🏁 Winner announcement
- 🔁 New Game / Restart support

---

## 🖼️ Screenshots

> _Screenshots will be added here._

- Screenshot 1:
- Screenshot 2:
- Screenshot 3:

---

## 🎥 Demo Video

> _Demo link will be added here._

📺 **Demo Video:** 👉 _[Add demo link here]_

The video demonstrates:
- Game setup and UI overview
- Human vs Human gameplay
- Human vs AI gameplay

---

## ⚙️ Technologies Used

- **Language:** C++17
- **GUI Framework:** Qt
- **Build System:** CMake
- **Version Control:** Git & GitHub

---

## 🚀 Build & Run Instructions

### 🔧 Prerequisites

- C++17 compatible compiler
- Qt (6.10.1)
- CMake (>= 3.10)

Make sure Qt is properly installed and added to your environment.

### 🛠️ Build Steps

```bash
git clone [https://github.com/kirolosmorcos/Quoridor-Game.git](https://github.com/kirolosmorcos/Quoridor-Game.git)
cd Quoridor-Game
mkdir build
cd build
cmake ..
cmake --build .
```

# 🎮 Controls & Interaction

## 🖱️ Pawn Move
- Click on a highlighted square to move your pawn.

## 🧱 Wall Placement
- Hover between cells to preview wall placement.
- If the wall is legal, it will highlight and can be placed by clicking.
- Illegal wall placements are not highlighted.

## 🔄 Undo / Redo
- Use the **Undo** and **Redo** buttons to revert or reapply moves.

## 🆕 Restart
- Start a fresh match with same chosen settings at any time.

## 🆕 New Game
- Start a fresh match with different settings at any time.

---

# 🎲 Game Modes

## 👥 Human vs Human
- Two players play locally on the same computer.

## 🤖 Human vs AI
- Play against an AI opponent with selectable difficulty.

---

# 🤖 AI Implementation

The AI opponent is implemented using:
- **Minimax Algorithm**
- **Alpha-Beta Pruning** for optimization

### 🧮 Heuristic Evaluation Based On:
- Shortest path to goal  
- Opponent distance  
- Remaining walls  
- Blocking potential  

---

# 🎚️ Difficulty Levels

AI difficulty is controlled by:
- **Search depth**
- **Number of explored moves (branching factor)**

| Difficulty | Depth | numberOfMoves | Description                 |
|------------|--------|----------------|-----------------------------|
| Easy       | Low    | Small          | Fast, shallow search        |
| Medium     | Medium | Moderate       | Balanced strength           |
| Hard       | Higher | Larger         | Deeper, stronger AI         |

These parameters are defined in `controller.cpp`.

---

# 🧠 Game State Representation

The game model uses:
- Two boolean arrays to represent walls:
  - `horizontal[8][9]`
  - `vertical[9][8]`
- Pawn positions stored as an integers.

The board itself is **not stored explicitly**. Instead:
- Static helper functions in `GameState` (`getRow()`, `getColumn()`) map positions.

This design simplifies wall management and reduce memory used.

---

# 🧭 Pathfinding & Wall Validation

To ensure walls never completely block a player:
- Every wall placement is validated to guarantee both players still have at least one valid path to their goal.
- BFS is used to check if there is a valid path for both players.

---

# 🔄 Undo / Redo

The game supports undoing and redoing moves by storing previous game states in a stack, allowing players to:
- Revert mistaken moves.
- Explore alternative strategies.

---

# 📚 References

- Official Quoridor Rules  
- BoardGameGeek – Quoridor  
- Minimax & Alpha-Beta Pruning tutorials  
- Pathfinding algorithm resources  
- Course project description  
