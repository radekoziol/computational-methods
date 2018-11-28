//
// Created by radekkoziol on 28.11.18.
//

#ifndef DIFFERENTIAL_EQ_AGHINTEGRATION_H
#define DIFFERENTIAL_EQ_AGHINTEGRATION_H


#include <functional>

using namespace std;

class aghIntegration {

private:
    function<double(double)> fun;

public:
    aghIntegration(const function<double(double)> &fun);

    virtual ~aghIntegration() = default;


    virtual double integrateWithSimpson(double from, double to, unsigned int pointNumber);

    virtual double integrateWithTrapeze(double from, double to, unsigned int pointNumber);

    virtual double integrateWithSquares(double from, double to, unsigned int pointNumber);
};


#endif //DIFFERENTIAL_EQ_AGHINTEGRATION_H
