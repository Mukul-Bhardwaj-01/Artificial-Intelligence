#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

struct Node {
    vector<vector<int>> state;
    string path;
};

vector<vector<int>> goal = {{1,2,3},{4,5,6},{7,8,0}};
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};
string dir = "UDLR";

// Find blank position
pair<int,int> findZero(vector<vector<int>> &s) {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(s[i][j]==0) return {i,j};
    return {-1,-1};
}

// Check goal
bool isGoal(vector<vector<int>> &s) { return s==goal; }

// Generate neighbors
vector<Node> neighbors(Node cur) {
    vector<Node> res;
    auto [x,y] = findZero(cur.state);
    for(int k=0;k<4;k++) {
        int nx=x+dx[k], ny=y+dy[k];
        if(nx>=0 && nx<3 && ny>=0 && ny<3) {
            Node nxt = cur;
            swap(nxt.state[x][y], nxt.state[nx][ny]);
            nxt.path += dir[k];
            res.push_back(nxt);
        }
    }
    return res;
}

// Check solvability using inversion count
bool isSolvable(vector<vector<int>> board) {
    vector<int> flat;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j]!=0) flat.push_back(board[i][j]);

    int inv=0;
    for(int i=0;i<flat.size();i++)
        for(int j=i+1;j<flat.size();j++)
            if(flat[i] > flat[j]) inv++;

    return (inv%2==0);
}

// DFS util with depth limit
bool dfsUtil(Node cur, set<vector<vector<int>>> &vis, int depth, int limit) {
    if(isGoal(cur.state)) return true;
    if(depth > limit) return false;

    vis.insert(cur.state);
    for(auto nxt: neighbors(cur)) {
        if(!vis.count(nxt.state)) {
            if(dfsUtil(nxt, vis, depth+1, limit))
                return true;
        }
    }
    return false;
}

bool solveDFS(vector<vector<int>> start, int limit=20) {
    set<vector<vector<int>>> vis;
    return dfsUtil({start,""}, vis, 0, limit);
}

int main() {
    vector<vector<int>> start = {
        {1,2,3},
        {4,5,6},
        {8,7,0}
    };

    if(!isSolvable(start)) {
        cout << "Unsolvable\n";
        return 0;
    }

    auto begin = high_resolution_clock::now();
    bool solved = solveDFS(start, 20); // depth limit = 20
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - begin);

    if(solved) cout << "Solvable (Time: " << duration.count() << " ms)\n";
    else cout << "Unsolvable (within depth limit)\n";
}