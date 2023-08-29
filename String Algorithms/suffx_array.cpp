void count_sort() {
    memset(cnt,0,sizeof(cnt));
    for(int i = 0; i < n; i++) {
        cnt[c[i]]++;
    }
    pos[0] = 0;

    for(int i = 1; i < n; i++) {
        pos[i] = pos[i-1]+cnt[i-1];
    }

    for(int i = 0; i < n; i++) {
        int j = c[p[i]];
        p_new[pos[j]] = p[i];
        pos[j]++;
    }
    swap(p, p_new);
}

void solve() {
    cin >> s;

    s += "$";
    n = (int)s.size();

    for(int i = 0; i < n; i++) {
        a[i] = {s[i], i};
    }

    sort(a, &a[n]);

    for(int i = 0; i < n; i++) {
        p[i] = a[i].ss;
    }

    c[p[0]] = 0;

    for(int i = 1; i < n; i++) {
        if(a[i].ff == a[i-1].ff) {
            c[p[i]] = c[p[i-1]];
        } else {
            c[p[i]] = c[p[i-1]] + 1;
        }
    }

    for(int k = 0; (1<<k) < n; k++) {
        for(int i = 0; i < n; i++) {
            p[i] = (p[i]-(1<<k)+n)%n;
        }

        count_sort();

        c_new[p[0]] = 0;

        for(int i = 1; i < n; i++) {
            ii prev = {c[p[i-1]], c[(p[i-1] + (1<<k)) % n]};
            ii now = {c[p[i]], c[(p[i] + (1<<k)) % n]};
            if(prev == now) {
                c_new[p[i]] = c_new[p[i-1]];
            } else {
                c_new[p[i]] = c_new[p[i-1]]+1;
            }
        }

        swap(c, c_new);
    }
}
