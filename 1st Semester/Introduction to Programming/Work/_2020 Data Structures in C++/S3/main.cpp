#include <iostream>
#include <cstring>
using namespace std;

///exercitii simple cu structuri reprezentand tablouri
///(S2)

struct vector
{
    unsigned int nrElemente;
    int element[200];
};

bool esteOrdonat(vector v)
{

    int prec = v.element[0];

    for(int i = 1; i<= v.nrElemente; i++)
    {
        if(v.element[i] < prec)
            return false;
        prec = v.element[i];
    }
    return true;

}


/// 3.5.2

struct complex
{
    int re;
    int im;
};

complex add(complex z1, complex z2)
{
    complex z3;
    z3.re = z1.re + z2.re;
    z3.im = z1.im + z2.im;
    return z3;
}

complex subtract(complex z1, complex z2)
{
    complex z3;
    z3.re = z1.re - z2.re;
    z3.im = z1.im - z2.im;
    return z3;
}

complex multiply(complex z1, complex z2)
{
    complex z3;
    z3.re = z1.re * z2.re - z1.im * z2.im;
    z3.im = z1.re * z2.im + z1.im * z2.re;
    return z3;
}

complex divide(complex z1, complex z2)
{
    complex z3;
    z3.re = z1.re * z2.re + z1.im * z2.im;
    z3.re/= z2.re * z2.re + z2.im * z2.im;

    z3.im = z1.im * z2.re - z1.re * z2.im;
    z3.im/= z2.re * z2.re + z2.im * z2.im;
    return z3;
}

/// 3.5.1
char possibleSymbols[] = "CDHS";

struct Card
{
    char Number;
    char Symbol;
};
Card Deck[52];

void initDeck()
{
    for(int j = 0; j<= 3; j++)
    {
        char activeSymbol = possibleSymbols[j];

        for(int i = 1; i<=13; i++)
        {
            int ind = i + j * 13;
            if(i == 1)
                Deck[ind].Number = 'A';
            else if(i == 11)
                Deck[ind].Number = 'J';
            else if(i == 12)
                Deck[ind].Number = 'Q';
            else if(i == 13)
                Deck[ind].Number = 'K';
            else
                Deck[ind].Number = i%10 + '0';
            Deck[ind].Symbol = activeSymbol;
        }
    }
}

void printDeck()
{
    for(int i = 0; i<= 52; i++)
    {
        cout<<Deck[i].Number<< Deck[i].Symbol << " ";
        if(i % 13 == 0)
            cout << endl;
    }
}


int main()
{
    initDeck();
    printDeck();
    return 0;
}
