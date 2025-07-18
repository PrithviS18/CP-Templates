#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef pair<ll, ll> node;
typedef tree<node, null_type, less<node>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ordered_set st; 
st.insert(node(vec[i].second, i));
ll val1 = st.order_of_key(node(vec[i].first, n));
auto it = find_by_order(index) (it->first)
