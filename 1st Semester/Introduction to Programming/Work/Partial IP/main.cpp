#include <iostream>
using namespace std;

int i = 10,s = 3,x[5]={2,3,4,5,1};

int main() {
int a=5,b=2,*p=&a,*q=&b;
 *p=*q+1;
  a+=*q;
  b=*p+b+1;
   p=&b; q=&a;
    int s=1000*a+100*b+10**p+*q;
    cout<<s;
     return 0;
}
