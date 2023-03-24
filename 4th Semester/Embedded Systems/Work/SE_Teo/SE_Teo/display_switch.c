#include <8051.h>

char var;
char i;

int main()
{
    var = 0;
    while (1)
    {
        if (P2_0 == 0) // 0
        {
            P1 = 0b11000000;
        }
        else if (P2_1 == 0) // 1
        {
            P1 = 0b11111001;
        }
        else if (P2_2 == 0) // 2
        {
            P1 = 0b10100100;
        }
        else if (P2_3 == 0) // 3
        {
            P1 = 0b10110000;
        }
        else if (P2_4 == 0) // 4
        {
            P1 = 0b10011001;
        }
        else if (P2_5 == 0) // 5
        {
            P1 = 0b10010010;
        }
        else if (P2_6 == 0) // 6
        {
            P1 = 0b10000010;
        }
        else if (P2_7 == 0) // 7
        {
            P1 = 0b11111000;
        }
        else // 8
        {
            P1 = 0b10000000;
        }

        if (var == 0)
        {
            P3_3 = 0;
            P3_4 = 0;
            var = 1;
            for (i = 0; i < 100; i++)
            {
            }
        }
        else if (var == 1)
        {
            P3_3 = 1;
            P3_4 = 0;
            var = 2;
            for (i = 0; i < 100; i++)
            {
            }
        }
        else if (var == 2)
        {
            P3_3 = 0;
            P3_4 = 1;
            var = 3;
            for (i = 0; i < 100; i++)
            {
            }
        }
        else if (var == 3)
        {
            P3_3 = 1;
            P3_4 = 1;
            var = 0;
            for (i = 0; i < 100; i++)
            {
            }
        }
    }
}