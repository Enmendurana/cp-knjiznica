/*
	Naslov: Disjoint Set Union
 	Problem: Povezovanje množic med sabo in preverjanje, v katero množico spada vsak element.
	Čas: O(1)
 	Prostor: O(N)
*/

const int maxn = int(3e5) + 10;
int p[maxn], r[maxn];

void make_set(int v) {
	p[v] = v; r[v] = 0;
}

int find_set(int v) {
	if(p[v] != v) p[v] = find_set(p[v]);
	return p[v];
}

void union_set(int v, int u) {
	v = find_set(v);
	u = find_set(u);
	if(v != u) {
		if(r[v] < r[u]) swap(v, u);
		else if(r[v] == r[u]) r[v]++;
		p[u] = v;
	}
}

bool check_set(int v, int u) {
	return find_set(v) == find_set(u);
}
