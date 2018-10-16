//
// Created by radekkoziol on 12.10.18.
//

#include <iostream>

#include <gsl/gsl_ieee_utils.h>


using namespace std;


int main() {

    float f = 1.0 / 3.0;
    double d = 1.0 / 3.0;

    double fd = f; /* promote from float to double */

    printf(" f=");
    gsl_ieee_printf_float(&f);
    printf("\n");

    printf("fd=");
    gsl_ieee_printf_double(&fd);
    printf("\n");

    printf(" d=");
    gsl_ieee_printf_double(&d);
    printf("\n");
}