/*
	Naslov: Z-Function
	Problem: Iskanje vzorcev v stringu.
	Čas: O(N)
	Prostor: O(N)
	Naloga: https://cses.fi/problemset/task/1753
*/

const int maxn = int(1e6) + 10;
string a, b; cin >> a >> b;
string s = b + "$" + a;

int ans = 0;

int m = (int)b.size();
int n = (int)s.size();
vector<int> z(n, 0);

for(int i = 1, l = 0, r = 0; i < n; i++) {
    if(i <= r) z[i] = min(r-i+1, z[i-l]);
    while(i+z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
    if(i + z[i] - 1 > r) {
        l = i;
        r = i + z[i] - 1;
    }
    if(z[i] == m) ans++;
}

cout << ans << "\n";
