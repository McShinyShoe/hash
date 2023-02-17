#include <iostream>
#include "../src/base.h"
#include "../src/strnum.h"

#include <thread>

using namespace std;
using namespace shiny;

bool editing = 0;
bool printing = 0;

std::string txt;
size_t i = 0;
void printNum()
{
    while(i != __SIZE_MAX__)
    {
        while(editing);
        printing = true;
        cout << txt << " = " << i << endl;  
        printing = false;
    }
}
void calcTxt()
{
    while(i != __SIZE_MAX__)
    {
        while(printing);
        editing = true;
        txt = binary.decodeN(i, 64);
        editing = false;
    }
}

void addI()
{
    for(; i < __SIZE_MAX__; i++);
}

int main()
{
    StrNum num(base2);    
    std::thread t1(printNum);
    std::thread t2(calcTxt);
    std::thread ti1(addI);
    std::thread ti2(addI);
    std::thread ti3(addI);
    std::thread ti4(addI);
    t1.join();
    t2.join();
    ti1.join();
    ti2.join();
    ti3.join();
    ti1.join();
    num = 123123;
    cout << num << endl;  
    num.rComplement();
    cout << num << endl;
}