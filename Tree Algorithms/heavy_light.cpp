/*
    Naslov: Heavy-Light Decomposition
    Problem: Range queries na poti med poljubnima vozliščema v drevesu.
    Naloge:
        https://cses.fi/problemset/task/1138
        https://cses.fi/problemset/view/2134/
*/

int timer = 0;
 
void heavy_light(int r, int v) {
    aux[v] = r; idx[v] = timer++;
    last[r] = v;
    priority_queue<ii> pq;
 
    for(int u : G[v]) {
        if(u != p[v]) {
            pq.emplace(sz[u], u);
        }
    }
 
    int w, u;
    if(!pq.empty()) {
        tie(w,u) = pq.top(); pq.pop();
        heavy_light(r,u);
    }
 
    while(!pq.empty()) {
        tie(w,u) = pq.top(); pq.pop();
        heavy_light(u,u);
    }
}
