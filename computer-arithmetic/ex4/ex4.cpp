//
// Created by radekkoziol on 12.10.18.
//


#include <iostream>

#include <gsl/gsl_ieee_utils.h>
#include <cmath>


using namespace std;

float f(float x) {
    return static_cast<float>(sqrt(pow(x, 2) + 1) - 1);
}


float g(float x) {
    return static_cast<float>((abs(x)) / (sqrt(pow(x, 2) + 1) + 1));
}


int main() {

    float x = 1.0;
    int i;

    for (i = 1; i < 50; i++) {

        float f_x = f(x);
        float g_x = g(x);

        printf(" x =");
        gsl_ieee_printf_float(&x);
        printf("\n");

        printf(" f(x) =");
        gsl_ieee_printf_float(&f_x);

        if (!isnormal(f_x))
            printf(" is subnormal \n");
        else
            printf("\n");

        printf(" g(x) =");
        gsl_ieee_printf_float(&g_x);

        if (!isnormal(g_x))
            printf(" is subnormal \n");
        else
            printf("\n");

        printf(" g(x) - f(x) =");
        float diff = g_x - f_x;
        gsl_ieee_printf_float(&diff);
        printf("\n\n");


        x = static_cast<float>(x / 2.0);
    }


}