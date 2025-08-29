#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> getNextStates(int a, int b, int curA, int curB) {
    vector<pair<int,int>> nextStates;
    nextStates.push_back({a, curB});
    nextStates.push_back({curA, b});
    nextStates.push_back({0, curB});
    nextStates.push_back({curA, 0});
    int pourinB = min(curA, b - curB);
    nextStates.push_back({curA - pourinB, curB + pourinB});
    int pourinA = min(curB, a - curA);
    nextStates.push_back({curA + pourinA, curB - pourinA});
    return nextStates;
}

bool waterJug(int a, int b, int d) {
    queue<pair<int,int>> q;
    set<pair<int,int>> visited;

    q.push({0,0});
    visited.insert({0,0});

    while(!q.empty()) {
        auto pair = q.front();
        q.pop();
        if(pair.first == d || pair.second == d) return 1;
        for(auto curPair : getNextStates(a,b,pair.first,pair.second)) {
            if(!visited.count(curPair)) {
                visited.insert(curPair);
                q.push(curPair);
            }
        }
    }
    return 0;
}

int main() {
    cout<<"Enter the capactity of both jugs A and B: ";
    int a,b,d;
    cin>>a>>b;
    cout<<"Enter the amount of water needed in: ";
    cin>>d;
    if(waterJug(a,b,d)) cout<<"The quantity = "<<d<<", is achievable with the given capacities";
    else cout<<"The quantity = "<<d<<", is not achievable with the given capacities";
    return 0;
}