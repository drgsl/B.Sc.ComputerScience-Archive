#include <iostream>
#include <cstring>
using namespace std;

///Problema 4/Lab 4

struct cuvant
{
    char text[100];
    unsigned int nrAparitii;
};

cuvant * getWords(char Text[])
{
    static cuvant cuvinte[100];

    char *p;
    int i = 0;
    p = strtok(Text, " ");
    while(p)
    {
        bool isInArray = false;
        for(int j = i; j>=0; j--)
        {
            if(!strcmp(p, cuvinte[j].text))
            {
                isInArray = true;
                cuvinte[j].nrAparitii ++;
                break;
            }
        }
        if(!isInArray)
        {
            strcpy(cuvinte[i].text, p);
            cuvinte[i].nrAparitii = 1;
            i++;
        }
        p = strtok(NULL, " ");
    }

    return cuvinte;
}


int main()
{
    char textTest[] = "ana si maria si-au spus cuvinte si si-au spus cum ca maria a inteles ca ana minte";
    cuvant *cuvinte2 = getWords(textTest);

    int i = 0;
    while(true)
    {
        cuvant cuvActual = *(cuvinte2 + i);
        if (strcmp(cuvActual.text,"") == 0)
            break;
        cout << "Cuvantul  " << i << " : " << cuvActual.text << endl;
        cout << "Nr aparitii" << " : " << cuvActual.nrAparitii << endl;
        cout<<endl;
        i++;

    }
    return 0;
}
