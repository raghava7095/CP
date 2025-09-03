#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    vector<string>res;
    function<void(int,char,char,char)>hanoi=[&](int n,char from,char to,char aux){
        if(n==1){
            res.push_back(string(1,from)+" "+string(1,to));
            return;
        }
        hanoi(n-1,from,aux,to);
        res.push_back(string(1,from)+" "+string(1,to));
        hanoi(n-1,aux,to,from);
    };
    hanoi(n,'1','3','2');
    cout << res.size() << endl;
    for(string move:res)cout << move << endl;
    return 0;
}