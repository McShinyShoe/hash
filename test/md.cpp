#include "../src/md.h"
#include "base.h"
#include <iostream>

using namespace std;
using namespace shiny;

int main()
{
    MD2 md2;
    md2.init("qwertyuiopasdfghj");
    md2.calculate();
    // for(auto block : md2.blocks)
    // {
    //     for(uint8_t word : block)
    //         cout << (int)word << " ";
    //     cout << endl;
    // }
    // for(uint8_t buff : md2.buffer)
    // {
    //     cout << (int)buff << endl;
    // }
    cout << "MD2: ";
    for(auto h : md2.getDisgest())
        cout << hexadecimal.decodeN(h, 2);
    cout << endl;
}