#include<algorithm>
#include<cstdio>
#include<cstring>
#include<ctime>

// RE是因为递归爆栈了

// 这种题目要加强训练
// 问题：搜索没办法解决依赖关系
// 思考：什么样子的问题不能用DFS
// TODO：问题已经确认并且证明了，接下来思考一下BFS的解法，官方提供了另一种基于图的解法

const int max_size = 1e3+10;
const int inf = 1e9;
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

int h, w, memory[max_size][max_size][4], done[max_size][max_size];
char map[max_size][max_size];

struct Status
{
    int x,y,forward;
}start, target;

int search(Status status, bool allow_rotate = false)
{
    // if(done[status.x][status.y]) return inf;
    done[status.x][status.y] = 1;
    // printf("Search: (%d, %d, %d)\n",status.x,status.y,status.forward);

    // check
    if(!(1 <= status.x && status.x <= h && 1 <= status.y && status.y <= w && 
        0 <= status.forward && status.forward <= 3))
    {
        // printf("Error: (%d, %d, %d)\n",status.x,status.y,status.forward);
    }

    if(memory[status.x][status.y][status.forward]!=-1)
    {
        return memory[status.x][status.y][status.forward];
    }

    int ans = inf;
    int* p_ans = &memory[status.x][status.y][status.forward];

    if(status.x == start.x && status.y == start.y)
    {
        ans = 0;
    }else
    {
        int back_x = status.x + dx[status.forward];
        int back_y = status.y + dy[status.forward];

        // !done[back_x][back_y]：排除部分情况，可能会导致无法得到最优解
        if(1 <= back_x && back_x <= h && 1 <= back_y && back_y <= w && map[back_x][back_y]=='.' && !done[back_x][back_y])
        {
            ans = std::min(ans, search((Status){back_x,back_y,status.forward},true));
        }

        if(allow_rotate)
        {
            status.forward = (status.forward + 1) % 4;
            ans = std::min(ans, search(status, false) + 1);
            status.forward = (status.forward + 2) % 4;
            ans = std::min(ans, search(status, false) + 1);
            // status.forward = (status.forward + 3) % 4;
            // ans = std::min(ans, search(status, false) + 2);
        }
    }

    done[status.x][status.y] = 0;
    return *p_ans = ans;
}

inline void test()
{
    srand((unsigned)time(nullptr));

    for(int i=1;i<=1000;i+=1)
    {
        for(int j=1;j<=1000;j+=1)
        {
            printf("%c",(rand()%2 || std::abs(i-j)<=1)?'.':'#');
        }
        puts("");
    }
}

int main()
{
    // test(); return 0;

    memset(memory,-1,sizeof(memory));
    memset(done,0,sizeof(done));

    scanf("%d %d",&h,&w);

    scanf("%d %d",&start.x,&start.y);
    scanf("%d %d",&target.x,&target.y);

    for(int i=1;i<=h;i+=1)
    {
        scanf("%s",map[i] + 1);
    }

    int ans = inf;
    for(int i=0;i<4;i+=1)
    {
        ans = std::min(ans, search((Status){target.x,target.y,i}));
    }
    printf("%d\n",ans);

    return 0;
}