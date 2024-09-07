// 2维平面上有一些点
// 从左上角走到右下角，只允许向右或者下走
// 尽可能经过多的点

#include<algorithm>
#include<iostream>
#include<vector>

const int maxn = 2e5 + 1;

struct node
{
    int r,c;
    bool operator<(const node& other) const
    {
        if(r == other.r) return c < other.c;
        return r < other.r;
    }

    void move(const node& other)
    {
        // std::cout << "move" << r << "," << c << " to " << other.r << "," << other.c << std::endl;

        for(; r<other.r; r+=1) std::cout << 'D';
        for(; c<other.c; c+=1) std::cout << 'R';
        // std::cout << std::endl;
    }
};

int lis_ai(int numbers_count, int* numbers, std::vector<int>& lis_index, bool allow_equal = true)
{
    if (numbers_count == 0) return 0;

    std::vector<int> tails(numbers_count, 0);  // 存储最小的结尾元素
    std::vector<int> prev(numbers_count, -1);  // 存储前驱元素的索引
    int length = 0;

    for (int i = 0; i < numbers_count; ++i)
    {
        // 选择upper_bound或lower_bound来确定插入位置
        auto it = allow_equal ? std::upper_bound(tails.begin(), tails.begin() + length, numbers[i])
                              : std::lower_bound(tails.begin(), tails.begin() + length, numbers[i]);

        int index = it - tails.begin();
        tails[index] = numbers[i];
        // 记录前驱元素的索引
        if (index > 0) {
            prev[i] = lis_index[index - 1];
        }
        // 更新当前元素的索引在lis_index中的位置
        if (index == length) {
            lis_index.push_back(i);
            length++;
        } else {
            lis_index[index] = i;
        }
    }

    // 根据prev数组回溯LIS
    for (int i = lis_index[length - 1]; i >= 0; i = prev[i]) {
        lis_index[length - 1] = i;
        length--;
    }

    return lis_index.size();  // 返回LIS的长度
}

int h,w,n,data[maxn];
std::vector<node> nodes;

int main()
{
    std::cin >> h >> w >> n;

    int r,c;
    for(int i=1; i<=n; i+=1)
    {
        std::cin >> r >> c;
        nodes.push_back((node){r,c});
    }
    std::sort(nodes.begin(),nodes.end());

    int index = 0;
    for(auto i=nodes.begin(); i!=nodes.end(); i++)
    {
        data[index++] = i->c;
    }

    std::vector<int> lis_index;
    std::cout << lis_ai(n,data,lis_index) << std::endl;

    node start = (node){1,1};
    for(auto i=lis_index.begin(); i!=lis_index.end(); i++)
    {
        start.move(nodes[*i]);
    }
    start.move((node){h,w});
    std::cout << std::endl;

    return 0;
}