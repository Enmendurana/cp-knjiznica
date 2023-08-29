int d[maxn];

vector<vector<ii>> g;

void dijkstra(int s) {

    fill_n(d,maxn,INT_MAX);

    priority_queue<ii, vector<ii>, greater<ii>> pq;

    d[s] = 0; 
    pq.emplace(0,s);

    while(!pq.empty()) {
        auto [cost,v] = pq.top(); pq.pop();
        if(d[v]!=cost) continue;

        for(auto [u, w] : g[v]) {
            if(d[v]+w < d[u]) {
                d[u] = d[v]+w;
                pq.emplace(d[u],u);
            }
        }
    }
}
