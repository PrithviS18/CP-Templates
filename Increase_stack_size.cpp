/*JOY MAA DURGA*/

#include<bits/stdc++.h> 

using namespace std;

typedef long long ll;

static void run_with_stack_size(void (*func)(void), size_t stsize) {
    char *stack, *send;
    stack = (char *)malloc(stsize);
    send = stack + stsize - 16;
    send = (char *)((uintptr_t)send / 16 * 16);
    asm volatile(
        "mov %%esp, (%0)\n"
        "mov %0, %%esp\n"
        :
        : "r"(send));
    func();
    asm volatile("mov (%0), %%esp\n" : : "r"(send));
    free(stack);
}
void solve( ) {
    
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    int t=1;
    cin >> t;
    for (int i=1;i<=t;i++){
        cout<<"Case #"<<i<<": ";
        run_with_stack_size(solve, 1024 * 1024 * 1024);
    }
}


//for 64 bit compiler use %%rsp
