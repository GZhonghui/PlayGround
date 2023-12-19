#include<algorithm>
#include<cstdio>
#include<cstdint>
#include<cstring>
#include<unordered_map>

const int64_t maxn=100000+10;
const int64_t mod=1e9+7;

char s[maxn];
int64_t dp[maxn];

inline char prev(char x)
{
    if(x=='t') return 'a';
    if(x=='c') return 't';
    if(x=='o') return 'c';
    if(x=='d') return 'o';
    if(x=='e') return 'd';
    if(x=='r') return 'e';

    return 0;
}

int main()
{
    int64_t n;scanf("%lld %s",&n,s+1);

    int64_t ans=0;
    std::unordered_map<char,int64_t> mem;

    for(int64_t i=1;i<=n;i+=1)
    {
        dp[i]=0;
        if(s[i]=='a')
        {
            dp[i]=1;
            if(!mem.count('a')) mem['a']=0;
            mem['a']=(mem['a']+1)%mod;

            continue;;
        }

        char prev_c=prev(s[i]);
        if(!prev_c) continue;

        /*
        for(int64_t j=1;j<i;j+=1)
        {
            if(s[j]==prev_c)
            {
                dp[i]=(dp[i]+dp[j])%mod;
            }
        }
        */

       if(!mem.count(prev_c)) mem[prev_c]=0;
       dp[i]=mem[prev_c]%mod;

        if(!mem.count(s[i])) mem[s[i]]=0;
        mem[s[i]]=(mem[s[i]]+dp[i])%mod;
    }

    for(int64_t i=1;i<=n;i+=1)
    {
        if(s[i]=='r') ans=(ans+dp[i])%mod;
    }

    printf("%lld\n",ans);

    return 0;
}