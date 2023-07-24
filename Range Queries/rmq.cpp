/*
	Naslov: Range Minimum Query
 	Problem: Min na intervalu [l, r]
  	Čas per init: O(N * log(N))
    Čas per query: O(1)
	Prostor: O(N * log(N))
*/

const int maxn = int(3e5) + 10;

int a[maxn], rmq[maxn][30], n;

void init() {
	for(int i = 0; i < n; i++) {
		rmq[i][0] = a[i];
	}

	for(int k = 1; k < 30; k++) {
		for(int i = 0; i + (1<<k) - 1 < n; i++) {
			rmq[i][k] = min(rmq[i][k-1], rmq[i+(1<<(k-1))][k-1];
		}
	}
}

int query(int l, int r) {
	int k = __lg(r-l+1);
	return min(rmq[l][k], rmq[r-(1<<k)+1][k]);
}
