/*
    Naslov: Farach-Colton and Bender Algorithm
    Problem: Iskanje LCA
    Čas per build: O(N)
    Čas per query: O(1)
*/

const int maxn = int(1e6)+10;
const int lg = 21;

vector<vector<int>> g;

int d[maxn], euler[maxn], in[maxn];
int rmq[maxn][lg]; 

int bucket[maxn][11];
int masks[maxn], memo[maxn];

int n, K, timer = 0;

void dfs(int prev, int v) {
    in[v] = timer;
    euler[timer++] = v;

    for(int u : g[v]) {
        if(u != prev) {
            d[u] = d[v] + 1;
            dfs(v,u);
            euler[timer++] = v;
        }
    }
}

int compare(int v, int u) {
    if(d[v] < d[u]) return v;
    else return u;
}

void build() {
    K = __lg(timer)>>1;
    K = max(K, 1);

    for(int i = 0; i < (1<<(K-1)); i++) {
        int idx = 0, cnt = 0, ans = 0;
        for(int j = 1; j < K; j++) {
            cnt += (i&(1<<(K-1-j))) ? -1 : 1;
            if(cnt < ans) {
                ans = cnt;
                idx = j;
            }
        }
        memo[i] = idx;
    }

    for(int i = 0; i*K < timer; i++) {
        for(int j = i*K; j < min(timer,(i+1)*K); j++) {
            int v = euler[j];
            bucket[i][j-i*K] = v;
        }
        int mask = 0;
        for(int j = 1; j < K; j++) {
            mask <<= 1;
            mask |= (d[bucket[i][j-1]] > d[bucket[i][j]]);
        }
        masks[i] = mask;
    }

    for(int i = 0; i*K < timer; i++) {
        rmq[i][0] = bucket[i][memo[masks[i]]];
    }

    int sz = (timer / K) + 1;
    for(int k = 1; k < lg; k++) {
        for(int i = 0; i + (1<<k) - 1 < sz; i++) {
            int v = rmq[i][k-1];
            int u = rmq[i+(1<<(k-1))][k-1];
            rmq[i][k] = compare(v,u);
        }
    }
}

int prefix(int mask, int r) {
    mask &= ((1<<(K-1))-1) ^ ((1<<(K-1-r))-1);
    return mask;
}

int suffix(int mask, int l) {
    mask |= ((1<<(K-1))-1) ^ ((1<<(K-1-l))-1);
    return mask;
}

int query(int v, int u) {
    int l = in[v];
    int r = in[u];
    if(l > r) swap(l,r);

    int bl = l / K;
    int br = r / K;

    int mask;

    if(bl==br) {
        mask = suffix(masks[bl],l-bl*K); 
        mask = prefix(mask, r-br*K);
        return bucket[bl][memo[mask]];
    }

    mask = suffix(masks[bl],l-bl*K); 
    v = bucket[bl][memo[mask]];

    mask = prefix(masks[br], r-br*K);
    u = bucket[br][memo[mask]];

    int lca = compare(v,u);

    if(bl+1 < br) {
        int k = __lg(br-bl-1);

        v = rmq[bl+1][k];
        u = rmq[br-(1<<k)][k];

        lca = compare(lca,v);
        lca = compare(lca,u);
    }

    return lca;
}

void init() {
    d[0] = INT_MAX;

    dfs(1,1);
    build();
}
