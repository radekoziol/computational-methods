//
// Created by radekkoziol on 12.10.18.
//

#include <iostream>

using namespace std;


float next_float(float value) {
    return value * 1.001;
}

double next_double(double value) {
    return value * 1.001;
}

int main() {
    int i;
    double next_d_val = 1.01;
    float next_f_val = 1.01;


    for (i = 1; i <= 100; i++) {
        next_d_val = next_double(next_d_val);
        cout.precision(100);
        cout << "Double no " << i << " : " << next_d_val << endl;

        next_f_val = next_float(next_f_val);
        cout.precision(100);
        cout << "Float no  " << i << " : " << next_f_val << endl;

        cout.precision(100);
        cout << fixed << "Difference" << " :  " << next_d_val - next_f_val << endl;
    }


    return 0;
}
