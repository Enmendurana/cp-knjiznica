/*
	Naslov: Pregled v Globino
	Problem: Iteracija skozi vsa vozlišča, do katerih lahko pridem iz vozlišča v
	Čas: O(V + E)
	Prostor: O(V + E)
*/ 

const int maxn = int(3e5) + 10;
bool visited[maxn];

void dfs(int v) {
	visited[v] = true;
	for(int u : G[v]) {
    		if(!visited[u]) dfs(u);
	}
}
