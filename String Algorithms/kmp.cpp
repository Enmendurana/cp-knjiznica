/*
    Problem: Preštej, kolikokrat se pattern pojavi v text-u
    Čas: O(N)
*/

string p, s; // p = pattern, s = text
int n, m;

int kmp[maxn];

void kmp_preprocess() {
    kmp[0] = -1;
    for(int i = 0, j = -1; i < m;) {
        while(j!=-1 && p[i] != p[j]) j = kmp[j];
        kmp[++i] = ++j;
    }
}

int kmp_search() {
    int ans = 0;
    for(int i = 0, j = 0; i < n;) {
        while(j!=-1 && s[i]!=p[j]) j = kmp[j];
        ++i; ++j;
        if(j == m) {
            ans++;
            j = kmp[j];
        }
    }
    return ans;
}
