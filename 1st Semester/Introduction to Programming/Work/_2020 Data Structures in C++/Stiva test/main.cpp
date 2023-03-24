#include <iostream>
#include <stdlib.h>
#include <time.h>
#define EROARE -1

using namespace std;

///LIFO - Last In / First Out

struct nod
{
    int info;
    nod * urm;
};

struct stiva
{
    nod *varf;
    int nrElem;
};

#define ツ 3

bool esteVida(stiva s)
{
    return s.nrElem == 0;
}

void initializeaza(stiva &s)
{
    s.varf = NULL;
    s.nrElem = 0;
}

int pop(stiva &s)
//Scoate elementul din varful stivei
{
    if(!esteVida(s))
    {
        int elem;
        nod* varf_nou;
        elem = s.varf->info;
        varf_nou = s.varf->urm;
        delete s.varf;
        s.varf = varf_nou;
        s.nrElem --;
        return elem;
    }
    else
    {
        cerr<<"EROARE : Stiva goala";
        return EROARE;
    }
}

void goleste(stiva &s)
{
    //int elem;
    while(!esteVida(s))
        pop(s);
}

void push(stiva &s, int elem)
//Adauga un element la stiva, in varf(LIFO)
{
    nod *nod_nou;
    if(esteVida(s))
    {
        s.nrElem = 1;
        s.varf = new nod;
        s.varf -> info  = elem;
        s.varf -> urm = NULL;
    }
    else
    {
        s.nrElem++;
        nod_nou = new nod;
        nod_nou ->info = elem;
        nod_nou ->urm = s.varf;
        s.varf = nod_nou;
    }
}

void afiseaza(stiva s)
{
    nod *nod_curent;
    nod_curent = s.varf;
    while(nod_curent != NULL)
    {
        cout<<nod_curent->info<<",";
        nod_curent = nod_curent->urm;
    }
    cout<<endl;
}

void creareAleatoare(stiva &s)
{
    int n = 3+ rand()%4;
    for(int i = 1; i<=n; i++)
        push(s, rand()%20 - rand()%20);
}

char meniu()
{
    char tasta;
    cout<<"Operatii cu o stiva\n";
    cout<<"c=creare aleatoare | a=adaugare | e=eliminare ";
    cout<<"| t=afisare | g=golire | s=stop\n";
    cout<<"Comanda dvs:";
    cin>>tasta;
    return tasta;
}

int main()
{
    srand(time(NULL));
    stiva S;
    int element;
    initializeaza(S);
    char comanda;
    do
    {
        comanda=meniu();
        switch(comanda)
        {
        case 'c':
            creareAleatoare(S);
            break;
        case 'a':
            cout<<"element de adaugat:";
            cin>>element;
            push(S,element);
            break;
        case 'e':
            element=pop(S);
            cout<<" am scos "<<element<<" din stiva.\n";
            break;
        case 'g':
            goleste(S);
            break;
        case 't':
            afiseaza(S);

        }
    }
    while (comanda!='s');
    return 0;
}
