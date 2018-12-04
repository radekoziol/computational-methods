#include <iostream>
#include "aghIntegration.cpp"


using namespace std;

double fun1(double x) {
    return x*x;
}

int main() {


    aghIntegration A = aghIntegration(fun1);
    unsigned int pointNumber = 100;

    cout << "Using " << pointNumber << " points: " << endl;

    double val = A.integrateWithSquares(0, 10, pointNumber);

    cout << "Square Method: " << val << endl;

    val = A.integrateWithTrapeze(0, 10, pointNumber);

    cout << "Trapeze Method: " << val << endl;

    val = A.integrateWithSimpson(0, 10, pointNumber);

    cout << "Simpson Method: " << val << endl;

    val = A.integrateWithMonteCarlo(0,10,pointNumber);

    cout << "Monte Carlo method: " << val << endl;

    val = A.calculatePiWithMontCarlo(pointNumber);

    cout << "Pi value using Monte Carlo: " << val << endl;







    return 0;
}