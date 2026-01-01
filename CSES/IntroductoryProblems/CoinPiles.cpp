#include<bits/stdc++.h>
using namespace std;
#define ll long long
void solve(){
    ll a,b;
    cin>>a>>b;
    if((a+b)%3==0 && 2*min(a,b)>=max(a,b)){
        cout << "YES" << endl; 
    }else{
        cout << "NO" << endl;
    }  
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin>>t;
    while(t--) {
        solve();
    }
    return 0;
}