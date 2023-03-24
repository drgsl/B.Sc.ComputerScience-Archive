#include <8051.h>

int main()
{
    char currentC;
    char c1, c2, c3, c4;
    char last;
    last = 0;
    c1 = 12, c2 = 12, c3 = 12, c4 = 12;
    char i, k;
    while (1)
    {
        currentC = 12;
        for (i = 0; i < 4; i++)
        {
            if (i == 0)
            {
                P0_0 = 0;
                P0_1 = 1;
                P0_2 = 1;
                P0_3 = 1;
                if (P0_4 == 0) // #
                {
                    currentC = 11;
                }
                else if (P0_5 == 0) // 0
                {
                    currentC = 0;
                }
                else if (P0_6 == 0) // *
                {
                    currentC = 10;
                }
            }
            else if (i == 1)
            {
                P0_0 = 1;
                P0_1 = 0;
                P0_2 = 1;
                P0_3 = 1;
                if (P0_4 == 0) // 9
                {
                    currentC = 9;
                }
                else if (P0_5 == 0) // 8
                {
                    currentC = 8;
                }
                else if (P0_6 == 0) // 7
                {
                    currentC = 7;
                }
            }
            else if (i == 2)
            {
                P0_0 = 1;
                P0_1 = 1;
                P0_2 = 0;
                P0_3 = 1;
                if (P0_4 == 0) // 6
                {
                    currentC = 6;
                }
                else if (P0_5 == 0) // 5
                {
                    currentC = 5;
                }
                else if (P0_6 == 0) // 4
                {
                    currentC = 4;
                }
            }
            else if (i == 3)
            {
                P0_0 = 1;
                P0_1 = 1;
                P0_2 = 1;
                P0_3 = 0;
                if (P0_4 == 0) // 3
                {
                    currentC = 3;
                }
                else if (P0_5 == 0) // 2
                {
                    currentC = 2;
                }
                else if (P0_6 == 0) // 1
                {
                    currentC = 1;
                }
            }
        }

        if (currentC != 12) // apasat
        {
            if (last == 0)
            {
                if (c1 == 12)
                {
                    c1 = currentC;
                }
                else if (c2 == 12)
                {
                    c2 = currentC;
                }
                else if (c3 == 12)
                {
                    c3 = currentC;
                }
                else if (c4 == 12)
                {
                    c4 = currentC;
                }
            }
            last = 1;
        }
        else
        {
            last = 0;
        }

        for (i = 0; i < 4; i++)
        {
            P0_7 = 0;

            if (i == 0) // c1
            {
                P3_3 = 1;
                P3_4 = 1;
                currentC = c1;
            }
            else if (i == 1) // c2
            {
                P3_3 = 0;
                P3_4 = 1;
                currentC = c2;
            }
            else if (i == 2) // c3
            {
                P3_3 = 1;
                P3_4 = 0;
                currentC = c3;
            }
            else // c4
            {
                P3_3 = 0;
                P3_4 = 0;
                currentC = c4;
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
            else if (currentC == 9) // 9
            {
                P1 = 0b10010000;
            }
            else if (currentC == 10) // *
            {
                P1 = 0b10111111;
            }
            else if (currentC == 11) // #
            {
                P1 = 0b11110110;
            }
            else // nimic
            {
                P1 = 0b11111111;
            }

            P0_7 = 1;
            for (k = 0; k < 100; k++)
            {
            }
        }
    }
}