/*
  Problem: Ali se daljici sekata/dotikata?
  Čas: O(1)
  Naloga: https://cses.fi/problemset/task/2190
*/

ll x[maxn][2], y[maxn][2];

int produkt(ll x1, ll y1, ll x2, ll y2) {
    ll ans = x1*y2 - x2*y1;
    return ans / max(1LL, abs(ans));
}

bool good(int v, int u) {
    int op1 = produkt(x[v][1] - x[v][0], y[v][1] - y[v][0], x[u][0] - x[v][1], y[u][0] - y[v][1]);
    int op2 = produkt(x[v][1] - x[v][0], y[v][1] - y[v][0], x[u][1] - x[v][1], y[u][1] - y[v][1]);

    bool bad = (x[v][0] < x[u][0] && x[v][1] < x[u][0] && x[v][0] < x[u][1] && x[v][1] < x[u][1]);
    bad |= (y[v][0] < y[u][0] && y[v][1] < y[u][0] && y[v][0] < y[u][1] && y[v][1] < y[u][1]);

    return (op1 * op2 <= 0) && !bad;
}

bool seka(int v, int u) {
    return good(v,u) && good(u,v);
}
