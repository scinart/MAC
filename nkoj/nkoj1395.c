#include <stdio.h>

int main()
{
    int sum;
    char c;
    int i;
    while(1)
    {
        sum=0;
        i=0;
        while(1)
        {
            c=getchar();
            if (c=='#')
                  return 0;
            else if (c == '\n')
            {
                  printf("%d\n", sum);
                  break;
            }
            else if (c == ' ')
            {
                  i++;
            }
            else
            {
                  i++;
                  sum+=i*(c-'@');
            }
        }
    }
}
