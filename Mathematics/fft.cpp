/*
  Naslov: FFT
  Problem: Množenje polinomov
  Čas: O(N * log(N))
  Prostor: O(N)
  Naloga: https://putka-upm.acm.si/tasks/t/genialis/
*/

typedef complex<double> cd;

void fft(vector<cd> &a, bool invert) {
    int n = (int)a.size();
    int lg_n = __lg(n);

    for (int i = 1, j = 0; i < n; i++) {
        int bit = (n >> 1);
        for (; j & bit; bit >>= 1) {
            j ^= bit;
        }
        j ^= bit;

        if(i > j) swap(a[i], a[j]);
    }

    for (int k = 2; k <= n; k <<= 1) {
        double ang = 2 * M_PI / k * (invert ? -1 : 1);
        cd wk(cos(ang), sin(ang));

        for (int i = 0; i < n; i += k) {
            cd w(1);
            for (int j = 0; j < (k>>1); j++) {
                cd u = a[i+j], v = a[i+j+(k>>1)] * w;
                a[i+j] = u + v;
                a[i+j+(k>>1)] = u - v;
                w *= wk;
            }
        }
    }

    if (invert) {
        for(cd &x : a) {
            x /= n;
        }
    }
}

vector<int> multiply(vector<int> &a, vector<int> &b) {
    vector<cd> fa(a.begin(), a.end());
    vector<cd> fb(b.begin(), b.end());

    int n = (int)a.size() + (int)b.size();

    if(n - (n&-n)) {
        n <<= 1;
        while(n - (n&-n)) {
            n -= (n&-n);
        }
    }

    fa.resize(n); fb.resize(n);
    fft(fa,0); fft(fb,0);

    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }

    fft(fa, 1);

    vector<int> ans(n);

    for (int i = 0; i < n; i++) {
        ans[i] = (int)round(fa[i].real());
    }

    return ans;
}
