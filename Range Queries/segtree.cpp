/*
	Naslov: Segment Tree
 	Problem: 	
  		1. Range queries [lx, rx)
  		2. Point updates
  	Čas per build: O(N * log(N))
	Čas per query/update: O(log(N))
 	Prostor: O(N)
*/

typedef long long ll;
const int maxn = int(2e5) + 10;

ll a[maxn], t[4*maxn]; int n;

void build(int v, int l, int r) {
    if(r-l==1) {
        if(l < n) t[v] = a[l];
    } else {
        int mid = (l+r)>>1;
        build(2*v,l,mid);
        build(2*v+1,mid,r);
        t[v] = t[2*v] + t[2*v+1];
    }
}
 
ll query(int v, int l, int r, int lx, int rx) {
    if(lx <= l && r <= rx) {
        return t[v];
    } else if(r <= lx || rx <= l) {
        return 0;
    } else {
        int mid = (l+r)>>1;
        ll s1 = query(2*v,l,mid,lx,rx);
        ll s2 = query(2*v+1,mid,r,lx,rx);
        return s1 + s2;
    }
}
 
void update(int v, int l, int r, int i, int w) {
    if(r-l==1) {
        t[v] = w;
    } else {
        int mid=(r+l)>>1;
        if(i < mid) {
            update(2*v,l,mid,i,w);
        } else {
            update(2*v+1,mid,r,i,w);
        }
        t[v] = t[2*v]+t[2*v+1];
    }
}
