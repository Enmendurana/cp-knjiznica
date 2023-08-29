/*
    Problem: Iskanje vseh palindromov v O(N)
    Naloga: https://cses.fi/problemset/task/1111/
    p[i] ... max palindrome border on index i
*/

void manacher() {
    string s, t; cin >> t;

    for(auto c : t) {
        s += string("#") + c;
    }

    s += "^"; s[0] = '$';
    int n = (int)s.size() - 1;
    int ans = 1;

    for(int l = 1, r = 1, i = 1; r < n; i++) {
        p[i] = max(0, min(r-i, p[l+(r-i)]));
        while(s[i-p[i]] == s[i+p[i]]) p[i]++;
        if(i+p[i] > r) {
            l = i-p[i], r = i+p[i];
        }
        if(p[ans] < p[i]) ans = i;
    }

    string sol; 

    for(int i = ans-p[ans]+1; i < ans + p[ans]; i++) {
        if(s[i]=='#') continue;
        sol += s[i];
    }

    cout << sol << "\n";
}
