/*
    Problem: Iskanje mostov in presečnih točk v neusmerjenem grafu.
    Naloge: 
        https://cses.fi/problemset/task/2076
        https://cses.fi/problemset/task/2077
*/

vector<vector<int>> g;

int d[maxn], low[maxn];

int timer = 0;
set<int> presečne_točke;
vector<ii> mostovi;

void tarjan_dfs(int prev, int v) {
    d[v] = low[v] = ++timer;

    int cnt = 0;
    for(int u : g[v]) {
        if(u==prev) continue;
        if(d[u]==0) {
            tarjan_dfs(v,u);
            low[v] = min(low[v], low[u]);

            if(d[v] <= low[u]) presečne_točke.emplace(v);
            if(d[v] < low[u]) mostovi.pb(v,u);
            cnt++;
        } else {
            low[v] = min(low[v], d[u]);
            if(prev==v) presečne_točke.erase(v);
        }
    }

    if(prev == v && cnt > 1) presečne_točke.emplace(v);
    else if(prev == v && cnt == 1) presečne_točke.erase(v);
}
