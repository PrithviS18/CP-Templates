void solve(int g) {
   ll n,m,q;
   cin>>n>>m>>q;
   
   vector<vector<ll>> dist(n+1,vector<ll>(n+1,LLONG_MAX));
   
   for (int i=0;i<m;i++){
        ll a,b,c;
        cin>>a>>b>>c;
        dist[a][b]=min(dist[a][b],c),dist[b][a]=min(dist[b][a], c);
   }
   for (int i=1;i<=n;i++)dist[i][i]=0;
   for (int k=1;k<=n;k++){
        for (int i=1;i<=n;i++){
            for (int j=1;j<=n;j++){
                if (dist[i][k]!=LLONG_MAX && dist[k][j]!=LLONG_MAX){
                    dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
                }
            }
        }
    }
    while (q--){
        ll a,b;
        cin>>a>>b;
        cout<<(dist[a][b]==LLONG_MAX?-1:dist[a][b])<<endl;
    }
}