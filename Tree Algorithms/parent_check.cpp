/*
	Naslov: Parent Check
 	Problem: Ali je vozlišče v starš vozlišča u.
  	Čas per build: O(N)
   	Čas per query: O(1)
	Prostor: O(N)
*/

const int maxn = int(3e5) + 10;
vector<vector<int>> G;

int tin[maxn], tout[maxn], timer = 0;

void dfs(int prev, int v) {
	tin[v] = ++timer;
	for(int u : G[v]) {
		if(u != prev) dfs(v, u);
	}
	tout[v] = ++timer;
}

bool parent(int v, int u) {
	return tin[v] <= tin[u] && tout[u] <= tout[v];
}
