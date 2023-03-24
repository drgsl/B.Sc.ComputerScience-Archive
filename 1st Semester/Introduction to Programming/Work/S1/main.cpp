#include <iostream>

using namespace std;

int bisect(int an)
{
    if(an % 4 == 0 && an % 100 != 0 && an % 400 == 0)
        return true;
    return false;
}

int maxim(int a, int b, int c)
{
    int maxi;
    maxi = (a>b? a: b)>c? maxi : c;
    return maxi;
}

/*
Raspunsuri:

-- 3 --
a = 5;
b = 10;

b = 11;
a = 6;
d = 6/11 = .54;
b = 10;
b = 11;

11, 11, 11, .54;

-- 4 --
b = 11;
a = 6;
c = 0.54;
b = 10;
b = 11;

a = 11;
c = 11;
cout << 11/2 = 5;

*/

void ord(int a, int b, int c)
{

    int n3 = (a>b? a: b)>c? n3 : c;
    int n1 = (a<b? a: b)<c? n1 : c;


    cout << n1 << " " << n2 << " "<< n3;
}

int main()
{
    int a = 5, b = 10;
    float d,c;
    c = a = ++b, ++a, d=(float)a/b--, ++b;
    printf("%d %d , %f %f\n",a,b,c,d);
    cout<<endl;

    a=5,b=10;
    cout<<(c=a=++b,++a,c=(float)a/b--,++b)/2;
}
