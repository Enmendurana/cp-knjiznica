const int maxn = int(1e6)+10;
const int lg = 21;

int p[maxn][lg];
int d[maxn];

vector<vector<int>> g;

void dfs(int prev, int v) {
    p[v][0] = prev;
    d[v] = d[prev]+1;

    for(int u : g[v]) {
        if(!d[u]) {
            dfs(v,u);
        }
    }
}

void init(int s, int n) {
    dfs(s,s);
    for(int k = 1; k < lg; k++) {
        for(int v = 1; v <= n; v++) {
            p[v][k] = p[p[v][k-1]][k-1];
        }
    }
}

int query(int v, int u) {
    if(d[v] < d[u]) swap(v,u);

    for(int k = lg-1; d[v] > d[u]; k--) {
        if(d[p[v][k]] >= d[u]) {
            v = p[v][k];
        }
    }
    if(v==u) return v;
    for(int k = lg-1; p[v][0] != p[u][0]; k--) {
        if(p[v][k] != p[u][k]) {
            v = p[v][k];
            u = p[u][k];
        }
    }
    return p[v][0];
}
