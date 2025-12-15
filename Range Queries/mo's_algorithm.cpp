int rootN;

struct Query {
    int l,r,ind;
};


bool compare (Query a, Query b){
    // if lefts lie within same block sort w.r.t right
    if (a.l/rootN == b.l/rootN){
        return a.r/rootN < b.r/rootN;
    }
    // else sort w.r.t left
    return a.l/rootN < b.l/rootN;
}

void remove(int idx){}
void add(int idx){}

void solve(int g) {
    int n;
    cin>>n;
    int arr[n];

    rootN = sqrtl(n);

    int queries,l,r;
    cin>>queries;

    vector<Query> q (queries);

    for (int i=0;i<queries;i++){
        cin>>l>>r;
        q[i].l=l,q[i].r=r,q[i].ind=i;    
    }

    sort (q.begin(),q.end(),compare);

    //MO's algorithm
    int cur_L = 0,cur_R=-1;
    for (int i=0;i<queries;i++){
        while (cur_L > q[i].l){
            cur_L--;
            remove(cur_L);
        }
        while (cur_R < q[i].r){
            cur_R++;
            add(cur_R);
        }
        while (cur_L < q[i].l){
            remove(cur_L);
            cur_L++;
        }
        while (cur_R>q[i].r){
            remove(cur_R);
            cur_R--;
        }
    }
}