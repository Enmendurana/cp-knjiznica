vector<vector<tuple<ll,ll,ll>>> G;

int d[maxn], p[maxn], last[maxn];

bool bfs(int s, int t) {
    memset(d,-1,sizeof(d));
    memset(p,-1,sizeof(p));
    
    queue<int> q({s}); d[s] = 0;

    while(!q.empty()) {
        int v = q.front(); q.pop();
        if(v == t) break;
        for(auto &[u, cap, flow] : G[v]) {
            if((cap-flow > 0) && (d[u] == -1)) {
                d[u] = d[v]+1;
                q.push(u);
                p[u] = v;
            }
        }
    }
    return d[t] != -1;
}

unordered_map<int, unordered_map<int, int>> m;

ll dfs(int v, int t, ll f) {
    if((v==t) || (f==0)) return f;
    for(int &i = last[v]; i < G[v].size(); i++) {
        auto &[u, cap, flow] = G[v][i];
        if(d[u] != d[v]+1) continue;
        ll pushed = dfs(u, t, min(f, cap-flow));
        if(pushed != 0) {
            flow += pushed;
            auto &rflow = get<2>(G[u][m[u][v]]);
            rflow -= pushed;
            return pushed;
        }
    }
    return 0;
}

void add_edge(int v, int u, ll w, bool directed = true) {
    if(v == u) return;
    G[v].pb(u,w,0); 
    m[v][u] = G[v].size()-1;
    G[u].pb(v, (directed ? 0 : w), 0);
    m[u][v] = G[u].size()-1;
}

ll dinic(int s, int t) {
    ll mf = 0;
    while(bfs(s, t)) {
        memset(last,0,sizeof(last));
        while(ll f = dfs(s,t,LLONG_MAX)) {
            mf += f;
        }
    }
    return mf;
}

// O(V^2*E)

void min_cut() {
    vector<ii> edges;

    for(int v = 1; v <= n; v++) {
        for(auto [u, cap, flow] : G[v]) {
            if(d[v]!=-1&&d[u]==-1) {
                edges.pb(v,u);
            }
        }
    }

    for(auto [v, u] : edges) {
        cout << v << " " << u << "\n";
    }
}
