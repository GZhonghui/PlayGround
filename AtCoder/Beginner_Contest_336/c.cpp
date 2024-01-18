#include<cstdio>
#include<algorithm>
#include<cstdint>
#include<stack>

int main()
{
    std::stack<int> ans;

    int64_t n;
    scanf("%lld",&n);

    if(n==1) {puts("0"); return 0;}

    n-=1;
    while(n)
    {
        ans.push(n%5);
        n=n/5;
    }

    while(!ans.empty())
    {
        printf("%d",ans.top()*2);
        ans.pop();
    }
    puts("");

    return 0;
}