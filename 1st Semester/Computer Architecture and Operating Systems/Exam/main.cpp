// examen ACSO.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


void insert(int *array, int size, int max, int value) {

int i;
   for( i = size;i>0 && array[i-1]> value;i--)//using obsolete binding at 'i'
     array[i]=array[i-1];
     array[i]= value;//name lookup of i changed for new ISO 'for' scoping

}


int main()
{
    int v[10] = { 15,29,57 }, i;
    insert(v, 3, 10, 40); // insereaza valoarea 40
    for (i = 0; i < 4; i++)
        std::cout << v[i] << ' '; // se va afisa "15 29 40 57" pe ecran
    return 0;


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
