#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin>>s;
    sort(s.begin(),s.end());
    vector<string>permutations;
    do{
        permutations.push_back(s);
    }while(next_permutation(s.begin(),s.end()));
    cout << permutations.size() << endl;
    for(string perm:permutations){
        cout << perm << endl;
    }
    return 0;
}