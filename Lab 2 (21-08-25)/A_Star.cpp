#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> getNextStates(const vector<vector<int>> &grid, int m, int n, int iCur, int jCur) {
    vector<pair<int,int>> nextStates;
    //Up level
    if(iCur-1>=0) {
        if(jCur-1>=0 && grid[iCur-1][jCur-1] != 1) nextStates.push_back({iCur-1,jCur-1});
        if(grid[iCur-1][jCur] != 1) nextStates.push_back({iCur-1,jCur});
        if(jCur+1<n && grid[iCur-1][jCur+1] != 1) nextStates.push_back({iCur-1,jCur+1});
    }
    //Same level
    if(jCur-1 >= 0 && grid[iCur][jCur-1] != 1) nextStates.push_back({iCur,jCur-1});
    if(jCur+1 < n && grid[iCur][jCur+1] != 1) nextStates.push_back({iCur,jCur+1});
    //down level
    if(iCur+1 < m) {
        if(jCur-1>=0 && grid[iCur+1][jCur-1] != 1) nextStates.push_back({iCur+1,jCur-1});
        if(grid[iCur+1][jCur] != 1)nextStates.push_back({iCur+1,jCur});
        if(jCur+1<n && grid[iCur+1][jCur+1] != 1) nextStates.push_back({iCur+1,jCur+1});
    }
    return nextStates;
}

void reachGoal(vector<vector<int>> grid, int is, int js, int ig, int jg, int m, int n) {
    queue<pair<int,int>> q;
    set<pair<int,int>> visited;
    q.push({is,js});
    visited.insert({is,js});
    while(!q.empty()) {
        auto state = q.front();
        q.pop();
        cout<<"\n("<<state.first<<","<<state.second<<")";
        if(state.first == ig && state.second == jg) {
            cout<<"\nThe goal has been reached!";
            return;
        }
        for(auto nextState : getNextStates(grid, m,n,state.first,state.second)) {
            if(!visited.count(nextState)) {
                visited.insert(nextState);
                q.push(nextState);
            }
        }
    }
    cout<<"\nThe goal is not reachable!";
}

int main() {
    cout<<"Specify the grid dimensions: (Rows and columns) : ";
    int m,n,is,js,ig,jg;
    cin>>m>>n;
    vector<vector<int>> grid(m, vector<int>(n));
    cout<<"\nEnter the grid elements (0 is for free path, 1 is for obstacle) :\n";
    for(int i = 0; i<m; ++i) {
        for(int j = 0; j<n; ++j) {
            cin>>grid[i][j];
        }
        cout<<endl;
    }
    cout<<"\nThe input grid is:\n";
    for(int i = 0; i<m; ++i) {
        for(int j = 0; j<n; ++j) {
            cout<<grid[i][j]<<"  ";
        }
        cout<<endl;
    }
    cout<<"\nEnter the start location : (i,j) : ";
    cin>>is>>js;
    cout<<"\nEnter the goal location : (k,l) : ";
    cin>>ig>>jg;
    reachGoal(grid,is,js,ig,jg,m,n);
    return 0;
}