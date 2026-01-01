#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,x;
    cin>>n>>x;
    vector<int>a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    sort(a.begin(),a.end());
    int i=0,j=n-1,ans=0;
    while(i<=j){
        if(a[i]+a[j]<=x){
            i++;
            j--;
        }
        else{
            j--;
        }
        ans++;
    }
    cout<<ans<<endl;
    return 0;
}