#include <bits/stdc++.h>
using namespace std;
static const int INF = 1e9;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int E;
    if (!(cin >> E)) return 0;
    auto addE = [&](vector<unordered_set<int>> &adj, int a, int b) {
        adj[a].insert(b);
        adj[b].insert(a);
    };
    vector<unordered_set<int>> g1(2005), g2(2005);
    int maxNode = 0, a, b;
    for(int i=0;i<E;i++){
        cin >> a >> b;
        addE(g1,a,b);
        maxNode = max(maxNode, max(a,b));
    }
    for(int i=0;i<E;i++){
        cin >> a >> b;
        addE(g2,a,b);
        maxNode = max(maxNode, max(a,b));
    }
    int N = maxNode;
    for(int i=1;i<=N;i++){
        if(!g1[i].size()) g1[i];
        if(!g2[i].size()) g2[i];
    }
    vector<int> d1(N+1), d2(N+1);
    vector<vector<int>> nd1(N+1), nd2(N+1);
    for(int i=1;i<=N;i++){
        d1[i] = g1[i].size();
        d2[i] = g2[i].size();
    }
    for(int i=1;i<=N;i++){
        for(int x : g1[i]) nd1[i].push_back(d1[x]);
        sort(nd1[i].begin(), nd1[i].end());
        for(int x : g2[i]) nd2[i].push_back(d2[x]);
        sort(nd2[i].begin(), nd2[i].end());
    }
    unordered_map<string, vector<int>> g2Buckets;
    auto keyGen = [&](int deg, const vector<int>& nbr)->string {
        string k = to_string(deg) + "#";
        for(int v : nbr) k += to_string(v) + ",";
        return k;
    };
    for(int i=1;i<=N;i++){
        g2Buckets[keyGen(d2[i], nd2[i])].push_back(i);
    }
    vector<vector<int>> cand(N+1);
    for(int i=1;i<=N;i++){
        auto k = keyGen(d1[i], nd1[i]);
        if(!g2Buckets.count(k)){
            cout << 0;
            return 0;
        }
        cand[i] = g2Buckets[k];
    }
    vector<int> order(N);
    iota(order.begin(), order.end(), 1);
    sort(order.begin(), order.end(), [&](int x, int y){
        if(cand[x].size() != cand[y].size()) return cand[x].size() < cand[y].size();
        if(d1[x] != d1[y]) return d1[x] > d1[y];
        return x < y;
    });
    vector<int> assign(N+1), used(N+1);
    set<vector<int>> isoPerms;
    function<void(int)> dfs = [&](int pos){
        if(pos == N){
            vector<int> p(N);
            for(int i=1;i<=N;i++) p[i-1] = assign[i];
            isoPerms.insert(p);
            return;
        }
        int u = order[pos];
        for(int v : cand[u]){
            if(used[v]) continue;
            bool ok = true;
            for(int w : g1[u]){
                if(assign[w] && !g2[v].count(assign[w])) { ok = false; break; }
            }
            if(!ok) continue;
            assign[u] = v;
            used[v] = 1;
            dfs(pos+1);
            used[v] = 0;
            assign[u] = 0;
        }
    };
    dfs(0);
    if(isoPerms.empty()){ cout << 0; return 0; }
    vector<int> id(N);
    iota(id.begin(), id.end(), 1);
    if(isoPerms.count(id)){ cout << 0; return 0; }
    set<vector<int>> rot;
    function<vector<int>(vector<int>&)> makePerm = [&](vector<int>& cyc){
        vector<int> p(N);
        iota(p.begin(), p.end(), 1);
        int L = cyc.size();
        for(int i=0;i<L;i++){
            int a = cyc[i], b = cyc[(i+1)%L];
            p[a-1] = b;
        }
        return p;
    };
    for(int s=1;s<=N;s++){
        stack<tuple<int,vector<int>,unordered_set<int>>> st;
        st.push({s,{s},{s}});
        while(!st.empty()){
            auto [cur, path, usedSet] = st.top(); st.pop();
            for(int nb : g1[cur]){
                if(nb == s && path.size() >= 3 && *min_element(path.begin(), path.end()) == s){
                    auto cyc = path;
                    rot.insert(makePerm(cyc));
                    reverse(cyc.begin(), cyc.end());
                    rot.insert(makePerm(cyc));
                } else if(nb > s && !usedSet.count(nb)){
                    auto np = path; np.push_back(nb);
                    auto ns = usedSet; ns.insert(nb);
                    st.push({nb, np, ns});
                }
            }
        }
    }
    if(rot.empty()){ cout << -1; return 0; }
    queue<pair<vector<int>,int>>q;
    q.push({id,0});
    set<vector<int>> vis;
    vis.insert(id);
    vector<vector<int>> rotList(rot.begin(),rot.end());
    while(!q.empty()){
        auto [cur, dist] = q.front(); q.pop();
        for(auto &r : rotList){
            vector<int> nxt(N);
            for(int i=0;i<N;i++) nxt[i] = r[cur[i]-1];
            if(vis.count(nxt)) continue;
            if(isoPerms.count(nxt)){
                cout << dist+1;
                return 0;
            }
            vis.insert(nxt);
            q.push({nxt, dist+1});
        }
    }
    cout << -1;
    return 0;
}
