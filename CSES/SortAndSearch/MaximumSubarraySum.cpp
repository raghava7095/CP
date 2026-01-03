#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n;
    cin >> n;
    vector<ll>arr(n);
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }
    ll sum = arr[0];
    ll maxsum = arr[0];
    for(int i=1;i<n;i++){
        sum = max(arr[i],sum+arr[i]);
        maxsum = max(maxsum,sum);
    }
    cout << maxsum << endl;
    return 0;
}