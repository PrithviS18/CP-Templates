void solve(int g) {
    ll n,q;
    cin>>n>>q;
    ll LOG=0;
    while ((1<<(LOG))<=n)LOG++;
    vector <vector<ll>> up(n+1,vector<ll> (LOG+1,0));
    ll parent[n+1];
    parent[0]=parent[1]=0;
    for (int i=2;i<=n;i++)cin>>parent[i];

    for (int i=1;i<=n;i++){
        up[i][0]=parent[i];
        for (int j=1;j<LOG;j++){
            up[i][j]=up[up[i][j-1]][j-1];
        }
    }
    // cout<<(1<<LOG)<<endl;
    while (q--){
        ll x,k;
        cin>>x>>k;
        for (int j=LOG;j>=0;j--){
            if (k&(1<<j))x=up[x][j];
        }
        cout<<(x==0?-1:x)<<endl;
    }
}