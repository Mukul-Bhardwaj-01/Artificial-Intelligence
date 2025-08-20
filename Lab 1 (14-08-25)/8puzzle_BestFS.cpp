#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

int heuristic(string state, string goal) {
    int h = 0;
    for (int i = 0; i < 9; i++)
        if (state[i] != '0' && state[i] != goal[i])
            h++;
    return h;
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

void bestFirstSearch(string start, string goal) {
    struct Node {
        string state;
        int h;
        bool operator<(const Node &other) const {
            return h > other.h;
        }
    };
    priority_queue<Node> pq;
    set<string> visited;
    pq.push({start, heuristic(start, goal)});
    visited.insert(start);
    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();
        cout << "Visiting: " << cur.state << "  (h=" << cur.h << ")\n";
        if (cur.state == goal) {
            cout << "\nGoal state reached!\n";
            return;
        }
        for (auto &next : getNextStates(cur.state)) {
            if (!visited.count(next)) {
                visited.insert(next);
                pq.push({next, heuristic(next, goal)});
            }
        }
    }
    cout << "\nGoal state not reachable!\n";
}

int main() {
    string initial, goal;
    cout << "Enter initial state: ";
    cin >> initial;
    cout << "\nEnter goal state: ";
    cin >> goal;

    bestFirstSearch(initial, goal);
    return 0;
}