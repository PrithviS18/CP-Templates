class TrieNode {
public:
    TrieNode* children[2];
    int maxx;

    TrieNode (){
        children[0]=children[1]=nullptr;
        maxx=-1;
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie(){
        root = new TrieNode();
    }

    void insert(ll val, int i){
        TrieNode* node = root;
        ll power = 1073741824;
        while (power!=0){
            int index;
            ((val&power)==0?index=0:index=1);
            if (!node->children[index]){
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
            node->maxx = max(node->maxx,i);
            power/=2;
        }
    }

    int nearestIndex (ll val, ll k){
        TrieNode * node = root;
        ll power = 1073741824;
        int ans = -1;
        while(power!=0 && node!=nullptr){
            ll ind,ind1;
            ((val&power)==0?ind=0:ind=1);
            ((k&power)==0?ind1=0:ind1=1);
            // cout<<ind<<" "<<ind1<<endl;
            if (ind==1 && ind1==1){
                node = node->children[0];
                if (power==1 && node!=nullptr)ans=max(ans,node->maxx);
            }
            else if (ind==0 && ind1==0){
                if (node->children[1]!=nullptr)ans=max(ans,node->children[1]->maxx);
                node = node->children[0];
                if (power==1 && node!=nullptr)ans=max(ans,node->maxx);
            }
            else if (ind==0 && ind1==1){
                node = node->children[1];
                if (power==1 && node!=nullptr)ans=max(ans,node->maxx);
            }
            else {
                if (node->children[0]!=nullptr)ans=max(ans,node->children[0]->maxx);
                node = node->children[1];
                if (power==1 && node!=nullptr)ans=max(ans,node->maxx);
            }
            power/=2;
        }
        return ans;
    }  
};

void solve(int t) {
    ll n,k;
    cin>>n>>k;
    ll arr[n];
    for (int i=0;i<n;i++)cin>>arr[i];
    if (k==0){
        cout<<1<<endl;
        return;
    }
    Trie trie;
    int ans=INT_MAX;
    for (int i=0;i<n;i++){
        if (i==0)trie.insert(arr[i],i);
        else{
            int val = trie.nearestIndex(arr[i],k);
            // cout<<val<<" ";
            if (val!=-1)ans=min(ans,i-val+1);
            trie.insert(arr[i],i);
        }
    }
    (ans==INT_MAX?cout<<-1<<endl:cout<<ans<<endl);
}