#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef pair<ll, ll> node;
typedef tree<node, null_type, less<node>,
            rb_tree_tag, tree_order_statistics_node_update> ordered_set;

// st.order_of_key(node(a,i)),st.insert(node(a,i))
ordered_set st;
