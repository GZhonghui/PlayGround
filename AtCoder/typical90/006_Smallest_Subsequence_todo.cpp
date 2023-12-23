#include<algorithm>
#include<cstdio>
#include<cstdint>
#include<unordered_map>
#include<vector>

const int maxn=100000+10;

char s[maxn];
int n,k;

std::unordered_map<char,std::vector<int> > cache;

// next数组和贪心算法
int main()
{
    scanf("%d %d",&n,&k);
    scanf("%s",s+1);

    std::unordered_map<char,int> pos;

    for(int i=n;i>=1;i-=1)
    {
        
    }

    return 0;
}

int main_1()
{
    scanf("%d %d",&n,&k);
    scanf("%s",s+1);

    for(char i='a';i<='z';i+=1)
    {
        cache[i]=std::vector<int>();
    }

    for(int i=1;i<=n;i+=1)
    {
        char x=s[i];
        cache[x].push_back(i);
    }

    std::vector<char> ans;
    std::unordered_map<char,int> index;
    int now_end=0;

    for(int i='a';i<='z';i+=1)
    {
        index[i]=0;
    }

    again:;
    for(char i='a';i<='z';i+=1)
    {
        const std::vector<int>& orders=cache[i];
        /*
        for(auto j=orders.begin();j!=orders.end();++j)
        {
            if(*j>now_end&&ans.size()<k&&(n-*j>=k-ans.size()-1))
            {
                ans.push_back(i);
                now_end=*j;
                goto again;
            }
        }
        */

       // bool found=false;
       for(int j=index[i];j<orders.size();j+=1)
       {
            if(orders[j]<=now_end)
            {
                index[i]+=1;
                continue;
            }

            if(n-orders[j]>=k-ans.size()-1)
            {
                ans.push_back(i);
                now_end=orders[j];
                index[i]+=1;

                // found=true;
                goto again;
            }// else break;
       }
       // if(found) goto again;
    }

    for(int i=0;i<k;i+=1)
    {
        printf("%c",ans[i]);
    }
    puts("");

    return 0;
}