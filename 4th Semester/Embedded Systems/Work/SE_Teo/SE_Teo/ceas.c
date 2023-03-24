#include <8051.h>

volatile char var;

void timer0(void) __interrupt 1
{
    TH0 = 0b00000011;
    TL0 = 0b11101000;
    var = var << 1;
    if (var == 0)
    {
        var = 1;
    }
    P1 = ~var;
    if (P3 == 1)
    {
        P3 = 2;
    }
    else
    {
        P3 = 1;
    }
}

int main()
{
    TH0 = 0b00000011;
    TL0 = 0b11101000;
    TMOD = 1;

    ET0 = 1;
    EA = 1;

    var = 1;
    P1 = ~var;
    TR0 = 1;
    P3 = 1;

    while (1)
    {
    }
}