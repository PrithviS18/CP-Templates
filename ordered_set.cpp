#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
using namespace std;




/*long long gcd(long long a,long long b){
     if (a == 0)
         return b;
     return gcd(b % a, a); 
}*/
template<
        //find_by_order(k) -> this function returns and iterator to the kth largest element (counting from zero)
        //order_of_key(k) -> this function returns the number of items that are lesser than the given value k
        typename Key, // Key type
        typename Mapped, // Mapped-policy
        typename Cmp_Fn = less<Key>, // Key comparison functor
        typename Tag = rb_tree_tag, // Specifies which underlying data structure to use
        template<
        typename Const_Node_Iterator,
        typename Node_Iterator,
        typename Cmp_Fn_,
        typename Allocator_>
        class Node_Update = null_node_update, // A policy for updating node invariants
        typename Allocator = allocator<char> > // An allocator type
using ordered_set_tree=tree<Key,Mapped,Cmp_Fn,Tag,Node_Update,Allocator>;
typedef ordered_set_tree<long long,null_type,less<long long>,rb_tree_tag,tree_order_statistics_node_update>ordered_set;

        //find_by_order(k) -> this function returns and iterator to the kth largest element (counting from zero)

        //order_of_key(k) -> this function returns the number of items that are lesser than the given value k
        // ordered_set st;
        // long long sum=0;
        // for (int i=0;i<n;i++){
        //         if (st.size()!=0){
        //                 sum+=(long long)(st.size()-st.order_of_key(vec[i].second));
        //         }
        //         st.insert(vec[i].second);
        // }
void solve(){
        ll n,q;
        cin>>n>>q;  
}


int main(){
        ll t;
        cin>>t;
        while (t--){
                solve();
        }
}
