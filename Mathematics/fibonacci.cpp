/*
    Naslov: Fibonacci
    Problem: nek woodoo magic s potenciranjem matrik za fib v O(log(N))
    Čas: O(log(N))
    Prostor: O(log(N))
    Naloga: https://cses.fi/problemset/task/1722
*/

map<ll, ll> memo;
 
ll fib(ll n) {
    if(n < 2) return n;
    if(memo[n] != 0) return memo[n];
    ll k = (n+1)>>1;
    if(n&1) {
        memo[n] = fib(k) * fib(k) + fib(k-1) * fib(k-1);
    } else {
        memo[n] = (2*fib(k-1) + fib(k)) * fib(k);
    }
    memo[n] %= mod;
    return memo[n];
}
