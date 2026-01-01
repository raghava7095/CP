#include<bits/stdc++.h>
using namespace std;
#define ll long long
void appleDivision(int i,ll p2,ll p3,vector<ll>&a,ll &ans){
    if(i==a.size()){
        ans=min(ans,abs(p2-p3));
        return;
    }
    appleDivision(i+1,p2+a[i],p3,a,ans);
    appleDivision(i+1,p2,p3+a[i],a,ans);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin>>n;
    vector<ll>a(n);
    for(ll i=0;i<n;i++) cin>>a[i];
    ll ans=LLONG_MAX;
    appleDivision(0,0,0,a,ans);
    cout<<ans<<endl;
    return 0;
}                   