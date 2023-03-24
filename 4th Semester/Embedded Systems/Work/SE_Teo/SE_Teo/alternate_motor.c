#include <8051.h>

int main()
{
    while (1)
    {
        P3 = 1;
        for (char c = 'a'; c < 'd'; c++)
        {
        }
        P3 = 2;
        for (char c = 'a'; c < 'd'; c++)
        {
        }
    }
}