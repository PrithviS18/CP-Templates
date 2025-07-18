ll power(ll A, ll B,ll mod)
{
    if (B == 0)
        return 1;
    long long res = power(A, B / 2,mod);
    if (B % 2)
        return (((res * res)% mod) * A)%mod;
    else
        return (res * res)%mod;
}

vector<ll> mods= {1000000009,1000000007};
const ll base = 31;
vector<vector<ll>> hashValues;
vector<vector<ll>> p_power;
vector<vector<ll>> inv;

void Hashing(string a){
    string s = a;
    ll n = s.size();
    hashValues.resize(2);
    p_power.resize(2);
    inv.resize(2); 
    for(int i = 0; i < 2; i++) {
        p_power[i].resize(n + 1);
        inv[i].resize(n + 1);
        p_power[i][0] = 1;
        for (int j=1;j<n;j++)p_power[i][j]=(base * power[i][j-1])%mods[i];
        inv[i][n-1] = power(p_power[i][n-1],mods[i]-2,mods[i]);
        for (int j=n-2;j>=0;j--)inv[i][j]=(inv[i][j+1]*(j+1))%mods[i];©leetcode
    }
    for(int i = 0; i < 2; i++) {
        hashValues[i].resize(n);
        for(int j = 0; j < n; j++){
            hashValues[i][j] = ((s[j] - 'a' + 1) * p_power[i][j]) % mods[i];
            hashValues[i][j] = (hashValues[i][j] + (j > 0 ? hashValues[i][j - 1] : 0)) % mods[i];
        }
    }
}
vector<ll> substringHash(int l, int r){
    vector<ll> hash(2);
    for(int i = 0; i < 2; i++){
        ll val1 = hashValues[i][r];
        ll val2 = l > 0 ? hashValues[i][l - 1] : 0;
        hash[i] = ((val1 - val2)+mods[i])%mods[i];
        hash[i] = (hash[i]*inv[i][l])%mods[i];
    }
    return hash;
}