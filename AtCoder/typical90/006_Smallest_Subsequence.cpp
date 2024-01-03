#include<algorithm>
#include<cstdio>
#include<cstdint>
#include<unordered_map>
#include<vector>

const int maxn=100000+10;

char s[maxn];
int n,k;

// next数组和贪心算法
int main()
{
    scanf("%d %d",&n,&k);
    scanf("%s",s+1);

    std::unordered_map<char,int> next[maxn];

    for(int i=n;i>=1;i-=1)
    {
        for(int j='a';j<='z';j+=1)
        {
            if(next[0].count(j))
            {
                next[i][j]=next[0][j];
            }else
            {
                next[i][j]=-1;
            }
        }
        next[0][s[i]]=i;
    }

    /*
    for(int i=0;i<=n;i+=1)
    {
        printf("next %d:",i);
        for(int j='a';j<='z';j+=1)
        {
            if(next[i].count(j) && next[i][j]!=-1)
            printf("%c->%d,",j,next[i].count(j)?next[i][j]:0);
        }
        puts("");
    }
    */
    
    std::vector<char> ans;
    int left=0;
    for(int i=1;i<=k;i+=1)
    {
        for(int j='a';j<='z';j+=1)
        {
            if(next[left].count(j)&&next[left][j]!=-1&&(n-next[left][j]>=k-i))
            {
                ans.push_back(j);
                left=next[left][j];
                break;
            }
        }
    }

    for(int i=0;i<ans.size();i+=1) printf("%c",ans[i]); puts("");

    return 0;
}

int main_1()
{
    std::unordered_map<char,std::vector<int> > cache;

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