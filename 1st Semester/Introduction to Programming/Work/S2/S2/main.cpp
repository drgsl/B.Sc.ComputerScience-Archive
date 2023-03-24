#include <iostream>

using namespace std;

///2.1 Exercitii cu instructiuni repetitive

//secv max nr egale
void recap14()
{
    int n;

    cin>>n;

    int nr;
    int lastNr;
    int length = 1;

    int maxLength = 0;
    int maxIn = -1;
    for(int i = 1; i<= n; i++)
    {
        cin>>nr;
        if(nr == lastNr)
            length ++;
        else
        {
            if(length > maxLength)
            {
                maxLength = length;
                maxIn = i - maxLength;
            }
            length = 1;
        }

        lastNr = nr;
    }

    cout << "lungimea=" << maxLength;
    cout << endl;
    cout << "prima pozitie=" << maxIn;
}

//palindrom
void recap9()
{
    int n;
    cin>>n;
    int copieN = n;
    int ogl = 0;
    while(copieN)
    {
        ogl = ogl * 10 + copieN%10;
        copieN /= 10;
    }
    if(ogl == n)
        cout<<"Numarul este palindrom";
    else
        cout<<"Numarul nu este palindrom";
}

//numar lipsa dintr-o secventa fara vector
void mediu1()
{
    int n;
    cin>>n;

    int nr;
    int sumaPartiala = 0;
    int sumaCompleta = n*(n+1)/2;
    for(int i = 1; i<n; i++)
    {
        cin>>nr;
        sumaPartiala += nr;
    }
    cout<<"lipseste "<< sumaCompleta - sumaPartiala;
}


///2.2 Exercitii cu functii

long factorial_rec(long n)
{

    if(n == 1)
        return 1;
    else
        return n*factorial_rec(n-1);
}

unsigned int fibonnaci_rec(int index)
{

    if(index == 0)
        return 0;
    if(index == 1)
        return 1;
    else
        return fibonnaci_rec(index-1) + fibonnaci_rec(index-2);
}

bool isPalindrome(unsigned int x)
{

    int binNum[32];

    int i = 0;
    while(x>0)
    {
        binNum[i] = x%2;
        x = x/2;
        i++;
    }
    for (int j = i - 1; j >= 0; j--)
        cout<<binNum[j];

        cout<<endl;

    for(int j = 0; j<i; j++)
        if(binNum[j] != binNum[i-1-j])
            return false;
    return true;
}

int main()
{
    //recap14();
    //recap9();
    //mediu1();

    //cout<<factorial_rec(10);
    //cout<<fibonnaci_rec(3);

    //cout << isPalindrome(10);
    //cout << isPalindrome(15);


    return 0;
}
