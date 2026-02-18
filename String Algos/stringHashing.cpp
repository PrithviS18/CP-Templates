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


class Hashing {
public:
    ll mod = 1000000007;
    const ll base = 31;

    vector<ll> hashValues;
    vector<ll> p_power;
    vector<ll> inv;
    ll n;

    Hashing(const string &s) {
        n = s.size();

        hashValues.assign(n, 0);
        p_power.assign(n, 0);
        inv.assign(n, 0);

        /* compute base powers */
        p_power[0] = 1;
        for (int i = 1; i < n; i++) {
            p_power[i] = (p_power[i - 1] * base) % mod;
        }

        /* compute inverse powers */
        inv[n - 1] = power(p_power[n - 1], mod - 2, mod);
        for (int i = n - 2; i >= 0; i--) {
            inv[i] = (inv[i + 1] * base) % mod;
        }

        /* compute prefix hashes */
        for (int i = 0; i < n; i++) {
            ll val = ((s[i] - 'a' + 1) * p_power[i]) % mod;
            hashValues[i] = val;
            if (i > 0) {
                hashValues[i] = (hashValues[i] + hashValues[i - 1]) % mod;
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

    ll substringHash(int l, int r) {
        ll val1 = hashValues[r];
        ll val2 = (l > 0 ? hashValues[l - 1] : 0);

        ll hash = (val1 - val2 + mod) % mod;
        hash = (hash * inv[l]) % mod;

        return hash;
    }
};
