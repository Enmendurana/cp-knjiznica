/*
    Naslov: Fenwick Tree
    Problem: Prefix sum
    Čas per build: O(N)
    Čas per update/query: O(log(N))
    Prostor: O(N)
*/

const int maxn = int(1e6)+10;
int bit[maxn], a[maxn]; 

int n;

void build() {
    memset(bit,0,sizeof(bit));
    for(int i = 1; i <= n; i++) {
        bit[i] += a[i];
        if(i+(i&-i) <= n) {
            bit[i+(i&-i)] += bit[i];
        }
    }
}

void update(int i, int x) {
    x = x - a[i];
    a[i] += x;
    for(;i <= n; i += (i&-i)) {
        bit[i] += x;
    }
}

int query(int i) {
    int ans = 0;
    for(;i > 0; i -= (i&-i)) {
        ans += bit[i];
    }
    return ans;
}
