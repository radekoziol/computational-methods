//
// Created by radekkoziol on 28.11.18.
//

#include <iostream>
#include "aghIntegration.h"


aghIntegration::aghIntegration(const function<double(double)> &newfun) {
    fun = newfun;
}


double aghIntegration::integrateWithSquares(double from, double to, unsigned int pointNumber) {

    double range = (to - from) / pointNumber;
    double sum = 0.0;

    for (int i = 1; i <= pointNumber; i++) {
        sum += fun(from + range * i);
    }

    return sum * range;
}

double aghIntegration::integrateWithTrapeze(double from, double to, unsigned int pointNumber) {

    double range = (to - from) / pointNumber;
    double sum = 0.0;

    for (int i = 1; i <= pointNumber; i++) {
        sum += (fun(from + range * i) + fun(from + range * (i - 1))) / 2;
    }

    return sum * range;
}

double aghIntegration::integrateWithSimpson(double from, double to, unsigned int pointNumber) {

    double range = (to - from) / pointNumber;
    double sum = 0.0;

    for (int i = 0; i < pointNumber - 1; i++) {
        sum += 2 * fun(from + range * (i + 1)) + 4 * fun(from + range * (2 * i + 1) / 2);
    }

    sum += 4 * fun(from + range * (2 * (pointNumber - 1) + 1) / 2);

    return (fun(from) + fun(to) + sum) * range / 6;

}
