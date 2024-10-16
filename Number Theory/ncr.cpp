vector<ll> fact(N, 0), invfact(N, 0);

ll mod_mul(ll a, ll b){
    a = a % mod;
    b = b % mod;
    return (((a * b) % mod) + mod) % mod;
}
 
ll mod_add(ll a, ll b){
    a = a % mod;
    b = b % mod;
    return (((a + b) % mod) + mod) % mod;
}

ll mod =  1e9+7;
const ll N = 2e5+1;
ll fact[N],invfact[N];

ll power(ll x, ll y){
    ll res = 1;
    x = x % mod;
    while(y > 0){
        if(y & 1)
            res = res * x % mod;
        x = x * x % mod;
        y = y >> 1;
    }
    return res;
}
void factorials(){
    fact[0] = 1;
    for(int i=1;i<N;i++) 
        fact[i] = (i * 1LL * fact[i - 1]) % mod;
    invfact[N-1] = power(fact[N-1], mod - 2);
    for(int i=N-2;i>=0;i--) 
        invfact[i] = ((i + 1) * 1LL * invfact[i + 1]) % mod;
}

ll ncr(ll n, ll r) {
    if(r > n || n < 0 || r < 0)
        return 0;
    return ((fact[n] * invfact[r]) % mod * invfact[n - r]) % mod;
}