#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin>>n;
    ll tc,np;
    for(ll i=1;i<=n;i++){
       tc=(i*i)*(i*i-1)/2;
       np=4*(i-1)*(i-2);    
       cout << tc-np << endl;       
    }
    return 0;
}