//
// Created by radekkoziol on 17.10.18.
//

#include <iostream>
#include <vector>
#include <array>
#include <math.h>
#include <algorithm>
#include <memory>
#include "library.h"


namespace regression {

    class LinearRegressor {

    public:

        LinearRegressor() = default;

        float fit(std::vector<float> x, std::vector<float> y) { throw exceptions::NotImplementedException(); }

        std::vector<float> predict(std::vector<float> x) { throw exceptions::NotImplementedException(); }

        /*
            b = sum( (xi-mean(x)) * (yi-mean(y)) ) / sum((xi – mean(x))^2)
            b = sumB1/sumB2
            a = mean(y) – b * mean(x)
            y = b + a * x
         */
        std::pair<float, float> linearRegression(std::vector<float> x, std::vector<float> y) {
            float A, B, sumB1, sumB2, meanX, meanY;
            sumB1 = sumB2 = 0.0;
            meanX = mean(x);
            meanY = mean(y);

            for (int i = 0; i < x.size(); i++) {
                sumB1 += ( (x[i] - meanX) * (y[i] - meanY) );
                sumB2 += pow(x[i] - meanX,2);
            }

            B = sumB1 / sumB2;
            A = meanY - B * meanX;

            return std::pair<float, float>(A, B);
        }

    private:

        std::pair<float, float> coefficients;

        float rmse(std::vector<float> x, std::vector<float> y) {
            float rmse = 0.0;

            for (int i = 1; i < x.size(); i++) {
                rmse += pow(2, (x[i] - y[i]));
            }

            return rmse / x.size();

        }


        float mean(std::vector<float> x) {

            float mean = 0.0;

            for (int i = 0; i < x.size(); i++) {
                mean += x[i];
            }

            return mean / x.size();
        }

    };

}


int main() {

    const std::vector<float> x =
            {
                    {0.0f},
                    {1.0f},
                    {2.0f},
//                    {0.4f},
//                    {0.5f},
//                    {0.6f},
//                    {0.7f}
            };

    const std::vector<float> y =
            {
                    {2.0f},
                    {4.0f},
                    {6.0f},
//                    {0.4f},
//                    {0.5f},
//                    {0.6f},
//                    {0.7f}
            };


    std::unique_ptr<regression::LinearRegressor> regression =
            std::make_unique<regression::LinearRegressor>(regression::LinearRegressor());

    std::pair<float, float> coefficients = regression->linearRegression(x,y);

    std::cout << "a = " << coefficients.second << " b = " << coefficients.first << std::endl;


}