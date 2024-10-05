vector <ll> Seg, arr;
 
void build(ll index, ll start , ll end){
    if (start==end){
        Seg[index]=arr[start];
        return;
    }
    ll mid = (start+end)/2;
    build(2*index+1,start,mid);
    build(2*index+2,mid+1,end);
    Seg[index]=Seg[2*index+1]+Seg[2*index+2];
    return;
}
 
void update (ll index, ll idx, ll val, ll start , ll end){
    if (start==end){
        Seg[index]=val;
        return;
    }
    ll mid = (start+end)/2;
    if (idx<=mid)update(2*index+1,idx,val,start,mid);
    else update(2*index+2,idx,val,mid+1,end);
    
    Seg[index]=Seg[2*index+1]+Seg[2*index+2];
}
 
ll query (ll index, ll start, ll end, ll l ,ll r){
    if (end<l || start>r)return 0;
    if (start>=l && end<=r)return Seg[index];
    ll mid = (start+end)/2;
    ll left=query(2*index+1,start,mid,l,r);
    ll right=query(2*index+2,mid+1,end,l,r);
    return left+right;
}

