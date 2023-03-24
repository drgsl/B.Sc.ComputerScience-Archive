#include <iostream>
#include <cstring>

using namespace std;

struct word
{

    char txt[32];

};

int main()
{
    char str[255] = "I went to the library yesterday";
    //scanf("%[^\n]s", str);

    char *p = strtok(str, " ");

    word words[10];
    int i = 0;

    while(p)
    {
        strcpy(words[i++].txt, p);
        p = strtok(NULL, " ");
    }

    for(int i = 0; i<6; i++)
    {
        for(int j = 5; j >=i; j--)
        {
            if(strlen(words[j].txt) > strlen(words[i].txt))
            {
                ///Swap
                char aux[32] = "";
                strcpy(aux, words[i].txt);
                strcpy(words[i].txt, words[j].txt);
                strcpy(words[j].txt, aux);
            }
        }
    }
    for(int i = 0; i<6; i++)
        cout<<words[i].txt<<endl;
    return 0;
}
