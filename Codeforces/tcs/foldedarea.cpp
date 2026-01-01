#include <bits/stdc++.h>
using namespace std;

static const double EPS = 1e-9;

struct PT {
    double x, y;
    PT() : x(0), y(0) {}
    PT(double a, double b) : x(a), y(b) {}
};

PT operator+(PT a, PT b){ return PT(a.x + b.x, a.y + b.y); }
PT operator-(PT a, PT b){ return PT(a.x - b.x, a.y - b.y); }
PT operator*(PT a, double t){ return PT(a.x * t, a.y * t); }

double cr(PT a, PT b){ return a.x*b.y - a.y*b.x; }
double dt(PT a, PT b){ return a.x*b.x + a.y*b.y; }

bool on_seg(const PT& p, const PT& a, const PT& b){
    PT ap=p-a, ab=b-a;
    if(fabs(cr(ap,ab)) > 1e-7) return false;
    double d = dt(ap,ab);
    if(d < -1e-7) return false;
    if(d - dt(ab,ab) > 1e-7) return false;
    return true;
}

vector<PT> cut_half(const vector<PT>& poly, PT A, PT B, bool keepLeft){
    vector<PT> nv;
    if(poly.empty()) return nv;
    int n = poly.size();

    for(int i=0;i<n;i++){
        PT P = poly[i], Q = poly[(i+1)%n];
        double c1 = cr(B-A, P-A);
        double c2 = cr(B-A, Q-A);

        bool s1 = keepLeft ? (c1 > EPS) : (c1 < EPS || fabs(c1) <= EPS);
        bool s2 = keepLeft ? (c2 > EPS) : (c2 < EPS || fabs(c2) <= EPS);

        if(s1) nv.push_back(P);

        if(s1 != s2){
            PT d = Q-P, axis = B-A;
            double denom = cr(d,axis);
            if(fabs(denom) < EPS) continue;
            double t = cr(A-P, axis) / denom;
            nv.push_back(P + d*t);
        }
    }

    vector<PT> out;
    for(auto &p : nv){
        if(out.empty() ||
           fabs(out.back().x - p.x) > 1e-7 ||
           fabs(out.back().y - p.y) > 1e-7)
            out.push_back(p);
    }

    if(out.size() > 1){
        if(fabs(out.front().x - out.back().x) < 1e-7 &&
           fabs(out.front().y - out.back().y) < 1e-7)
            out.pop_back();
    }
    return out;
}

PT reflect_point(PT p, PT A, PT B){
    PT AB = B-A;
    double L2 = dt(AB,AB);
    if(L2 < EPS) return p;
    double t = dt(p-A, AB) / L2;
    PT proj = A + AB*t;
    return proj*2.0 - p;
}

vector<PT> seg_inter(PT A, PT B, PT C, PT D){
    vector<PT> r;
    PT u = B-A, v = D-C;
    double Dn = cr(u,v);
    if(fabs(Dn) < EPS) return r;
    PT w = C-A;
    double t = cr(w, v) / Dn;
    double s = cr(w, u) / Dn;
    if(t > -EPS && t < 1+EPS && s > -EPS && s < 1+EPS)
        r.push_back(A + u*t);
    return r;
}

bool inside(const PT &p, const vector<PT> &poly){
    if(poly.empty()) return false;
    int n = poly.size();

    for(int i=0;i<n;i++){
        if(on_seg(p, poly[i], poly[(i+1)%n])) return true;
    }

    bool f = false;
    for(int i=0;i<n;i++){
        PT a = poly[i], b = poly[(i+1)%n];
        if((a.y > p.y) != (b.y > p.y)){
            double xint = a.x + (p.y - a.y) * (b.x-a.x) / (b.y-a.y);
            if(xint > p.x) f = !f;
        }
    }
    return f;
}

void solve(){
    double A;  
    if(!(cin >> A)) return;

    double x1,y1,x2,y2;
    cin >> x1 >> y1 >> x2 >> y2;

    double L = sqrt(A);
    vector<PT> sq = { PT(0,0), PT(L,0), PT(L,L), PT(0,L) };

    PT P1(x1,y1), P2(x2,y2);

    vector<PT> rightHalf = cut_half(sq, P1, P2, false);
    vector<PT> leftHalf  = cut_half(sq, P1, P2, true);

    vector<PT> refl;
    for(auto &p: leftHalf) refl.push_back(reflect_point(p,P1,P2));

    vector<PT> crit;

    auto add = [&](PT p){
        for(auto &q: crit)
            if(fabs(p.x-q.x)<1e-9 && fabs(p.y-q.y)<1e-9) return;
        crit.push_back(p);
    };

    for(auto &p: rightHalf) add(p);
    for(auto &p: refl) add(p);

    if(!rightHalf.empty() && !refl.empty()){
        int n1 = rightHalf.size(), n2 = refl.size();
        for(int i=0;i<n1;i++){
            PT a = rightHalf[i], b = rightHalf[(i+1)%n1];
            for(int j=0;j<n2;j++){
                PT c = refl[j], d = refl[(j+1)%n2];
                auto v = seg_inter(a,b,c,d);
                for(auto &p:v) add(p);
            }
        }
    }

    auto add_on_edges = [&](const vector<PT>& A,const vector<PT>& B){
        for(auto &p:A){
            for(int i=0;i<(int)B.size();i++){
                if(on_seg(p,B[i],B[(i+1)%B.size()])){
                    add(p);
                    break;
                }
            }
        }
    };

    add_on_edges(rightHalf, refl);
    add_on_edges(refl, rightHalf);

    set<pair<long long,long long>> finalSet;

    auto process = [&](const vector<PT>& P,const vector<PT>& Q){
        if(P.empty()) return;
        int n = P.size();
        for(int i=0;i<n;i++){
            PT a = P[i], b = P[(i+1)%n];
            PT d = b-a;
            if(dt(d,d) < EPS) continue;

            vector<double> ts = {0.0, 1.0};
            for(auto &p: crit){
                if(on_seg(p,a,b)){
                    double t;
                    if(fabs(d.x) > fabs(d.y)){
                        if(fabs(d.x) < EPS) continue;
                        t = (p.x-a.x)/d.x;
                    } else {
                        if(fabs(d.y) < EPS) continue;
                        t = (p.y-a.y)/d.y;
                    }
                    if(t >= -1e-9 && t <= 1+1e-9)
                        ts.push_back(max(0.0, min(1.0, t)));
                }
            }

            sort(ts.begin(), ts.end());
            ts.erase(unique(ts.begin(), ts.end(), [](double a, double b){
                return fabs(a-b) < 1e-9;
            }), ts.end());

            for(int k=0;k+1<(int)ts.size();k++){
                double t1 = ts[k], t2 = ts[k+1];
                if(t2 - t1 < 1e-12) continue;

                PT p1 = a + d*t1;
                PT p2 = a + d*t2;
                PT mid( (p1.x+p2.x)/2.0, (p1.y+p2.y)/2.0 );

                bool inP = inside(mid,P);
                bool inQ = inside(mid,Q);

                if(inP ^ inQ){
                    auto put = [&](PT u){
                        long long X = llround(u.x*100.0);
                        long long Y = llround(u.y*100.0);
                        finalSet.insert({X,Y});
                    };
                    put(p1);
                    put(p2);
                }
            }
        }
    };

    process(rightHalf, refl);
    process(refl, rightHalf);

    vector<pair<double,double>> out;
    for(auto &p: finalSet)
        out.push_back({p.first/100.0, p.second/100.0});

    sort(out.begin(), out.end(), [](auto &a, auto &b){
        if(fabs(a.first-b.first) > 1e-8) return a.first < b.first;
        return a.second < b.second - 1e-8;
    });

    cout<<fixed<<setprecision(2);
    for(auto &p: out) cout<<p.first<<" "<<p.second<<"\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}
