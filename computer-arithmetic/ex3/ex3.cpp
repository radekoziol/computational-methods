//
// Created by radekkoziol on 12.10.18.
//

#include <iostream>

#include <gsl/gsl_ieee_utils.h>
#include <cmath>


using namespace std;


int main() {

    int i;
    float a = 1.1;

    for (i = 1; i <= 149; i++) {
        printf(" d=");
        gsl_ieee_printf_float(&a);

        if (!isnormal(a))
            printf(" is subnormal \n");
        else
            printf("\n");

        a = a / 2.0;
    }
}