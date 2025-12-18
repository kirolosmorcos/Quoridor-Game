#include "BFS.h"

int bfs(GameState startState, bool player)
{
    bool visited[81] = {false};

    queue<pair<GameState, int>> q;

    int startPos = player ? startState.player1_pos
                          : startState.player0_pos;

    q.push({startState, 0});
    visited[startPos] = true;

    while (!q.empty())
    {
        auto [curState, dist] = q.front();
        q.pop();

        int curPos = player ? curState.player1_pos
                            : curState.player0_pos;

        int row = curPos / 9;

        //  Goal check
        if (!player && row == 8) return dist;
        if (player && row == 0) return dist;

        // Generate legal moves
        vector<GameState> nextMoves;

        auto normal = normalPawnMoves(curState, player);
        auto jumps  = jumpMoves(curState, player);

        nextMoves.insert(nextMoves.end(), normal.begin(), normal.end());
        nextMoves.insert(nextMoves.end(), jumps.begin(), jumps.end());

        // 🔹 BFS expansion
        for (auto& nextState : nextMoves)
        {
            int nextPos = player ? nextState.player1_pos
                                 : nextState.player0_pos;

            if (!visited[nextPos])
            {
                visited[nextPos] = true;
                q.push({nextState, dist + 1});
            }
        }
    }

    return -1; // no path
}
