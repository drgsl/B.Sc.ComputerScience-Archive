#include <iostream>
#include <cstring>
using namespace std;

int convert_str_to_int(char str[])
{
    //cout<<str<<" ";
    int num =0;
    for(int i = 0; i<strlen(str); i++)
    {
        num*=10;
        num+=str[i]-'0';
    }
    cout<<num<<" ";
    return num;
}

int main()
{
    FILE *f;
    f = fopen("in.txt", "r");
    if(!f)
        perror("Error on reading! Error message: "), exit(1);

    int sum = 0;

    for(int i= 0; i<4; i++)
    {
        char buf[10];
        fscanf(f,"%s", &buf);
        sum+=convert_str_to_int(buf);
    }
    cout<<sum;
    return 0;
}
