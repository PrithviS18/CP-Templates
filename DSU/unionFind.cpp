vector<ll> parent,sizes;
multiset <ll> st;

ll find(ll x){
    if (parent[x]==x)return x;
    return parent[x]=find(parent[x]);
}

bool unions(ll x, ll y){
    ll x_root = find(x);
    ll y_root = find(y);
    if (x_root==y_root)return false;

    if (sizes[x_root] < sizes[y_root]){swap(x_root,y_root);}
    
    st.erase(st.find(sizes[x_root]));
    st.erase(st.find(sizes[y_root]));
    sizes[x_root]+=sizes[y_root];
    st.insert(sizes[x_root]);

    parent[y_root]=x_root;

    return true;
}