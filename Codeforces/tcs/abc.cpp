#include <bits/stdc++.h>
using namespace std;
int lcs_length_rolling(const string &s, const string &t) {
    int n = (int)s.size();
    vector<int> prev(n + 1, 0), cur(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s[i-1] == t[j-1]) cur[j] = prev[j-1] + 1;
            else cur[j] = max(prev[j], cur[j-1]);
        }
        swap(prev, cur);
    }
    return prev[n];
}
string read_items_line(int n) {
    string line;
    while (true) {
        if (!std::getline(cin, line)) break;
        if (!line.empty()) break;
    }
    stringstream ss(line);
    vector<string> toks;
    string tok;
    while (ss >> tok) toks.push_back(tok);
    string s;
    if ((int)toks.size() == n) {
        for (auto &x : toks) {
            s.push_back(x[0]);
        }
    } else {
        for (char c : line) {
            if (c == ' ' || c == '\t') continue;
            s.push_back(c);
        }
        while ((int)s.size() < n) {
            string more;
            if (!getline(cin, more)) break;
            for (char c : more) {
                if (c == ' ' || c == '\t') continue;
                s.push_back(c);
            }
        }
    }
    if ((int)s.size() > n) s = s.substr(0, n);
    return s;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    string dummy;
    getline(cin, dummy);
    string s = read_items_line(n);
    if ((int)s.size() != n) {
        s.clear();
        for (int i = 0; i < n; ++i) {
            string piece;
            if (!(cin >> piece)) break;
            s.push_back(piece[0]);
        }
    }
    string fixed_line;
    if (!getline(cin, fixed_line)) fixed_line = "";
    vector<int> fixed_positions;
    if (!fixed_line.empty()) {
        stringstream ss(fixed_line);
        int x;
        while (ss >> x) fixed_positions.push_back(x);
    }
    array<int,3> cnt = {0,0,0};
    for (char c : s) {
        if (c == 'A') ++cnt[0];
        else if (c == 'B') ++cnt[1];
        else if (c == 'C') ++cnt[2];
    }
    vector<char> letters = {'A','B','C'};
    int best = INT_MAX;
    bool found = false;
    sort(letters.begin(), letters.end());
    do {
        string t;
        for (int k = 0; k < 3; ++k) {
            int size = (letters[k] == 'A') ? cnt[0] : (letters[k] == 'B' ? cnt[1] : cnt[2]);
            t.append(size, letters[k]);
        }
        if ((int)t.size() != n) continue;
        bool feasible = true;
        for (int idx : fixed_positions) {
            if (idx < 1 || idx > n) { feasible = false; break; }
            if (t[idx-1] != s[idx-1]) { feasible = false; break; }
        }
        if (!feasible) continue;
        int lcs = lcs_length_rolling(s, t);
        int moves = n - lcs;
        if (!found || moves < best) {
            best = moves;
            found = true;
        }
    } while (next_permutation(letters.begin(), letters.end()));
    if (!found) {
        cout << "Impossible\n";
    } else {
        cout << best << '\n';
    }
    return 0;
}
