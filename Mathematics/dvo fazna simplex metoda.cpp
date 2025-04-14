/* * * * * * * * * * * * * * * * *
 *	author: omega
 *	created: 03-02-2025
 * * * * * * * * * * * * * * * * */

#include <bits/stdc++.h>

using namespace std;

struct buffer : streambuf {
int overflow(int x) {
    return x;
}
};

static buffer null_buffer;
static ostream null_stream(&null_buffer);

void local() {
#if defined(LOCAL_FLAG)
    freopen("/home/omega/Documents/input.in", "r", stdin);
    freopen("/home/omega/Documents/output.out", "w", stdout);
    freopen("/home/omega/Documents/error.err", "w", stderr);
    #define debug cerr
#else
    #define debug null_stream
#endif
}

#define ff first
#define ss second
#define pb emplace_back
#define pob pop_back
#define pf emplace_front
#define pof pop_front
#define endl '\n'

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int, int> ii;
typedef tuple<int, int, int> iii;
typedef pair<ll, ll> pll;
typedef tuple<ll, ll, ll> tlll;
typedef complex<double> cd;
typedef long double ld;

const ll mod = ll(1e9 + 7);
const int maxn = int(1e6) + 10;
const int maxm = int(1e3) + 10;
const int lg = 31;
const long double eps = (long double)(1e-9);

ld a[maxm][maxm], b[maxm], c[maxm];

int base[maxm];

ld x[maxm][maxm];

void vstavi(int i, int j) {
    for(int k = 0; k < maxm; k++) {
        x[j][k] += x[j][i] * x[i][k];
    }
    x[j][i] = 0;
}

void izpostavi(int i, int j) {
    for(int k = 0; k < maxm; k++) {
        x[j][k] = x[i][k] / (-x[i][j]);
    }
    x[j][j] = 0;
    x[j][i] = (1 / x[i][j]);
}

void print(int n) {

    cout << x[0][0] << "\n";

    for(int i = 1; i <= n; i++) {
        cout << (base[i] ? x[i][0] : 0) << " ";
    }

    cout << "\n";

}

void print(int vhod, int pivot, int n, int m) {
    debug << vhod << " " << pivot << "\n";
    for(int i = 1; i <= n+m+1; i++) {
        if(base[i]) {
            debug << "x[" << (i%(n+m+1)) << "] = ";
            for(int j = 0; j <= n+m+1; j++) {
                debug << x[i][j] << " ";
            }
            debug << "\n";
        }
    }

    debug << "z = ";

    for(int j = 0; j <= n+m+1; j++) {
        debug << x[0][j] << " ";
    }

    debug << "\n";
}

void simplex(int n, int m, int faza) {

    int w = n+m+1;

    if(faza == 1) {
        for(int i = 1; i <= m; i++) {
            x[n+i][0] = b[i]; base[n+i] = 1;
            for(int j = 1; j <= n; j++) {
                x[n+i][j] = -a[i][j];
            }
        }

        x[0][w] = -1;

        for(int i = 1; i <= m; i++) {
            x[n+i][w] = 1;
        }

        int pivot = 0;

        for(int i = n+1; i <= n+m; i++) {
            if(!pivot && (x[i][0] < 0)) {
                pivot = i;
            }
            if(pivot && (x[i][0] < x[pivot][0])) {
                pivot = i;
            }
        }

        if(!pivot) return;

        izpostavi(pivot, w);
        base[w] = 1; base[pivot] = 0;

        for(int i = 0; i <= n+m+1; i++) {
            vstavi(w, i);
        }

    }
    if(faza == 2) {
        if(base[w]) {
            cout << "nedopusten\n"; return;
        }

        for(int i = 1; i <= n+m; i++) {
            if(base[i] && x[i][0] + eps < 0) {
                cout << "nedopusten\n"; return;
            }
        }

        for(int j = 1; j <= n; j++) {
            x[0][j] = c[j];
        }

        for(int j = 1; j <= m; j++) {
            x[0][n+j] = 0;
        }

        for(int i = 0; i <= n+m; i++) {
            x[i][w] = 0;
        }

        base[w] = 0;

        for(int i = 0; i <= n; i++) {
            if(base[i]) vstavi(i, 0);
        }
    }

    int tr = 1000;

    while(tr--) {

        int vhod = 0;

        for(int j = 1; j <= n+m; j++) {
            if(x[0][j] > eps) {
                vhod = j; break;
            }
        }

        int pivot = 0;

        if(!vhod) {
            if(faza == 2) print(n);
            // print(n);
            return;
        }

        for(int i = 1; i <= n+m+1; i++) {
            if(base[i] && x[i][vhod] < -eps) {
                if(!pivot || (x[pivot][0] / x[pivot][vhod] < x[i][0] / x[i][vhod]+eps)) {
                    pivot = i;
                }
            }
        }

        if(!pivot) {
            cout << "neomejen\n"; return;
        }

        izpostavi(pivot, vhod);
        base[vhod] = 1; base[pivot] = 0;

        for(int i = 0; i <= n+m+1; i++) {
            vstavi(vhod, i);
        }

    }

    debug << "error\n";

}

void solve() {

    int n, m; cin >> n >> m;

    for(int i = 1; i <= n; i++) {
        cin >> c[i];
    }

    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    for(int i = 1; i <= m; i++) {
        cin >> b[i];
    }

    simplex(n,m,1); // print(0,0,n,m);
    simplex(n,m,2); // print(0,0,n,m);

}

signed main() {
    local();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1; // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
