#include <8051.h>
int main()
{
    while(1){
        if(P2_0 == 0)
            P1 = 0xC0;
}
}

