/*
	Naslov: Pregled v Širino
 	Problem: Najkrajša dolžina vozlišč od začetnega vozlišča s
	Čas: O(V + E)
 	Prostor: O(V + E)
*/

const int maxn = int(3e5) + 10;
int d[maxn]; vector<vector<int>> G;

void bfs(int s) {
	memset(d,-1,sizeof(d));
	d[s] = 0;

	queue<int> q({s});

	while(!q.empty()) {
		int v = q.front(); q.pop();
		for(int u : G[v]) {
			if(d[u] == -1) {
				d[u] = d[v]+1;
				q.push(u);
			}
		}
	}
}
