#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Pt {
    int x, y;
    Pt(int a=0,int b=0):x(a),y(b){}
    bool operator==(const Pt& o) const { return x==o.x && y==o.y; }
    bool operator<(const Pt& o) const { return x!=o.x ? x<o.x : y<o.y; }
};

struct Seg {
    Pt a, b;      // endpoints
    Pt cen;       // rotation center (midpoint for single, intersection for cross)
    Pt mid;       // midpoint (for single)
    int idx=-1;
    int mate=-1;  // mate index if cross (or -1)
    bool cross=false; // is part of cross
    // hit() checks whether point p lies on the segment and, for crosses, on upper side
    bool hit(const Pt& p) const {
        if (p.x < min(a.x,b.x) || p.x > max(a.x,b.x)) return false;
        if (p.y < min(a.y,b.y) || p.y > max(a.y,b.y)) return false;
        // collinearity: (b-a) x (p-a) == 0
        ll dx1 = (ll)b.x - a.x, dy1 = (ll)b.y - a.y;
        ll dx2 = (ll)p.x - a.x, dy2 = (ll)p.y - a.y;
        if (dx1*dy2 != dx2*dy1) return false;
        // For cross-shaped bars we ensure we only accept the "upper" side (as problem statement)
        if (cross) {
            // ball must land on the part above the center (y >= cen.y). 
            // In original code logic you excluded p.y < cen.y; keep same but explicit.
            if (p.y < cen.y) return false;
        }
        return true;
    }
};

// rotate point p around center c by +90 degrees (CW) or -90 (CCW). integer arithmetic.
Pt rotCW(const Pt& p, const Pt& c){
    // CW: (x',y') = (cx + (py-cy), cy - (px-cx))
    return Pt(c.x + (p.y - c.y), c.y - (p.x - c.x));
}
Pt rotCCW(const Pt& p, const Pt& c){
    // CCW: (x',y') = (cx - (py-cy), cy + (px-cx))
    return Pt(c.x - (p.y - c.y), c.y + (p.x - c.x));
}

// check whether point r is on segment p-q (inclusive) using integer cross product and bbox
bool on_segment_exact(const Pt &p, const Pt &q, const Pt &r) {
    ll cross = (ll)(q.x - p.x) * (r.y - p.y) - (ll)(q.y - p.y) * (r.x - p.x);
    if (cross != 0) return false;
    if (r.x < min(p.x,q.x) || r.x > max(p.x,q.x)) return false;
    if (r.y < min(p.y,q.y) || r.y > max(p.y,q.y)) return false;
    return true;
}

// compute intersection of two infinite lines p1-p2 and p3-p4, return (valid, point)
pair<bool,Pt> intersection_point(const Pt &p1, const Pt &p2, const Pt &p3, const Pt &p4) {
    // Lines have integer coefficients. Compute intersection using determinant.
    // Avoid floating point: use integer arithmetic and ensure intersection is integer.
    // Solve: (x,y) satisfying both line eqns.
    // Using 2x2 linear solve:
    ll A1 = p2.y - p1.y;
    ll B1 = p1.x - p2.x;
    ll C1 = A1 * (ll)p1.x + B1 * (ll)p1.y; // note: using Ax + By = C form

    ll A2 = p4.y - p3.y;
    ll B2 = p3.x - p4.x;
    ll C2 = A2 * (ll)p3.x + B2 * (ll)p3.y;

    ll det = A1 * B2 - A2 * B1;
    if (det == 0) return {false, Pt(-1,-1)}; // parallel (shouldn't happen often; slopes ±1)
    // Use Cramer's rule: x = (C1*B2 - C2*B1)/det ; y = (A1*C2 - A2*C1)/det
    ll numx = C1 * B2 - C2 * B1;
    ll numy = A1 * C2 - A2 * C1;
    // need integer intersection:
    if (numx % det != 0 || numy % det != 0) return {false, Pt(-1,-1)};
    int ix = (int)(numx / det);
    int iy = (int)(numy / det);
    Pt ip(ix, iy);
    // now check it's on both segments
    if (on_segment_exact(p1,p2,ip) && on_segment_exact(p3,p4,ip)) return {true, ip};
    return {false, Pt(-1,-1)};
}

int n;
Pt startPos;
vector<Seg> initS;
set<int> outX;
map<pair<int,long long>, set<int>> memo; // memo[(endpointIdx, mask)] -> set of ground x

// DFS explore from current point cur. s = current configuration of segments (by value).
void go(const Pt &cur, vector<Seg> &s, long long mask) {
    // Check whether cur is exactly at an endpoint of some segment in this current config
    int eid = -1;
    for (int i = 0; i < n; ++i) {
        if (cur == s[i].a || cur == s[i].b) { eid = i; break; }
    }

    // If we are exactly at an endpoint, and we have memo, reuse
    if (eid != -1) {
        auto key = make_pair(eid, mask);
        auto it = memo.find(key);
        if (it != memo.end()) {
            for (int x : it->second) outX.insert(x);
            return;
        }
        // initialize memo entry now so deeper recursion can fill (prevents cycles)
        memo[key] = {};
    }

    // find the nearest segment strictly below current point at same x
    int hitIdx = -1;
    int bestDy = INT_MAX; // choose minimal vertical distance
    Pt hitPt(cur.x, -1);

    for (int i = 0; i < n; ++i) {
        const Seg &g = s[i];
        int xl = min(g.a.x, g.b.x), xr = max(g.a.x, g.b.x);
        if (cur.x < xl || cur.x > xr) continue;
        // segment slope is ±1 so compute y at cur.x via line equation
        // line: y = m*x + c where m = (b.y - a.y)/(b.x - a.x)
        int dx = g.b.x - g.a.x;
        int dy = g.b.y - g.a.y;
        // dx!=0 because bars are 45deg by statement
        int m = dy / dx; // ±1
        int c = g.a.y - m * g.a.x;
        int yy = m * cur.x + c;
        if (yy >= cur.y) continue; // strictly below
        Pt p(cur.x, yy);
        if (!g.hit(p)) continue; // not the right part (esp for cross)
        int dyv = cur.y - yy;
        if (dyv < bestDy) {
            bestDy = dyv;
            hitIdx = i;
            hitPt = p;
        }
    }

    if (hitIdx == -1) {
        // No bar below: ball reaches ground at x = cur.x
        if (eid != -1) {
            memo[{eid, mask}].insert(cur.x);
        }
        outX.insert(cur.x);
        return;
    }

    // Otherwise ball landed on segment hitIdx at hitPt.
    const Seg &g = s[hitIdx];

    // Without tilting (or as part of exploring), the ball may slide to either endpoint:
    // we recursively explore landing at both endpoints (simulate sliding to both).
    go(g.a, s, mask);
    go(g.b, s, mask);

    // If this bar has not yet been tilted, try tilting it cw and ccw
    if (((mask >> hitIdx) & 1LL) == 0) {
        auto tryTilt = [&](bool cw){
            vector<Seg> t = s; // copy configuration for this branch
            Seg &sg = t[hitIdx];

            // Rotate endpoints about sg.cen (cw or ccw)
            Pt newA = cw ? rotCW(sg.a, sg.cen) : rotCCW(sg.a, sg.cen);
            Pt newB = cw ? rotCW(sg.b, sg.cen) : rotCCW(sg.b, sg.cen);
            sg.a = newA;
            sg.b = newB;

            // rotated landing point
            Pt newHit = cw ? rotCW(hitPt, sg.cen) : rotCCW(hitPt, sg.cen);

            long long newMask = mask | (1LL << hitIdx);

            // If cross, rotate mate too and mark it as tilted
            if (g.cross && g.mate != -1) {
                int j = g.mate;
                Seg &mateSeg = t[j];
                // rotate mate endpoints about same center
                mateSeg.a = cw ? rotCW(initS[j].a, g.cen) : rotCCW(initS[j].a, g.cen);
                mateSeg.b = cw ? rotCW(initS[j].b, g.cen) : rotCCW(initS[j].b, g.cen);
                mateSeg.cen = g.cen; // intersection remains
                mateSeg.cross = true;
                newMask |= (1LL << j);
            }

            // Continue the simulation from newHit in this new configuration
            go(newHit, t, newMask);
        };

        tryTilt(true);
        tryTilt(false);
    }

    // Fill memo for endpoint state if we are at endpoint
    if (eid != -1) {
        auto &st = memo[{eid, mask}];
        for (int x : outX) st.insert(x);
    }
}

Pt midpoint(const Pt &a, const Pt &b) {
    return Pt( (a.x + b.x)/2, (a.y + b.y)/2 );
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    vector<tuple<int,int,int,int>> raw(n);
    for (int i = 0; i < n; ++i) {
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        raw[i] = make_tuple(x1,y1,x2,y2);
    }
    cin >> startPos.x >> startPos.y;

    initS.assign(n, Seg());
    vector<Seg> cur(n);

    // initialize segments with midpoints as center
    for (int i = 0; i < n; ++i) {
        int x1,y1,x2,y2;
        tie(x1,y1,x2,y2) = raw[i];
        initS[i].a = Pt(x1,y1);
        initS[i].b = Pt(x2,y2);
        initS[i].idx = i;
        initS[i].mid = midpoint(initS[i].a, initS[i].b);
        initS[i].cen = initS[i].mid;
        initS[i].cross = false;
        initS[i].mate = -1;
        cur[i] = initS[i];
    }

    // detect intersections and set cross / centers to the intersection point
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            auto pr = intersection_point(initS[i].a, initS[i].b, initS[j].a, initS[j].b);
            if (pr.first) {
                Pt p = pr.second;
                initS[i].cross = initS[j].cross = true;
                initS[i].mate = j; initS[j].mate = i;
                initS[i].cen = initS[j].cen = p;
                cur[i] = initS[i];
                cur[j] = initS[j];
            }
        }
    }

    go(startPos, cur, 0LL);

    // Print unique x's sorted (set iteration)
    for (int x : outX) cout << x << '\n';
    return 0;
}
