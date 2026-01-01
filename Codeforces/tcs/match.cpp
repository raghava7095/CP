#include <bits/stdc++.h>
using namespace std;

inline double polySignedArea(const vector<pair<double,double>> &p){
 double a=0; int n=p.size();
 for(int i=0;i<n;i++){
  auto &a1=p[i]; auto &a2=p[(i+1)%n];
  a+=a1.first*a2.second-a2.first*a1.second;
 }
 return a/2.0;
}

inline double polyArea(const vector<pair<double,double>> &p){
 return fabs(polySignedArea(p));
}

inline double minEdge(const vector<pair<double,double>> &p){
 double mn=1e18; int n=p.size();
 for(int i=0;i<n;i++){
  double dx=fabs(p[i].first-p[(i+1)%n].first);
  double dy=fabs(p[i].second-p[(i+1)%n].second);
  mn=min(mn,dx+dy);
 }
 return mn;
}
inline vector<pair<double,double>> inset(const vector<pair<double,double>> &op,double h){
 int n=op.size(); vector<pair<char,double>> ln; ln.reserve(n);
 for(int i=0;i<n;i++){
  auto &p0=op[i]; auto &p1=op[(i+1)%n];
  if(p1.first>p0.first) ln.push_back({'y',p0.second+h});
  else if(p1.first<p0.first) ln.push_back({'y',p0.second-h});
  else if(p1.second>p0.second) ln.push_back({'x',p0.first-h});
  else ln.push_back({'x',p0.first+h});
 }
 vector<pair<double,double>> ip; ip.reserve(n);
 for(int i=0;i<n;i++){
  auto &L1=ln[i]; auto &L2=ln[(i-1+n)%n];
  double X,Y;
  if(L1.first=='x'){X=L1.second; Y=L2.second;}
  else {X=L2.second; Y=L1.second;}
  ip.push_back({X,Y});
 }
 return ip;
}
void solveCase(int n, vector<pair<double,double>> pts){
 if(polySignedArea(pts)<0) reverse(pts.begin(),pts.end());
 double best=0; int t=1;
 while(true){
  if(t>250) break;
  double h=t/10.0;
  auto inP=inset(pts,h);
  if(minEdge(inP)<0.1-1e-9) break;
  double v=polyArea(inP)*h;
  best=max(best,v);
  t++;
 }
 cout<<fixed<<setprecision(2)<<best<<"\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (true) {
        int n;
        string line;
        if (!std::getline(cin, line)) break;
        if (line.empty()) break;
        n = stoi(line);
        vector<pair<double,double>> pts(n);
        for (int i = 0; i < n; i++) {
            std::getline(cin, line);
            double x, y;
            sscanf(line.c_str(), "%lf %lf", &x, &y);
            pts[i] = {x, y};
        }
        solveCase(n, pts);
 }
}
