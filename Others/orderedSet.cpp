#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef pair<ll, ll> node;
typedef tree<node, null_type, less<node>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

void solve() {
    ll n, m;
    cin >> n >> m;
    map<ll, vector<ll>> mpp;

    for (int i = 0; i < n; i++) {
        ll a, b;
        cin >> a >> b;
        mpp[b].push_back(a);
    }

    vector<pair<ll, ll>> vec;
    for (auto& it : mpp) {
        sort(it.second.begin(), it.second.end());
        for (ll a : it.second) {
            vec.push_back(make_pair(it.first, a));
        }
    }

    ll maxx = 0, minn = 0;
    ordered_set st; 


    for (int i = n - 1; i >= 0; i--) {
        // cout<<vec[i].first<<" ";
        st.insert(node(vec[i].second, i));
        ll val1 = st.order_of_key(node(vec[i].first, n));
        // cout<<val1<<" ";
        if (vec[i].second == 1) {
            minn++;
        }

        ll val = 0;

        // Check if b equals m
        if (vec[i].first == m) {
            val += n - i;
        } else {
            
            val = upper_bound(mpp[m].begin(), mpp[m].end(), vec[i].first) - mpp[m].begin();
        }

     
        maxx = max(maxx, val1 - min(val, minn));
    }

    cout << maxx << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    int t = 1;
    cin >> t; // Read the number of test cases
    for (int i = 1; i <= t; i++) {
        solve(); // Call the solve function for each test case
    }

}