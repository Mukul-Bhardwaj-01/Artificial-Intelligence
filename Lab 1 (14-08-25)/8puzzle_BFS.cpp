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

// Check if goal
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

// BFS solve (but don’t print moves)
bool solveBFS(vector<vector<int>> start) {
    queue<Node> q;
    set<vector<vector<int>>> vis;
    q.push({start,""});
    vis.insert(start);

    while(!q.empty()){
        Node cur=q.front(); q.pop();
        if(isGoal(cur.state)) return true; // found solution
        for(auto nxt: neighbors(cur)){
            if(!vis.count(nxt.state)){
                vis.insert(nxt.state);
                q.push(nxt);
            }
        }
    }
    return false;
}

int main() {
    vector<vector<int>> start = {
        {1,2,3},
        {4,0,6},
        {7,5,8}
    };

    if(!isSolvable(start)) {
        cout << "Unsolvable\n";
        return 0;
    }

    auto begin = high_resolution_clock::now();
    bool solved = solveBFS(start);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - begin);

    if(solved) cout << "Solvable (Time: " << duration.count() << " ms)\n";
    else cout << "Unsolvable\n";
}