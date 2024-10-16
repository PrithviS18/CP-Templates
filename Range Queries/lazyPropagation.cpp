ll Seg[4*maxN], lazy[4*maxN];

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

ll query (ll index, ll start, ll end, ll l ,ll r){
    if (lazy[index]!=0){
        ll dx = lazy[index];
        lazy[index]=0;
        Seg[index]+= dx * (end-start+1);

        if (start!=end){
            lazy[2*index+1]=dx;
            lazy[2*index+2]=dx;
        }
    }

    if (end<l || start>r)return 0;
    if (start>=l && end<=r)return Seg[index];

    ll mid = (start+end)/2;
    ll left=query(2*index+1,start,mid,l,r);
    ll right=query(2*index+2,mid+1,end,l,r);

    return left+right;
}

void update (ll index,ll start , ll end, ll l ,ll r, ll val){
   if (lazy[index]!=0){
        ll dx = lazy[index];
        lazy[index]=0;
        Seg[index]+= dx * (end-start+1);

        if (start!=end){
            lazy[2*index+1]=dx;
            lazy[2*index+2]=dx;
        }
    }

    if (end<l || start>r)return 0;

    if (start>=l && end<=r){
        ll dx = (end-start+1)*val;
        Seg[index]+=dx;

        if (start!=end){
            lazy[2*index+1]+=val;
            lazy[2*index+2]+=val;
            return;
        }
    }
    ll mid = (start+end)/2;
    update(2*index+1,start,mid,l,r,val);
    update(2*index+2,mid+1,end,l,r,val);
    
    Seg[index]=Seg[2*index+1]+Seg[2*index+2];
}