#include <iostream>
#include <vector>
using namespace std;

int heuristic(string state, string goal) {
    int h = 0;
    for(int i=0; i<9; i++) {
        if(state[i] != '0' && state[i] != goal[i])
            h++;
    }
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

void hillClimb(string start, string goal) {
    string current = start;
    int currentHeuristic = heuristic(current, goal);
    cout << "\nInitial state: " << current << "  (h=" << currentHeuristic << ")\n";
    while (true) {
        vector<string> neighbors = getNextStates(current);
        string bestNeighbor = current;
        int bestHeuristic = currentHeuristic;
        for (auto &next : neighbors) {
            int h = heuristic(next, goal);
            if (h < bestHeuristic) {
                bestHeuristic = h;
                bestNeighbor = next;
            }
        }
        if (bestHeuristic >= currentHeuristic) {
            cout << "\nNo better neighbor found. Stopping.\n";
            break;
        }
        current = bestNeighbor;
        currentHeuristic = bestHeuristic;
        cout << "Moved to: " << current << "  (h=" << currentHeuristic << ")\n";
        if (currentHeuristic == 0) {
            cout << "\nGoal state reached!\n";
            return;
        }
    }
    if (currentHeuristic != 0)
        cout << "\nGoal state not reachable by hill climbing!\n";
}

int main() {
    string initial, goal;
    cout << "Enter initial state: ";
    cin >> initial;
    cout << "\nEnter goal state: ";
    cin >> goal;

    hillClimb(initial, goal);
    return 0;
}