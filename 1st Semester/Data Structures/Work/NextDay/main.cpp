#include <iostream>

using namespace std;

struct Date
{

    int z;
    int l;
    int a;

};

int isLeapYear(int year)
{

    return (year %400 == 0)||((year%4 == 0 ) && (year %100 != 0));

}

int lastDayOfMonth(Date date)
{

    if(date.l == 2)
        if(isLeapYear(date.a))
            return 29;
        else
            return 28;
    if(date.l == 4 || date.l == 6 || date.l == 9 || date.l == 11)
        return 30;
    return 31;

}

Date nextDate(Date date)
{

    if(date.z != lastDayOfMonth(date))
        date.z++;
    else
    {
        date.z = 1;
        date.l = (date.l + 1)%12;
        if(date.l == 1)
            date.a++;
    }
    return date;
}


int main()
{
    Date data1;
    data1.z = 29;
    data1.l = 2;
    data1.a = 2020;

    Date data2 = nextDate(data1);
    cout << data2.z << " " << data2.l << " " << data2.a << endl;
    return 0;
}
