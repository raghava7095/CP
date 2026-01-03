#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,x;
    cin >> n >> x;
    vector<int>arr(n);
    vector<pair<int,int>>original(n);
    for(int i=0;i<n;i++){
        cin >> arr[i];
        original[i]={arr[i],i};
    }
    sort(original.begin(),original.end());
    int left=0,right=n-1;
    while(left<right){
        int sum=original[left].first+original[right].first;
        if(sum==x){
            cout << original[right].second+1 << " " << original[left].second+1 << "\n";
            return 0;
        }
        else if(sum<x){
            left++;
        }
        else{
            right--;
        }
    }
    cout << "IMPOSSIBLE\n";
    return 0;
}