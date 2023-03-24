#pragma once
#include <stdio.h>
class NumberList
{
    int numbers[10];
    int count;
public:
    // count will be 0
    void Init() {
        count = 0;
    }

    // adds X to the numbers list and increase the data member count.
    // if count is bigger or equal to 10, the function will return false
    bool Add(int x) {
        if (count >= 10)
            return false;

        numbers[count++] = x;
    }

    // will sort the numbers vector
    void Sort() {
        for (int i = 0; i < count; i++) {
            for (int j = i+1; j <=count; j++) {
                if (numbers[i] > numbers[j])
                {
                    int aux = numbers[i];
                    numbers[i] = numbers[j];
                    numbers[j] = aux;
                }
            }
        }
    }

    // will print the current vector
    void Print() {
        for (int i = 0; i < count; i++) {
            printf("%d ", numbers[i]);
        }
        printf("\n");
    }

};

