#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

bool isGoal(string &initial, string&goal) {
    return initial == goal;
}

vector<string> getNextStates(string current) {
    vector<string> newStates;
    int zeroIndex = current.find('0');
    int curRow = zeroIndex/3, curCol = zeroIndex%3;
    vector<pair<int,int>> directions = {{-1,0},{1,0},{0,-1},{0,1}};
    for(auto dir : directions) {
        int newRow = curRow + dir.first, newCol = curCol + dir.second;
        if(newRow<3 && newRow>=0 && newCol<3 && newCol>=0) {
            int newZeroPos = newRow*3 + newCol;
            string newState = current;
            swap(newState[zeroIndex],newState[newZeroPos]);
            newStates.push_back(newState);
        }
    }
    return newStates;
}

bool dfs(string current, string goal, set<string> &visited) {
    cout<<"\nCurrent state: "<<current;
    if(isGoal(current,goal)) return 1;
    visited.insert(current);
    vector<string> nextStates = getNextStates(current);
    for(auto str : nextStates) {
        if(!visited.count(str)) {
            if(dfs(str,goal,visited)) return 1;
        }
    }
    return 0;
}

int main() {
    set<string> visited;
    cout<<"Enter the initial state: ";
    string initial, goal;
    cin>>initial;
    cout<<"\nEnter the goal state: ";
    cin>>goal;
    if(dfs(initial,goal,visited)) cout<<"\nGoal state is achievable!";
    else cout<<"Goal state not achievable!";
    return 0;
}