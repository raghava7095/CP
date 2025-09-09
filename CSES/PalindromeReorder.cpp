#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin>>s;
    vector<ll>freq(26,0);
    for(char c:s){
        freq[c-'A']++;
    }
    ll oddCount=0;
    for(ll count:freq){
        if(count%2)oddCount++;
    }
    if(oddCount>1){
        cout << "NO SOLUTION" << endl;
        return 0;
    }
    string firstHalf="",middle="";
    for(ll i=0;i<26;i++){
        if(freq[i]%2){
            middle=string(freq[i],char('A'+i));
        }
        else{firstHalf+=string(freq[i]/2,char('A'+i));}
    }
    string secondHalf=firstHalf;
    reverse(secondHalf.begin(),secondHalf.end());
    cout << firstHalf+middle+secondHalf << endl;
    return 0;
}