/*
	Naslov: Segment Tree
  	Problem: 	1. Povečaj vsako vrednost na intervalu [lx, rx) za w.
				2. Nastavi vsako vrednost na intervalu [lx, rx) na w.
				3. Izračunaj vsoto vrednosti na intervalu [lx, rx)
	Čas per build: O(N * log(N))	
  	Čas per query/update: O(log(N))
	Prostor: O(N)
 	Naloga: https://cses.fi/problemset/task/1735
*/

#define ll long long
const int maxn = int(3e5) + 10;

ll t[4*maxn], add[4*maxn], up[4*maxn], a[maxn];
int n, m;

void build(int v, int l, int r) {
    if(r-l==1) {
        if(l < n) t[v] = a[l];
    } else {
        int mid=(l+r)>>1;
        build(2*v,l,mid);
        build(2*v+1,mid,r);
        t[v] = t[2*v] + t[2*v+1];
    }
}

void push(int v, int l, int r) {
    if(r-l==1) return;
    int mid=(l+r)>>1;
    if(up[v]!=0) {
        t[2*v] = up[v]*(mid-l);
        t[2*v+1] = up[v]*(r-mid);
        add[2*v] = add[2*v+1] = 0;
        up[2*v] = up[2*v+1] = up[v];
        up[v] = 0;
    }
    if(add[v] != 0) {
        t[2*v] += add[v]*(mid-l);
        t[2*v+1] += add[v]*(r-mid);
        add[2*v] += add[v];
        add[2*v+1] += add[v];
        add[v] = 0;
    }
}

void increase(int v, int l, int r, int lx, int rx, ll w) {
    push(v,l,r);
    if(lx <= l && r <= rx) {
        t[v] += w * (r-l);
        add[v] += w;
    } else if(r <= lx || rx <= l) {
        return;
    } else {
        int mid=(l+r)>>1;
        increase(2*v,l,mid,lx,rx,w);
        increase(2*v+1,mid,r,lx,rx,w);
        t[v]=t[2*v]+t[2*v+1];
    }
}

void update(int v, int l, int r, int lx, int rx, ll w) {
    push(v,l,r);
    if(lx <= l && r <= rx) {
        t[v] = w*(r-l);
        up[v] = w;
    } else if(r <= lx || rx <= l) {
        return;
    } else {
        int mid=(l+r)>>1;
        update(2*v,l,mid,lx,rx,w);
        update(2*v+1,mid,r,lx,rx,w);
        t[v]=t[2*v]+t[2*v+1];
    }
}

ll query(int v, int l, int r, int lx, int rx) {
    push(v,l,r);
    if(lx <= l && r <= rx) {
        return t[v];
    } else if(r <= lx || rx <= l) {
        return 0;
    } else {
        int mid=(l+r)>>1;
        ll s1 = query(2*v,l,mid,lx,rx);
        ll s2 = query(2*v+1,mid,r,lx,rx);
        t[v]=t[2*v]+t[2*v+1];
        return s1+s2;
    }
}

void solve() {

    memset(t,0,sizeof(t));
    memset(add,0,sizeof(add));
    memset(up,0,sizeof(up));

    cin >> n >> m;

    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    build(1,0,2*n);

    for(int op, lx, rx; m--;) {
        cin >> op >> lx >> rx; l--;
        if(op==1) {
            int w; cin >> w;
            increase(1,0,2*n,lx,rx,w);
        } else if(op==2) {
            int w; cin >> w;
            update(1,0,2*n,lx,rx,w);
        } else {
            cout << query(1,0,2*n,lx,rx) << "\n";
        }
    }
}
