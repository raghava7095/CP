#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> s;
    int n = s.size();
    int ans = 1;
    int maxans = 1;
    for(int i=1;i<n;i++){
        if(s[i]==s[i-1]) ans++;
        else ans = 1;
        maxans = max(maxans,ans);
    }
    cout << maxans;
    return 0;
}