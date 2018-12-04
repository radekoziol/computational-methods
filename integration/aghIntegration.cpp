//
// Created by radekkoziol on 28.11.18.
//

#include <iostream>
#include <random>
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

double aghIntegration::calculatePiWithMontCarlo(unsigned int pointNumber) {

    std::default_random_engine gen;
    std::uniform_real_distribution<double> distr;

    int hits = 0;

    for (int i = 0; i < pointNumber; i++) {
        double x = distr(gen);
        double y = distr(gen);
        double lengthToCenter = sqrt(x * x + y * y);
        if (lengthToCenter <= 1) hits++;
    }


    return double(hits) / pointNumber * 4;
}

double aghIntegration::integrateWithMonteCarlo(double from, double to, unsigned int pointNumber) {

    std::default_random_engine gen;
    std::uniform_real_distribution<double> distr(from,to);

    double sum = 0.0;

    for (int i = 0; i < pointNumber; i++) {
        double x = distr(gen);
        sum += fun(x);
    }

    return sum * (to - from) / (pointNumber);
}
