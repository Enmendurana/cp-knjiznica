/*
    Problem: Convex Hull
    Naloga: https://cses.fi/problemset/task/2195
*/

vector<pll> P;
 
bool ok[maxn];
 
bool check(int i, int j, int k) {
    pll a = P[i], b = P[j], c = P[k];
    pll prev = {b.ff-a.ff, b.ss-a.ss};
    pll now = {c.ff-b.ff, c.ss-b.ss};
 
    ll ans = prev.ff * now.ss - prev.ss * now.ff;
 
    return (ans <= 0);
}
 
void andrew(int n) {
    memset(ok,false,sizeof(ok));
    stack<ii> st;
 
    st.emplace(0,0);
 
    while(!st.empty()) {
        auto [i, j] = st.top();
        int k = j+1;
 
        ok[i] = ok[j] = true;
 
        if(k >= n) break;
        
        while(!check(i,j,k)) {
            st.pop(); ok[j] = false;
            tie(i,j) = st.top();
        }
        
        st.emplace(j,k);
    }
}
 
void solve() {
 
    vector<ii> ans;
 
    int n; cin >> n;
    P.resize(n);
 
    for(auto &[x, y] : P) {
        cin >> x >> y;
    }
    sort(P.begin(), P.end());
 
    andrew(n);
    for(int i = 1; i < n-1; i++) {
        if(ok[i]) ans.pb(P[i]);
    }
 
    reverse(P.begin(), P.end());
 
    andrew(n);
    for(int i = 1; i < n-1; i++) {
        if(ok[i]) ans.pb(P[i]);
    }
 
    ans.pb(P[0]); ans.pb(P[n-1]);
 
    cout << (int)ans.size() << "\n";
 
    for(auto [x, y] : ans) {
        cout << x << " " << y << "\n";
    }
}
