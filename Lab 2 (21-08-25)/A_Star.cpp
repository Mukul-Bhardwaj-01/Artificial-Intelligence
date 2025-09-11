#include <bits/stdc++.h>
using namespace std;

// State structure for each cell
struct State {
    int x, y;   // position
    int g, h;   // g = cost so far, h = heuristic
    vector<pair<int,int>> path; // path taken so far

    // Compare function for priority queue (min-heap by f)
    bool operator<(const State& other) const {
        return (g + h) > (other.g + other.h); // reversed for min-heap
    }
};

// Heuristic: Manhattan distance
int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Check validity of move
bool isValid(int x, int y, int rows, int cols, vector<vector<int>>& grid) {
    return (x >= 0 && y >= 0 && x < rows && y < cols && grid[x][y] == 0);
}

// A* algorithm using priority queue
vector<pair<int,int>> AStar(vector<vector<int>>& grid, pair<int,int> start, pair<int,int> goal) {
    int rows = grid.size(), cols = grid[0].size();

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    priority_queue<State> pq;

    // Push start state
    pq.push({start.first, start.second, 0, heuristic(start.first, start.second, goal.first, goal.second), {{start.first, start.second}}});

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        int x = current.x, y = current.y;

        if (visited[x][y]) continue;
        visited[x][y] = true;

        // Goal check
        if (x == goal.first && y == goal.second) {
            return current.path;
        }

        // Expand neighbors
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (isValid(nx, ny, rows, cols, grid) && !visited[nx][ny]) {
                int gNew = current.g + 1;
                int hNew = heuristic(nx, ny, goal.first, goal.second);
                auto newPath = current.path;
                newPath.push_back({nx, ny});
                pq.push({nx, ny, gNew, hNew, newPath});
            }
        }
    }
    return {}; // no path found
}

int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };

    pair<int,int> start = {0, 0};
    pair<int,int> goal = {4, 4};

    auto path = AStar(grid, start, goal);

    if (!path.empty()) {
        cout << "Path found:\n";
        for (auto [x,y] : path)
            cout << "(" << x << "," << y << ") ";
        cout << "\n";
    } else {
        cout << "No path exists.\n";
    }

    return 0;
}
