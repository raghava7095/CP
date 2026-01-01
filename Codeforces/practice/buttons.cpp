#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    int clicks = 0;
    while (m > n) {
        if (m % 2 == 0) {
            m /= 2;
        } else {
            m += 1;
        }
        clicks++;
    }
    clicks += (n - m);
    cout << clicks << endl;
    return 0;
}
