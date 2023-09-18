/*
    Naslov: Minimum Cost Max Flow (Potentials)
    Naloga: Minimum cena, da pošljem flow iz vozlišča s v vozlišče t
    Čas: O(F*M*log(N))
    Naloga: https://cses.fi/problemset/task/2121
*/

vector<vector<int>> g;

int cap[maxm], flow[maxm];
int weight[maxm];
int d[maxn], p[maxn], pot[maxn];

int edge[maxm], tr = 0;

void add_edge(int v, int u, int c, int w) {
    g[v].pb(tr); edge[tr] = u;
    weight[tr] = w; cap[tr] = c; flow[tr] = 0;

    g[u].pb(++tr); edge[tr] = v;
    weight[tr] = -w; cap[tr] = c; flow[tr++] = c;
}

bool dijkstra(int s, int t) {
    fill_n(d,maxn,INT_MAX);
    d[s] = 0;

    priority_queue<ii, vector<ii>, greater<ii>> pq;
    pq.emplace(d[s],s);

    bool ans = 0;

    while(!pq.empty()) {
        auto [dist, v] = pq.top(); pq.pop();
        if(v==t) {
            ans = 1; break;
        }

        if(dist != d[v]) continue;

        for(int i : g[v]) {
            int u = edge[i];
            int w = weight[i] + pot[v] - pot[u];
            if(flow[i] < cap[i] && d[v] + w < d[u]) {
                d[u] = d[v] + w;
                p[u] = i;
                pq.emplace(d[u],u);
            }
        }
    }

    for(int v = 1; v <= t; v++) {
        d[v] += pot[v] - pot[s];
    }

    swap(pot,d);
    return ans;
}

int aug(int s, int t) {
    int v = t;
    int f = INT_MAX;

    while(v != s) {
        f = min(f, cap[p[v]]-flow[p[v]]);
        v = edge[p[v]^1];
    }

    for(v = t; v != s;) {
        flow[p[v]] += f;
        flow[p[v]^1] -= f;
        v = edge[p[v]^1];
    }

    return f;
}

int mcmf(int s, int t) {
    int cost = 0;

    while(dijkstra(s,t)) {
        cost += pot[t] * aug(s,t);
    }

    return cost;
}
