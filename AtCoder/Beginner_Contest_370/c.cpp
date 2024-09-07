#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cstring>

const int max_len = 128;

char s[max_len],t[max_len];

int main()
{
    scanf("%s %s",s,t);
    if(strcmp(s,t) == 0)
    {
        printf("0\n");
        return 0;
    }

    int len = strlen(s), ans = 0;
    for(int i = 0; i < len; i += 1)
    {
        if(s[i] != t[i])
        {
            ans += 1;
        }
    }

    printf("%d\n",ans);
    for(int j = 0; j < ans; j += 1)
    {
        // char min_target;
        // int min_target_index = -1;

        int update_index = 0;

        for(int i = 0; i < len; i += 1)
        {
            if(s[i] != t[i])
            {
                if(s[i] > t[i])
                {
                    update_index = i;
                    break;
                }
                if(s[i] < t[i])
                {
                    update_index = i;
                }
                /*
                if(min_target_index == -1 || t[i] < min_target)
                {
                    min_target_index = i;
                    min_target = t[i];
                }
                */
            }
        }
        s[update_index] = t[update_index];
        printf("%s\n",s);
    }

    return 0;
}