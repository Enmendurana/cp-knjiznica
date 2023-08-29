/*
    Problem: strongly connected components v usmerjenem grafu.
*/

vector<vector<int>> g;

int timer = 0;
int d[maxn], low[maxn];

bool ok[maxn]; stack<int> st;
int scc[maxn];

void tarjan_scc(int v) {
    d[v] = low[v] = ++timer;
    ok[v] = true;
    st.push(v);

    for(int u : g[v]) {
        if(d[u]==0) {
            tarjan_scc(u);
            low[v] = min(low[v],low[u]);
        } else if(ok[u]) {
            low[v] = min(low[v],d[u]);
        }
    }

    if(d[v]==low[v]) {
        int u = 0;
        while(u != v) {
            u = st.top(); st.pop();
            ok[u] = false;
            scc[u] = v;
        }
    }
}
