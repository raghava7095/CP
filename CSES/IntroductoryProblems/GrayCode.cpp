#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin>>n;
    vector<string>grayCodes;
    for(ll i=0;i<(1<<n);i++){
        ll gray=i^(i>>1);
        string code="";
        for(ll j=n-1;j>=0;j--){
            code+=((gray&(1<<j))?'1':'0');
        }
        grayCodes.push_back(code);
    }
    for(string code:grayCodes){
        cout << code << endl;
    }
return 0;
}