#include <8051.h>

int main()
{
    char var;
    var = 1;
    while (1)
    {
        switch (var)
        {
        case 1:
            P1 = 0b10100100;
            P3_3 = 0;
            P3_4 = 0;
            var=2;
            for (char i = 1; i < 5; i++)
            {
            }
            break;
        case 2:
            P1 = 0b10100100;
            P3_3 = 1;
            P3_4 = 0;
            var=3;
            for (char i = 1; i < 5; i++)
            {
            }
            break;
        case 3:
            P1 = 0b10100100;
            P3_3 = 0;
            P3_4 = 1;
            var=4;
            for (char i = 1; i < 5; i++)
            {
            }
            break;
        case 4:
            P1 = 0b10100100;
            P3_3 = 1;
            P3_4 = 1;
            var=1;
            for (char i = 1; i < 5; i++)
            {
            }
            break;
        }
    }
}