#include <8051.h>

char var;
char c1, c2, c3;
char currentC;
char i;
char k;

int main()
{
    var = 234;
    c1 = var % 10;
    c2 = (var / 10) % 10;
    c3 = (var / 100);

    while (1)
    {
        for (i = 0; i < 3; i++)
        {
            P0_7 = 0;

            if (i == 0) // display 0
            {
                P3_3 = 0;
                P3_4 = 1;
                currentC = c3;
            }
            else if (i == 1) // display 1
            {
                P3_3 = 1;
                P3_4 = 0;
                currentC = c2;
            }
            else if (i == 2) // display 2
            {
                P3_3 = 0;
                P3_4 = 0;
                currentC = c1;
            }

            if (currentC == 0) // 0
            {
                P1 = 0b11000000;
            }
            else if (currentC == 1) // 1
            {
                P1 = 0b11111001;
            }
            else if (currentC == 2) // 2
            {
                P1 = 0b10100100;
            }
            else if (currentC == 3) // 3
            {
                P1 = 0b10110000;
            }
            else if (currentC == 4) // 4
            {
                P1 = 0b10011001;
            }
            else if (currentC == 5) // 5
            {
                P1 = 0b10010010;
            }
            else if (currentC == 6) // 6
            {
                P1 = 0b10000010;
            }
            else if (currentC == 7) // 7
            {
                P1 = 0b11111000;
            }
            else if (currentC == 8) // 8
            {
                P1 = 0b10000000;
            }
            else // 9
            {
                P1 = 0b10011000;
            }

            P0_7 = 1;

            for(k=0; k<100; k++)
            {
                
            }
        }
    }
}