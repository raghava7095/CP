#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        long long x, y;
        cin >> x >> y;
        long long n = max(x, y);
        if (n & 1) { 
            if (y == n)
                cout << n * n - x + 1 << endl;
            else
                cout << (n - 1) * (n - 1) + y << endl;
        } else { 
            if (x == n)
                cout << n * n - y + 1 << endl;
            else
                cout << (n - 1) * (n - 1) + x << endl;
        }
    }
    return 0;
}
