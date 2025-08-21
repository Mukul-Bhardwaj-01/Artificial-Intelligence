#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

int N = 3;

// Goal state
vector<vector<int>> goal = {
    {0,1,2},
    {3,4,5},
    {6,7,8}
};

// Check solvability
bool isSolvable(vector<vector<int>> puzzle) {
    vector<int> arr;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(puzzle[i][j] != 0) arr.push_back(puzzle[i][j]);
        }
    }
    int inv = 0;
    for(int i=0;i<arr.size();i++){
        for(int j=i+1;j<arr.size();j++){
            if(arr[i] > arr[j]) inv++;
        }
    }
    return (inv%2==0);
}

// Misplaced tiles heuristic
int heuristic(vector<vector<int>> state) {
    int h=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(state[i][j] != 0 && state[i][j] != goal[i][j])
                h++;
        }
    }
    return h;
}

// Generate neighbors
vector<vector<vector<int>>> getNeighbors(vector<vector<int>> state) {
    vector<vector<vector<int>>> neighbors;
    int x,y;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(state[i][j]==0){ x=i; y=j; }

    vector<int> dx = {1,-1,0,0};
    vector<int> dy = {0,0,1,-1};
    for(int k=0;k<4;k++){
        int nx=x+dx[k], ny=y+dy[k];
        if(nx>=0 && nx<N && ny>=0 && ny<N){
            auto newState=state;
            swap(newState[x][y], newState[nx][ny]);
            neighbors.push_back(newState);
        }
    }
    return neighbors;
}

// Hill climbing search
bool hillClimbing(vector<vector<int>> start, int maxSteps=50) {
    auto cur = start;
    int curH = heuristic(cur);

    for(int step=0; step<maxSteps; step++) {
        if(curH == 0) return true; // solved

        auto neighbors = getNeighbors(cur);
        vector<vector<int>> best = cur;
        int bestH = curH;

        for(auto &next: neighbors) {
            int h = heuristic(next);
            if(h < bestH) {
                best = next;
                bestH = h;
            }
        }

        if(bestH >= curH) return false; // stuck
        cur = best;
        curH = bestH;
    }
    return (curH==0);
}

int main() {
    vector<vector<int>> start = {
        {1,2,3},
        {4,5,6},
        {7,8,0}
    };

    auto startTime = high_resolution_clock::now();

    if(!isSolvable(start)) {
        cout << "false\n";
    } else {
        bool solved = hillClimbing(start, 100);
        cout << (solved ? "true" : "false") << "\n";
    }

    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(endTime - startTime);
    cout << "Time taken: " << duration.count() << " ms\n";
    return 0;
}