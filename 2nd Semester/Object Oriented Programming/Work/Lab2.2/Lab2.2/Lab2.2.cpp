// Lab2.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Student.h"
#include <cstring>


int compareNames(Student s1, Student s2) {
    if (strlen(s1.getName()) > strlen(s2.getName()))
        return 1;
    if (strlen(s1.getName()) < strlen(s2.getName()))
        return -1;

        return 0;
}
int compareGradeMath(Student s1, Student s2) {
    if (s1.getGradeMath() > s2.getGradeMath())
        return 1;
    if (s1.getGradeMath() < s2.getGradeMath())
        return -1;
  
        return 0;
}
int compareGradeEnglish(Student s1, Student s2) {
    if (s1.getGradeEnglish() > s2.getGradeEnglish())
        return 1;
    else if (s1.getGradeEnglish() < s2.getGradeEnglish())
        return -1;
    else
        return 0;
}
int compareGradeHistory(Student s1, Student s2) {
    if (s1.getGradeHistory() > s2.getGradeHistory())
        return 1;
    else if (s1.getGradeHistory() < s2.getGradeHistory())
        return -1;
    else
        return 0;
}
int compareGradeAverage(Student s1, Student s2) {
    if (s1.getGradeAverage() > s2.getGradeAverage())
        return 1;
    else if (s1.getGradeAverage() < s2.getGradeAverage())
        return -1;
    else
        return 0;
}

int main()
{
    Student s1;
    s1.setName("Alex");
    std::cout << s1.getName() << std::endl;

    s1.setGradeMath(5);
    std::cout << s1.getGradeMath() << std::endl;

    s1.setGradeEnglish(6);
    std::cout << s1.getGradeEnglish() << std::endl;

    s1.setGradeHistory(7);
    std::cout << s1.getGradeHistory() << std::endl;

    std::cout << s1.getGradeAverage() << std::endl;

    Student s2;
    s2.setName("Bogdan");
    std::cout << s2.getName() << std::endl;

    s2.setGradeMath(7);
    std::cout << s2.getGradeMath() << std::endl;

    s2.setGradeEnglish(6);
    std::cout << s2.getGradeEnglish() << std::endl;

    s2.setGradeHistory(5);
    std::cout << s2.getGradeHistory() << std::endl;

    std::cout << s2.getGradeAverage() << std::endl;

    std::cout << std::endl;
    std::cout << compareNames(s1, s2) << std::endl;
    std::cout << compareGradeMath(s1, s2) << std::endl;
    std::cout << compareGradeEnglish(s1, s2) << std::endl;
    std::cout << compareGradeHistory(s1, s2) << std::endl;
    std::cout << compareGradeAverage(s1, s2) << std::endl;

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
