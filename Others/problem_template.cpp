#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
        int kEmptySlots(vector<int>& bulbs, int k) {
            int n = bulbs.size();
            vector<int> on(n,0);
    
            int ans = INT_MAX;
            for (int i=0;i<n;i++){
                on[bulbs[i]-1]=1;
                int one=0,count=0;
                for (int j=0;j<n;j++){
                    if (on[j]==1){
                        if (one>0 && count==k){
                            ans=(i+1);
                            break;
                        }
                        count=0,one++;
                    }
                    else {
                        count++;
                    }
                }
                if (ans != INT_MAX){
                    break;
                }
            }
            if (ans == INT_MAX){
                return -1;
            }
            return ans;
        }
    };


int main() {
    // outFile << testCases << endl;
    Solution solution;
    vector<int> bulbs = {6,2,11,10,9,3,19,1,7,5,15,13,12,18,8,17,16,4,14};
    int k=0;
        
    int result = solution.kEmptySlots(bulbs,k);
    cout << result << endl;
    
    return 0;
}
