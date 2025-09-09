#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin>>t;
    while(t--){
        ll n,m;
        cin>>n>>m;
        vector<ll>a(n);
        for(ll i=0;i<n;i++) cin>>a[i];
       sort(a.rbegin(), a.rend());
        vector<ll> pref(n+1,0), prefIw(n+1,0);
        for(int i=1;i<=n;i++){
            pref[i] = pref[i-1] + a[i-1];
            prefIw[i] = prefIw[i-1] + a[i-1] * i;
        }
        ll best = 0;
        int K = (int)min<ll>(n, m);
        for(int k=1;k<=K;k++){
            ll q = m / k;
            int r = (int)(m % k); 
            ll S = 0;
            if(r > 0){
                S += ( (ll)(r + 1) ) * pref[r] - prefIw[r];
            }
            if(k > r){
                S += ( (ll)(k + r + 1) ) * (pref[k] - pref[r])
                     - (prefIw[k] - prefIw[r]);
            }
            ll total = S + (ll)k * (q - 1) * pref[k] + (ll)k * pref[r];
            best = max(best, total);
        }
        cout << best << endl;
    }
    return 0;
}