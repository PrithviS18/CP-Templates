vector<ll> adj[MAXN];
ll depth[MAXN];
ll parent[MAXN];
ll up[MAXN][LOG];

void dfs(ll node,ll par)
{
    parent[node]=par;
    depth[node]=depth[par]+1;

    for(auto child:adj[node])
        if(child!=par)
            dfs(child,node);
}

ll lca(ll u,ll v)
{
    if(depth[u]<depth[v])
        swap(u,v);

    ll diff = depth[u]-depth[v];

    for(int i=0;i<LOG;i++)
        if(diff&(1<<i))
            u=up[u][i];

    if(u==v)
        return u;

    for(int i=LOG-1;i>=0;i--)
        if(up[u][i]!=up[v][i])
        {
            u=up[u][i];
            v=up[v][i];
        }

    return parent[u];
}