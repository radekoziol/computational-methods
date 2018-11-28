#include <iostream>
#include "aghIntegration.cpp"


using namespace std;

double fun1(double x) {
    return x*x;
}

int main() {


    aghIntegration A = aghIntegration(fun1);


    double val = A.integrateWithSquares(0, 10, 100);

    cout << "Square Method: " << val << endl;

    val = A.integrateWithTrapeze(0, 10, 100);

    cout << "Trapeze Method: " << val << endl;

    val = A.integrateWithSimpson(0, 10, 10);

    cout << "Simpson Method: " << val << endl;


    


    return 0;
}