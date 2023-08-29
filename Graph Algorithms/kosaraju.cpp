/*
    Problem: 2-sat, strongly connected components
    Naloga: https://cses.fi/problemset/task/1684
*/

vector<vector<int>> g, gr;
vector<int> topsort;

bool visited[maxn]; 
int d[maxn];

void dfs(int v) {
    visited[v] = true;
    for(int u : g[v]) {
        if(!visited[u]) dfs(u);
    }
    topsort.pb(v);
}

void scc(int v, int id) {
    d[v] = id;
    for(int u : gr[v]) {
        if(!d[u]) scc(u, id);
    }
}

void solve() {
 
    memset(visited,false,sizeof(visited));
    memset(d,0,sizeof(d));

    int n, m; cin >> n >> m;

    m = 2*m+1;
    g.resize(m+1);
    gr.resize(m+1);

    for(int v, u; n--;) {
        string op; 
        cin >> op >> v;
        v *= 2;
        if(op=="+") v++;

        cin >> op >> u;
        u *= 2;
        if(op=="+") u++;

        g[v^1].pb(u);
        g[u^1].pb(v);

        gr[u].pb(v^1);
        gr[v].pb(u^1);
    }

    for(int v = 2; v <= m; v++) {
        if(!visited[v]) dfs(v);
    }

    reverse(topsort.begin(), topsort.end());

    int id = 0;
    for(int v : topsort) {
        if(!d[v]) scc(v, ++id);
        if(d[v]==d[v^1]) {
            cout << "IMPOSSIBLE\n";
            return;
        }
    }

    for(int v = 2; v <= m; v+=2) {
        if(d[v] > d[v+1]) cout << "- ";
        else cout << "+ ";
    }

    cout << "\n";
}
