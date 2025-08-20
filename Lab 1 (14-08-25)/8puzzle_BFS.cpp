#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
using namespace std;

bool isGoal(string current, string goal) {
    return current == goal;
}

vector<string> getNextStates(const string &state) {
    vector<string> nextStates;
    int zero = state.find('0');
    int row = zero / 3, col = zero % 3;
    vector<pair<int,int>> directions = {{-1,0},{1,0},{0,-1},{0,1}};
    for (auto dir : directions) {
        int newRow = row + dir.first, newCol = col + dir.second;
        if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) {
            string newState = state;
            swap(newState[zero], newState[newRow * 3 + newCol]);
            nextStates.push_back(newState);
        }
    }
    return nextStates;
}

void bfs(string current, string goal, bool &flag) {
    queue<string> q;
    set<string> visited;
    q.push(current);
    visited.insert(current);
    while (!q.empty()) {
        string cur = q.front();
        q.pop();
        cout << cur << "\n";
        if (isGoal(cur,goal)) {
            flag = 1;
            return;
        }
        for (auto &next : getNextStates(cur)) {
            if (!visited.count(next)) {
                visited.insert(next);
                q.push(next);
            }
        }
    }
}

int main() {
    cout<<"Enter initial state: ";
    string initial, goal;
    cin>>initial;
    cout<<"\nEnter goal state: ";
    cin>>goal;
    bool flag = 0;
    bfs(initial,goal,flag);
    if(flag) cout<<"\nGoal state achievable!";
    else cout<<"Goal state not achievable!";
    return 0;
}