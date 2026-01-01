#include <bits/stdc++.h>
using namespace std;

static const int MX = 25;

int n, m;
char a[MX+1][MX+1];

struct C {
    int t, x1, y1, x2, y2;
};

vector<C> cs;
string s;
int best = INT_MAX;
bool ok = false;

int mv4[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

inline bool inside(int x, int y, int X1, int Y1, int X2, int Y2){
    return (x >= X1 && x <= X2 && y >= Y1 && y <= Y2);
}

void dfs(int x, int y, int k, vector<vector<int>> &vis, vector<pair<int,int>> &pos){
    if (a[x][y] != s[k]) return;
    vis[x][y] = 1;
    pos[k] = {x, y};

    if (k + 1 == (int)s.size()) {
        ok = true;
        int bad = 0;
        for (auto &c : cs) {
            auto p = pos[c.t - 1];
            if (inside(p.first, p.second, c.x1, c.y1, c.x2, c.y2)) bad++;
        }
        best = min(best, bad);
        vis[x][y] = 0;
        return;
    }

    for (auto &d : mv4) {
        int nx = x + d[0], ny = y + d[1];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && !vis[nx][ny]) {
            dfs(nx, ny, k + 1, vis, pos);
        }
    }

    vis[x][y] = 0;
}

void solve(){
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];

    int q;
    cin >> q;
    cs.clear();
    cs.reserve(q);

    for (int i = 0; i < q; i++) {
        C tmp;
        cin >> tmp.t >> tmp.x1 >> tmp.y1 >> tmp.x2 >> tmp.y2;
        cs.push_back(tmp);
    }

    cin >> s;

    vector<pair<int,int>> pos(s.size());
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            if (a[i][j] == s[0]) {
                vector<vector<int>> vis(n+1, vector<int>(m+1, 0));
                dfs(i, j, 0, vis, pos);
            }
        }
    }

    if (!ok) {
        cout << "Impossible";
    } else if (best == 0) {
        cout << "All clues are correct";
    } else {
        cout << best;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
