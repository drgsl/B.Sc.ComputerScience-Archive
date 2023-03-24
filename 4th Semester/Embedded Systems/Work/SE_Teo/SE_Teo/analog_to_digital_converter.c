#include <8051.h>

char value;
char n1, n2;
char i;
char contor;
char k;

int main()
{
    while (1)
    {
        // get the analog_to_digital convertion
        P3_6 = 0;
        P3_6 = 1;
        while (P3_2 == 1)
        {
            // waiting
        }
        P3_7 = 0;

        value = P2;

        P3_7 = 1;

        // calculate the display number
        if (value < 51)
        {
            n1 = 0;
            contor = 0;
            for (i = 1; i <= 50; i += 5)
            {
                contor++;
                if (value < i + 1)
                {
                    n2 = contor - 1;
                    break;
                }
            }
        }
        else if (value < 102)
        {
            n1 = 1;
            contor = 0;
            for (i = 1; i <= 50; i += 5)
            {
                contor++;
                if (value < i + 52)
                {
                    n2 = contor - 1;
                    break;
                }
            }
        }
        else if (value < 153)
        {
            n1 = 2;
            contor = 0;
            for (i = 1; i <= 50; i += 5)
            {
                contor++;
                if (value < i + 103)
                {
                    n2 = contor - 1;
                    break;
                }
            }
        }
        else if (value < 204)
        {
            n1 = 3;
            contor = 0;
            for (i = 1; i <= 50; i += 5)
            {
                contor++;
                if (value < i + 154)
                {
                    n2 = contor - 1;
                    break;
                }
            }
        }
        else if (value < 255)
        {
            n1 = 4;
            contor = 0;
            for (i = 1; i <= 50; i += 5)
            {
                contor++;
                if (value < i + 205)
                {
                    n2 = contor - 1;
                    break;
                }
            }
        }
        else
        {
            n1 = 5;
            n2 = 0;
        }

        // display 1 (partea intreaga)

        P3_3 = 1;
        P3_4 = 1;

        if (n1 == 0) // 0
        {
            P1 = 0b01000000;
        }
        else if (n1 == 1) // 1
        {
            P1 = 0b01111001;
        }
        else if (n1 == 2) // 2
        {
            P1 = 0b00100100;
        }
        else if (n1 == 3) // 3
        {
            P1 = 0b00110000;
        }
        else if (n1 == 4) // 4
        {
            P1 = 0b00011001;
        }
        else if (n1 == 5) // 5
        {
            P1 = 0b00010010;
        }


        P0_7 = 1;

        for (k = 0; k < 100; k++)
        {
        }
        
        P0_7 = 0;

        // display 1 (partea zecimala)

        P3_3 = 0;
        P3_4 = 1;

        if (n2 == 0) // 0
        {
            P1 = 0b11000000;
        }
        else if (n2 == 1) // 1
        {
            P1 = 0b11111001;
        }
        else if (n2 == 2) // 2
        {
            P1 = 0b10100100;
        }
        else if (n2 == 3) // 3
        {
            P1 = 0b10110000;
        }
        else if (n2 == 4) // 4
        {
            P1 = 0b10011001;
        }
        else if (n2 == 5) // 5
        {
            P1 = 0b10010010;
        }
        else if (n2 == 6) // 6
        {
            P1 = 0b10000010;
        }
        else if (n2 == 7) // 7
        {
            P1 = 0b11111000;
        }
        else if (n2 == 8) // 8
        {
            P1 = 0b10000000;
        }
        else // 9
        {
            P1 = 0b10010000;
        }

        P0_7 = 1;
        
        for (k = 0; k < 100; k++)
        {
        }

        P0_7 = 0;
    }
}