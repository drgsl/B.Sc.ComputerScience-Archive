//#include <iostream>

using namespace std;

#define tipDate int
typedef struct nod
{
    tipDate info;
    struct nod* urm;
    struct nod* prec;
};
typedef struct coada
{
    struct nod* prim;
    struct nod* ultim;
    unsigned int lungime;
};

///6.2.1

void addBegining(coada &Coada, tipDate info)
{

}


int main()
{

}
