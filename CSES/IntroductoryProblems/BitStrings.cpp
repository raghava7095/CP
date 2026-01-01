#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int mod=1e9+7;
ll modpow(ll base,ll exp,ll modulus){
    ll result=1;
    while(exp>0){
        if(exp&1)result=(result*base)%modulus;
        base=(base*base)%modulus;
        exp>>=1;
    }
    return result;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin>>n;
    ll ans=modpow(2,n,mod);
    cout << ans << endl;
    return 0;
}