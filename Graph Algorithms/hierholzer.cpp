/*
  Problem: Eulerian path v neusmerjenem grafu. 
*/

set<pii> edges;

void add_edge(int v, int u) {
        if(v > u) swap(v, u);
        edges.emplace(pii{v, u});
}

void remove_edge(int v, int u) {
        if(v > u) swap(v, u);
        edges.erase(pii{v, u});
}

bool ok_edge(int v, int u) {
        if(v > u) swap(v, u);
        return edges.find(pii{v, u}) != edges.end();
}

vector<int> hierholzer(int s) {
        vector<int> ans;
        stack<int> st;
        st.push(s);

        while(!st.empty()) {
                int v = st.top();
                for(; d[v] < (int)G[v].size(); d[v]++) {
                        int u = G[v][d[v]];
                        if(ok_edge(v, u)) {
                                st.push(u);
                                remove_edge(v, u);
                                break;
                        }
                }
                if(d[v] == (int)G[v].size()) {
                        ans.pb(v);
                        st.pop();
                }
        }

        return ans;
}
