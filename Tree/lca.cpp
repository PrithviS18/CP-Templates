vector<ll> depth;
vector<vector<ll>> adj;

void dfs(ll node,ll parent, ll lvl){
    depth[node]=lvl+1;
    for (auto it:adj[node])dfs(it,node,lvl+1);
}


void solve(int g) {
    ll n,q;
    cin>>n>>q;
    ll LOG=0;
    while ((1<<(LOG))<=n)LOG++;
    vector <vector<ll>> up(n+1,vector<ll> (LOG+1,0));


    depth = vector<ll> (n+1,0);
    adj = vector<vector<ll>> (n+1);
    for (int i=2;i<=n;i++)adj[parent[i]].push_back(i);
    
    ll parent[n+1];
    parent[0]=parent[1]=0;

    dfs(1,0,0);

    for (int i=1;i<=n;i++){
        up[i][0]=parent[i];
        for (int j=1;j<LOG;j++){
            up[i][j]=up[up[i][j-1]][j-1];
        }
    }
    // cout<<(1<<LOG)<<endl;
    while (q--){
        ll u,v;
        cin>>u>>v;

        if (depth[u]<depth[v])swap(u,v);
        ll diff = depth[u]-depth[v];
        // cout<<diff<<" ";
        for (int i=LOG;i>=0;i--){
            if ((1<<i)&diff)u=up[u][i];
        }
        // cout<<u<<" "<<v<<endl;
        if (u==v){
            cout<<u<<endl;
            continue;
        }
        for (int i=LOG;i>=0;i--){
            if (up[u][i]!=up[v][i]){
                u=up[u][i];
                v=up[v][i];
            }
        }
        cout<<up[u][0]<<endl;
    }
}