#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin>>n;
    ll sum=n*(n+1)/2;
    if(sum&1){
        cout << "NO" << endl;
        return 0;
    }
    sum/=2;
    vector<ll>nums;
    for(ll i=1;i<=n;i++){
        nums.push_back(i);
    }
    vector<ll>set1,set2;
    for(ll i=n-1;i>=0;i--){
        if(nums[i]<=sum){
            set1.push_back(nums[i]);
            sum-=nums[i];
        }else{
            set2.push_back(nums[i]);
        }
    }
    cout << "YES" << endl;
    cout << set1.size() << endl;
    for(auto x:set1)cout << x << " ";
    cout << endl;
    cout << set2.size() << endl;
    for(auto x:set2)cout << x << " ";
    return 0;
}