class Hashing {
public:
    vector<ll> mods = {1000000009, 1000000007};
    const ll base = 31;
    vector<vector<ll>> hashValues;
    vector<vector<ll>> p_power;
    vector<vector<ll>> inv;
    ll n;

    Hashing(const string &s) {
        n = s.size();
        hashValues.assign(2, vector<ll>(n));
        p_power.assign(2, vector<ll>(n));
        inv.assign(2, vector<ll>(n));

        for (int i = 0; i < 2; i++) {
            p_power[i][0] = 1;
            for (int j = 1; j < n; j++) {
                p_power[i][j] = (p_power[i][j - 1] * base) % mods[i];
            }

            inv[i][n - 1] = power(p_power[i][n - 1], mods[i] - 2, mods[i]);
            for (int j = n - 2; j >= 0; j--) {
                inv[i][j] = (inv[i][j + 1] * base) % mods[i];
            }

            for (int j = 0; j < n; j++) {
                ll val = ((s[j] - 'a' + 1) * p_power[i][j]) % mods[i];
                hashValues[i][j] = val;
                if (j > 0) {
                    hashValues[i][j] = (hashValues[i][j] + hashValues[i][j - 1]) % mods[i];
                }
            }
        }
    }

    ll power(ll A, ll B, ll mod) {
        if (B == 0) return 1;
        ll res = power(A, B / 2, mod);
        res = (res * res) % mod;
        if (B % 2) res = (res * A) % mod;
        return res;
    }

    string hashToString(const vector<ll> &hash) {
        return to_string(hash[0]) + "#" + to_string(hash[1]);
    }

    vector<ll> substringHash(int l, int r) {
        vector<ll> hash(2);
        for (int i = 0; i < 2; i++) {
            ll val1 = hashValues[i][r];
            ll val2 = l > 0 ? hashValues[i][l - 1] : 0;
            hash[i] = ((val1 - val2 + mods[i]) % mods[i]);
            hash[i] = (hash[i] * inv[i][l]) % mods[i];
        }
        return hash;
    }
};
