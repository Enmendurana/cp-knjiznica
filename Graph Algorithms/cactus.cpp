/*
    Naslov: Cactus
    Problem: "stiskanje" preprostih ciklov v kaktus grafu
    Čas: O(N)
    Naloga: https://codeforces.com/contest/231/problem/E
*/

int id[maxn], vis[maxn];
int d[maxn], p[maxn];

void dfs(int prev, int v) {
    p[v] = prev; id[v] = v; 
    vis[v] = 1;

    for(int u : g[v]) {
        if(!vis[u]) {
            d[u] = d[v] + 1;
            dfs(v,u);
        }
    }

    for(int u : g[v]) {
        if(u != prev) {
            if(d[id[v]] > d[id[u]]) {
                id[v] = id[u];
            }
        }
    }
}
