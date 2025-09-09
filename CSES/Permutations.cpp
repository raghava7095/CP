#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    if(n==1) {cout<<1; return 0;}
    if(n<=3) {cout<<"NO SOLUTION"; return 0;}
    if(n==4) {cout<<"2 4 1 3"; return 0;}
    for(int i=n;i>=1;i-=2) cout<<i<<" "; 
    for(int i=n-1;i>=1;i-=2) cout<<i<<" ";
    return 0;
}