map<char, int> trie[maxn];
int suff[maxn], d[maxn], timer = 0;
bool stop[maxn];

int memo[maxn];

int add_str(string s) {
    int v = 0;
    for(char c : s) {
        if(!trie[v][c]) {
            trie[v][c] = ++timer;
            d[timer] = d[v]+1;
        } 
        v = trie[v][c];
    }
    stop[v] = true;
    return v;
}

void push_links() {
    suff[0] = -1;
    queue<int> q({0});

    while(!q.empty()) {
        int v = q.front(); q.pop();

        for(auto [c, u] : trie[v]) {
            int j = suff[v];

            while(j!=-1 && !trie[j][c]) j = suff[j];

            if(j!=-1) suff[u] = trie[j][c]; 
            q.push(u);
        }
    }
}
