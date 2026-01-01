#include <bits/stdc++.h>
using namespace std;

map<vector<string>, string> ASCII_MAP = {
    {{"   ","  |","  |"}, "1"},
    {{" _ "," _|","|_ "}, "2"},
    {{" _ "," _|"," _|"}, "3"},
    {{"   ","|_|","  |"}, "4"},
    {{" _ ","|_ "," _|"}, "5"},
    {{"   "," _ "," | "}, "+"},
    {{"   ","_|_"," | "}, "*"},
    {{"   "," _ ","   "}, "-"},
    {{"  |"," _ ","|  "}, "/"},
    {{" | ","|  "," | "}, "("},
    {{" | ","  |"," | "}, ")"},
};

map<char, vector<string>> REV;

string s;
int pos;

long long parse_expr();
long long parse_term();
long long parse_factor();

long long parse_number() {
    int sign = 1;
    if (s[pos] == '-') { sign = -1; pos++; }
    long long r = 0;
    while (pos < s.size() && isdigit(s[pos])) {
        r = r * 10 + (s[pos] - '0');
        pos++;
    }
    return sign * r;
}

long long parse_factor() {
    if (s[pos] == '(') {
        pos++;
        long long v = parse_expr();
        pos++;
        return v;
    }
    return parse_number();
}

long long parse_term() {
    long long v = parse_factor();
    while (pos < s.size() && (s[pos] == '*' || s[pos] == '/')) {
        char op = s[pos++];
        long long r = parse_factor();
        if (op == '*') v = v * r;
        else v = v / r;
    }
    return v;
}

long long parse_expr() {
    long long v = parse_term();
    while (pos < s.size() && (s[pos] == '+' || s[pos] == '-')) {
        char op = s[pos++];
        long long r = parse_term();
        if (op == '+') v = v + r;
        else v = v - r;
    }
    return v;
}

int main() {
    for (auto &p : ASCII_MAP) REV[p.second[0]] = p.first; 
    for (auto &p : ASCII_MAP) REV[p.second[0]] = p.first;
    REV.clear();
    for (auto &p : ASCII_MAP) REV[p.second[0]] = p.first;
    map<string, vector<string>> R;
    for (auto &p : ASCII_MAP) R[p.second] = p.first;

    vector<string> in(3);
    getline(cin, in[0]);
    getline(cin, in[1]);
    getline(cin, in[2]);

    int n = in[0].size() / 3;
    s = "";
    for (int i = 0; i < n; i++) {
        vector<string> b = {
            in[0].substr(i*3,3),
            in[1].substr(i*3,3),
            in[2].substr(i*3,3)
        };
        s += ASCII_MAP[b];
    }

    pos = 0;
    long long val = parse_expr();
    string out = to_string(val);

    vector<string> r(3, "");
    for (char c : out) {
        vector<string> b = R[string(1,c)];
        r[0] += b[0];
        r[1] += b[1];
        r[2] += b[2];
    }

    cout << r[0] << "\n" << r[1] << "\n" << r[2] << "\n";
}
