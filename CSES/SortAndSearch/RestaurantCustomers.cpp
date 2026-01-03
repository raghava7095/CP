#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<pair<int,int>>customers(n);
    vector<pair<int,int>>arr(2*n);
    for(int i=0;i<n;i++){
        cin >> customers[i].first >> customers[i].second;
        arr[2*i]={customers[i].first,1};
        arr[2*i+1]={customers[i].second,-1};
    }
    sort(arr.begin(),arr.end());
    int curr=0,ans=0;
    for(int i=0;i<2*n;i++){
        curr+=arr[i].second;
        ans=max(ans,curr);
    }
    cout << ans << "\n";
    return 0;
}