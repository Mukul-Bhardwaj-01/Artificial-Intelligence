#include <bits/stdc++.h>
using namespace std;
#define INT_MAX = 10000;
int Grid[6][7] = {
        {0,0,0,INT_MAX,0,0,0},
        {0,0,INT_MAX,0,0,0,0},
        {0,0,0,INT_MAX,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,INT_MAX,INT_MAX,0,0,0},
        {0,0,0,0,INT_MAX,0,0}
    };
void calc_cost(int cost[6][7], int end[2]) {
    for(int i=0; i<6; ++i) {
        for(int j=0; j<7; ++j) {
            cost[i][j] = sqrt()
        }
    }
}
int main() {
    int start[2] = {1,1};
    int end[2] = {5,5};
    int cost[6][7];
    calc_cost(cost, end);
}