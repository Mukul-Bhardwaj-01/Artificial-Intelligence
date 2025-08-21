#include <iostream>
#include <numeric>
using namespace std;
int main() {
    int x, y, z;
    cout << "Enter capacity of jugs: ";
    cin >> x >> y;
    cout << "How much water you need: ";
    cin >> z;
    if (z > max(x, y)) {
        cout << "Not Solvable\n";
        return 0;
    }
    if (z % gcd(x, y) == 0)
        cout << "Solvable\n";
    else
        cout << "Not Solvable\n";
    return 0;
}