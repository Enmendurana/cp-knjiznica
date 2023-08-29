/*
    Problem: ploščina lika
    Naloga: https://cses.fi/problemset/task/2191
*/

vector<pll> P; int n;
 
ll area() {
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        ans += P[i].ff * P[i+1].ss - P[i+1].ff * P[i].ss;
    }
    // (abs(ans) >> 1);
    return abs(ans);
}
 
void solve() {
 
    cin >> n;
 
    P.resize(n);
 
    for(pll &p : P) {
        cin >> p.ff >> p.ss;
    }
 
    P.pb(P[0]);
 
    cout << area() << "\n";
}
