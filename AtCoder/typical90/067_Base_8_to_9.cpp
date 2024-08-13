#include<algorithm>
#include<cstdio>
#include<cstdint>
#include<cstring>

const int max_length = 32;

char n[max_length];

inline void step()
{
    int length = strlen(n);
    char _temp[max_length];
    uint64_t data = 0;

    for(int i=0;i<length;i+=1)
    {
        data *= 8;
        data += n[i] -'0';
    }

    int index = 0;
    while(data)
    {
        _temp[index++] = (data % 9) + '0';
        data /= 9;
    }

    if(index == 0)
    {
        _temp[0] = '0';
        index = 1;
    }

    for(int i=0;i<index;i+=1)
    {
        n[i] = _temp[index - i - 1];
        if(n[i] == '8') n[i] = '5';
    }
    n[index] = (char)0;
}

int main()
{
    int k;
    scanf("%s %d",n,&k);
    while(k--) step();
    puts(n);

    return 0;
}