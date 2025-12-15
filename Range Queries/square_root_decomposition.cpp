void solve(int g) {
    int n;
    cin>>n;
    int arr[n];

    int len = sqrtl(n); //size of each block
    vector<ll> b(len+1); //no. of blocks = len + 1
    
    //Pre-processing
    for (int i=0;i<n;i++){
        cin>>arr[i];
        b[i/len]+=arr[i];
    }

    int queries,l,r;
    cin>>queries;

    for (int i=0;i<queries;i++){
        cin>>l>>r;
        int sum=0;    
        for (int i=l;i<=r;){
            //the whole block lies in the range [l,r]
            if (i%len==0 && i+len-1<=r){
                sum+=b[i/len]; //using preprocessed block values
                i+=len;
            }
            else sum+=arr[i],i++; //block doesn't lies fully in range [l,r]
        }
        cout<<sum<<endl;
    }
}