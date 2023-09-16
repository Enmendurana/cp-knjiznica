/*
    Naslov: Minimum Cost Max Flow
    Naloga: Minimum cena, da pošljem flow iz vozlišča s v vozlišče t
    Čas: O(F*N*log(N))
    Naloga: https://cses.fi/problemset/task/2121
*/

vector<vector<tuple<int,int,int,int>>> g;

int d[maxn], p[maxn];
int edge[maxm], timer = 0;
unordered_map<int, unordered_map<int,int>> um;

void add_edge(int v, int u, int cap, int w) {
    edge[timer] = v + u;
    um[v][timer] = (int)g[v].size();
    um[u][timer] = (int)g[u].size();
    g[v].pb(timer,w,cap,0);
    g[u].pb(timer,-w,0,0);
    ++timer;
}

bool dijkstra(int s, int t) {
    fill_n(d,t+1,INT_MAX);

    priority_queue<ii, vector<ii>, greater<ii>> pq;

    pq.emplace(0,s);
    d[s] = 0; p[s] = s;

    while(!pq.empty()) {
        auto [dist, v] = pq.top(); pq.pop();

        if(d[v] != dist) continue;

        for(auto [i,w,cap,flow] : g[v]) {
            int u = edge[i] - v;
            if(d[v] + w < d[u] && cap > flow) {
                d[u] = d[v] + w; 
                p[u] = i;
                pq.emplace(d[u],u);
            }
        }
    }

    return (d[t] != INT_MAX);
}

int aug(int s, int t, int k, int &cost) {
    int v = t, pushed = k;

    while(v != s) {
        int i = p[v]; 
        v = edge[i] - v;

        auto [j,w,cap,flow] = g[v][um[v][i]];
        pushed = min(pushed, cap-flow);
    }

    for(v = t; v != s;) {
        int i = p[v], u = v;
        v = edge[i] - v;

        auto &[j,w,cap,flow] = g[v][um[v][i]];
        int &rflow = get<3>(g[u][um[u][i]]);
        flow += pushed;
        rflow -= pushed;
    }

    cost += pushed * d[t];
    return pushed;
}

int min_cost(int s, int t, int mf) {
    int cost = 0;
    while(mf != 0 && dijkstra(s,t)) {
        mf -= aug(s,t,mf,cost);
    }
    return (mf==0) ? cost : -1;
}
