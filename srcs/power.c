#include "myclass.hpp"

//static char modName[64] = {0};
// double fpower(double base, int pwr)
// {
//     int i = 0;
//     double r = 1.0;
//     for (; i < pwr; i++)
//         r = r * base;
//     return r;
// }

int ipower(int base, int pwr)
{
    //print_num(base);
    //print_num(pwr);
    int i = 0;
    int r = 1;
    for (; i < pwr; i++)
        r = r * base;
    return r;
}
