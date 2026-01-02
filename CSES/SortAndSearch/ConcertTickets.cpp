#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n , m;
    cin >> n >> m;
    multiset<int> ticketSet;
    vector<int>tickets(n);
    for(int i=0;i<n;i++){
        cin >> tickets[i];
        ticketSet.insert(tickets[i]);
    }
    vector<int>customers(m);
    for(int i=0;i<m;i++){
        cin >> customers[i];
    }
    sort(tickets.begin(), tickets.end());
    for(int i=0;i<m;i++){
        int desired = customers[i];
        auto it = ticketSet.upper_bound(desired);
        if(it == ticketSet.begin()){
            cout << -1 << "\n";
        } else {
            --it;
            cout << *it << "\n";
            ticketSet.erase(it);
        }
    }
    return 0;
}