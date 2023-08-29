/*
    Naslov: Treap
    Problem: deljenje in združevanje več dreves
    Čas per split/merge: O(log(N))
    Prostor: O(N)
*/

const int maxn = int(1e6)+10;

int pri[maxn];
int levo[maxn], desno[maxn];
int sz[maxn];

void build() {
    memset(levo,0,sizeof(levo));
    memset(desno,0,sizeof(desno));
    for(int i = 0; i < maxn; i++) {
        sz[i] = 1;
        pri[i] = rand();
    }
}

void split(int v, int &l, int &r, int i) {
    if(v==0) {
        l = r = 0;
        return;
    }
    if(sz[levo[v]] < i) {
        split(desno[v],desno[v],r,i-sz[levo[v]]-1);
        l = v;
    } else {
        split(levo[v],l,levo[v],i);
        r = v;
    }
    sz[v] = sz[levo[v]] + sz[desno[v]] + 1;
}

void merge(int &v, int l, int r) {
    if(l==0||r==0) {
        v = l+r;
        return;
    }
    if(pri[l] > pri[r]) {
        merge(desno[l],desno[l],r);
        v = l;
    } else {
        merge(levo[r],l,levo[r]);
        v = r;
    }
    sz[v] = sz[levo[v]] + sz[desno[v]] + 1;
}
