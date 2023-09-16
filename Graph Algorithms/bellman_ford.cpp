ll d[maxn], cost[maxn];
pair<int,int> edge[maxn];

bool bellman_ford(int n, int m) {
    fill_n(d,n+1,LLONG_MAX); d[1] = 0;
    bool ans = false;

    for(int i = 0; i < n; i++) {
        ans = false;
        for(int j = 0; j < m; j++) {
            auto [v,u] = edge[j];
            if(d[v] != LLONG_MAX && d[v]+cost[j] < d[u]) {
                d[u] = d[v]+cost[j];
                ans = true;
            }
        }
    }

    return ans;
}
