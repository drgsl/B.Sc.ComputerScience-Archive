#include <8051.h>

char var;
char c1, c2, c3, c4;
char i;
char last;

int main()
{
    c1 = 12, c2 = 12, c3 = 12, c4 = 12;
    last = 0;

    // partea de citire
    while (c1 == 12 || c2 == 12 || c3 == 12 || c4 == 12)
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
    }

    //aici trb transformat din 4 cifre in doua numere pe 8 biti fiecare

    TH0 = 0b00000011;
    TL0 = 0b11101000;
    TMOD = 1;
    var = 1;

    while (1)
    {
        P1 = ~var;
        TR0 = 1;
        while (TF0 == 0)
        {
            // waiting
        }
        TR0 = 0;
        TF0 = 0;
        TH0 = 0b00000011;
        TL0 = 0b11101000;
        var = var << 1;
        if (var == 0)
        {
            var = 1;
        }
    }
}