/*
    Naslov: Dynamic Connectivity
    Problem: 
      +  A new edge is created between nodes a and b.
      +  An existing edge between nodes a and b is removed.
      +  Report the number of components after every event.
    Čas: O(K*log(K))
    Prostor: O(K*log(K))
*/

int ans[maxn];
int dsu[maxn], sz[maxn];

int find_set(int v) {
    while(dsu[v] != v) v = dsu[v];
    return v;
}

stack<int> st;

int union_set(int v, int u) {
    v = find_set(v);
    u = find_set(u);
    if(v != u) {
        if(sz[v] < sz[u]) swap(v,u);
        dsu[u] = v; sz[v] += sz[u];
        st.emplace(u);
    }
    return (v != u);
}

void rollback() {
    while(st.top() != -1) {
        int u = st.top(); st.pop();
        sz[dsu[u]] -= sz[u]; dsu[u] = u;
    }
    st.pop();
}

// a[i] = (zač, konec, v, u)
void seg(vector<iiii> a, int l, int r, int x) {
    st.emplace(-1);

    vector<iiii> b;

    for(auto [s, e, v, u] : a) {
        if(e <= l || r <= s) continue;
        if(s <= l && r <= e) x -= union_set(v,u);
        else b.pb(s,e,v,u);
    }

    if(r-l == 1) {
        ans[l] = x;
    } else {
        int mid = (l+r) >> 1;
        seg(b,l,mid,x);
        seg(b,mid,r,x);
    }

    rollback();
}
