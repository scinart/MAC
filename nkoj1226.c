/*nkoj1226*/

#include <stdio.h>
#include <math.h>
/* input N
 * output \lfloor \sqrt{N} \rfloor
 */
int main()
{
    int N=-1;
    while(1)
    {
        scanf(" %d", &N);
        if(N)
        {
            printf("%d\n", (int)floor(sqrt(N)));
        }
        else
            break;
    }
    return 0;
}
