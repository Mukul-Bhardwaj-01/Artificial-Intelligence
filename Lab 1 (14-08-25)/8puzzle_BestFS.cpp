#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

struct Node {
    vector<vector<int>> state;
    int cost;
};

vector<vector<int>> goal = {
    {1,2,3},
    {4,5,6},
    {7,8,0}
};

// Count inversions for solvability check
bool isSolvable(vector<vector<int>> puzzle) {
    vector<int> arr;
    for (auto &row : puzzle) {
        for (int x : row) {
            if (x != 0) arr.push_back(x);
        }
    }
    int inv = 0;
    for (int i = 0; i < arr.size(); i++) {
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[i] > arr[j]) inv++;
        }
    }
    return (inv % 2 == 0);
}

// Heuristic: misplaced tiles
int heuristic(vector<vector<int>> &s) {
    int cnt = 0;
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            if(s[i][j] && s[i][j] != goal[i][j]) cnt++;
        }
    }
    return cnt;
}

bool isGoal(vector<vector<int>> &s) {
    return s == goal;
}

// Get neighbors
vector<vector<vector<int>>> getNeighbors(vector<vector<int>> &s) {
    vector<vector<vector<int>>> res;
    int x,y;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(s[i][j]==0) { x=i; y=j; }

    int dx[4]={-1,1,0,0}, dy[4]={0,0,-1,1};
    for(int k=0;k<4;k++) {
        int nx=x+dx[k], ny=y+dy[k];
        if(nx>=0 && nx<3 && ny>=0 && ny<3) {
            auto temp = s;
            swap(temp[x][y], temp[nx][ny]);
            res.push_back(temp);
        }
    }
    return res;
}

// Best-First Search
void solveBestFirst(vector<vector<int>> start) {
    cout << "\nBest-First Search:\n";

    if (!isSolvable(start)) {
        cout << "Not Solvable\n";
        return;
    }

    auto begin = high_resolution_clock::now();

    auto cmp = [](Node a, Node b){ return a.cost > b.cost; };
    priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);
    pq.push({start, heuristic(start)});

    set<vector<vector<int>>> visited;

    while(!pq.empty()) {
        Node cur = pq.top(); pq.pop();

        if (isGoal(cur.state)) {
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - begin);
            cout << "Solved\n";
            cout << "Time taken: " << duration.count() << " ms\n";
            return;
        }

        visited.insert(cur.state);

        for(auto &next : getNeighbors(cur.state)) {
            if(visited.find(next) == visited.end()) {
                pq.push({next, heuristic(next)});
            }
        }
    }

    cout << "No solution found.\n";
}

int main() {
    vector<vector<int>> start = {
        {1,2,3},
        {4,0,6},
        {7,5,8}
    };

    solveBestFirst(start);
}