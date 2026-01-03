#include<bits/stdc++.h>
using namespace std;
static bool cmp(const vector<int>&a,const vector<int>&b){
    return a[1]<b[1];
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<vector<int>>movies(n,vector<int>(2));
    for(int i=0;i<n;i++){
        cin >> movies[i][0] >> movies[i][1];
    }
    sort(movies.begin(),movies.end(),cmp);
    int ans=0;
    int last_end=-1;
    for(int i=0;i<n;i++){
        if(movies[i][0]>=last_end){
            ans++;
            last_end=movies[i][1];
        }
    }
    cout << ans << "\n";
    return 0;
}