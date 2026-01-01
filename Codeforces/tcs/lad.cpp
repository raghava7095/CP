#include <bits/stdc++.h>
using namespace std;
int M, N, k;
vector<string> grid;
inline bool cell_free(int r, int c) {
    return r >= 0 && r < M && c >= 0 && c < N && grid[r][c] != 'B';
}
bool check_anchor(int r, int c, int dir) {
    if (dir == 0) {
        for (int cc = c; cc < c + k; cc++)
            if (!cell_free(r, cc)) return false;
    } else {
        for (int rr = r; rr < r + k; rr++)
            if (!cell_free(rr, c)) return false;
    }
    return true;
}
tuple<int,int,int> anchor_from_positions(vector<pair<int,int>> &pos) {
    sort(pos.begin(), pos.end());
    vector<int> rows, cols;
    for (auto &p : pos) rows.push_back(p.first), cols.push_back(p.second);

    bool sameRow = true;
    for (int r: rows) if (r != rows[0]) sameRow = false;

    if (sameRow) {
        return { rows[0], *min_element(cols.begin(), cols.end()), 0 };
    }
    return { *min_element(rows.begin(), rows.end()), cols[0], 1 };
}
string solve() {
    vector<pair<int,int>> Ipos, Lpos;
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (grid[i][j] == 'l') Ipos.push_back({i,j});
            else if (grid[i][j] == 'L') Lpos.push_back({i,j});
    if (Ipos.empty() || Lpos.empty()) return "Impossible";
    k = Ipos.size();
    auto [sr, sc, sdir] = anchor_from_positions(Ipos);
    auto [gr, gc, gdir] = anchor_from_positions(Lpos);
    if (!check_anchor(sr, sc, sdir) || !check_anchor(gr, gc, gdir))
        return "Impossible";
    vector<vector<array<bool,2>>> vis(M, vector<array<bool,2>>(N, {false,false}));
    queue<array<int,4>> q;
    q.push({sr, sc, sdir, 0});
    vis[sr][sc][sdir] = true;
    int dr[4] = {-1,1,0,0};
    int dc[4] = {0,0,-1,1};
    while (!q.empty()) {
        auto [r, c, dir, dist] = q.front(); q.pop();
        if (r == gr && c == gc && dir == gdir)
            return to_string(dist);
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            bool ok = true;
            if (dir == 0) {
                for (int cc = nc; cc < nc + k; cc++) {
                    if (!(nr >= 0 && nr < M && cc >= 0 && cc < N && grid[nr][cc] != 'B')) {
                        ok = false; break;
                    }
                }
            } else {
                for (int rr = nr; rr < nr + k; rr++) {
                    if (!(rr >= 0 && rr < M && nc >= 0 && nc < N && grid[rr][nc] != 'B')) {
                        ok = false; break;
                    }
                }
            }
            if (ok && !vis[nr][nc][dir]) {
                vis[nr][nc][dir] = true;
                q.push({nr, nc, dir, dist + 1});
            }
        }
        if (dir == 0) {
            for (int SR = r - (k - 1); SR <= r; SR++) {
                int SC = c;
                bool sq_ok = true;
                for (int rr = SR; rr < SR + k && sq_ok; rr++)
                    for (int cc = SC; cc < SC + k; cc++)
                        if (!(rr >= 0 && rr < M && cc >= 0 && cc < N && grid[rr][cc] != 'B')) {
                            sq_ok = false; break;
                        }
                if (!sq_ok) continue;
                for (int col = SC; col < SC + k; col++) {
                    int ar = SR, ac = col, ad = 1;
                    if (!vis[ar][ac][ad] && check_anchor(ar, ac, ad)) {
                        vis[ar][ac][ad] = true;
                        q.push({ar, ac, ad, dist + 1});
                    }
                }
            }
        } else {
            for (int SC = c - (k - 1); SC <= c; SC++) {
                int SR = r;
                bool sq_ok = true;
                for (int rr = SR; rr < SR + k && sq_ok; rr++)
                    for (int cc = SC; cc < SC + k; cc++)
                        if (!(rr >= 0 && rr < M && cc >= 0 && cc < N && grid[rr][cc] != 'B')) {
                            sq_ok = false; break;
                        }
                if (!sq_ok) continue;
                for (int row = SR; row < SR + k; row++) {
                    int ar = row, ac = SC, ad = 0;
                    if (!vis[ar][ac][ad] && check_anchor(ar, ac, ad)) {
                        vis[ar][ac][ad] = true;
                        q.push({ar, ac, ad, dist + 1});
                    }
                }
            }
        }
    }
    return "Impossible";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> M >> N;
    grid.resize(M);
    for (int i = 0; i < M; i++) cin >> grid[i];
    cout << solve() << "\n";
    return 0;
}
