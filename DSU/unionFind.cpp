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

struct DSU {
    std::vector<int> f, siz;
    
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }
    
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    
    int size(int x) {
        return siz[find(x)];
    }
};