/*
    Problem: finding minimal rotation v string-u.
    Naloga: https://cses.fi/problemset/task/1110
*/

int duval() {
    int ans = 0;
    s += s;

    int n = (int)s.size();

    for(int l = 0; l < (n>>1);) {
        ans = l;
        int r = l+1, k = l;
        for(;r < n && s[k] <= s[r]; r++) {
            if(s[k] < s[r]) {
                k = l;
            } else {
                k++;
            }
        }
        while(l <= k) l += r - k;
    }

    return ans;
}
