#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> m(n);
    for (int i = 0; i < n; i++) m[i] = a[i].size();

    vector<vector<int>> id(n);
    int tot = 0;

    for (int r = 0; r < n; r++) {
        id[r].assign(m[r], -1);
        for (int i = 0; i < m[r]; i++)
            if (a[r][i] == '0') id[r][i] = tot++;
    }

    int c = tot++;
    vector<vector<int>> g(tot);

    for (int r = 0; r < n; r++) {
        for (int i = 0; i < m[r]; i++) {
            int u = id[r][i];
            if (u < 0) continue;

            int l = (i == 0 ? m[r] - 1 : i - 1);
            int rt = (i + 1 == m[r] ? 0 : i + 1);

            if (id[r][l] >= 0) g[u].push_back(id[r][l]);
            if (id[r][rt] >= 0) g[u].push_back(id[r][rt]);
        }
    }

    for (int r = 0; r + 1 < n; r++) {
        for (int i = 0; i < m[r + 1]; i++) {
            int u = id[r + 1][i];
            if (u < 0) continue;
            int j = i >> 1;
            if (j < m[r] && id[r][j] >= 0) {
                int v = id[r][j];
                g[u].push_back(v);
                g[v].push_back(u);
            }
        }
    }

    for (int i = 0; i < m[0]; i++) {
        int u = id[0][i];
        if (u >= 0) {
            g[u].push_back(c);
            g[c].push_back(u);
        }
    }

    vector<int> d(tot, -1);
    queue<int> q;

    int R = n - 1;
    for (int i = 0; i < m[R]; i++) {
        int u = id[R][i];
        if (u >= 0) {
            d[u] = 0;
            q.push(u);
        }
    }

    if (q.empty()) {
        cout << -1;
        return 0;
    }

    while (!q.empty()) {
        int u = q.front(); 
        q.pop();

        if (u == c) {
            cout << d[u] << "\n";
            return 0;
        }

        for (int v : g[u]) {
            if (d[v] < 0) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }

    cout << -1;
    return 0;
}
