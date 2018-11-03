//
// Created by radekkoziol on 31.10.18.
//

#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <algorithm>
#include <memory>
#include <complex>
#include <functional>
#include <chrono>

using namespace std;
using namespace std::chrono;

/// <summary>
/// Template function used for clamping specified datasets
/// </summary>
template<typename T>
T GetIndexClamped(const std::vector<T> points, int index) {
    if (index < 0)
        return points[0];
    else if (index >= int(points.size()))
        return points.back();
    else
        return points[index];
}


namespace fourier_transform {


    /// <summary>
    /// Defines interface for interpolation classes
    /// </summary>
    class FourierTransform {
        // public construction and destruction methods
    public:
        virtual ~FourierTransform() = default;

        // public interface methods
    public:

        std::vector<complex<double>> DFT_slow(const std::vector<complex<double>> &x);

        void DFT_fast(complex<double> *X, int N);
    };

    std::vector<complex<double>> FourierTransform::DFT_slow(const std::vector<complex<double>> &x) {

        double size = x.size();
        std::vector<complex<double>> out(size, 0.0);

        for (int i = 0; i < size; i++) {

            complex<double> sum = 0.0 + 0.0i;

            for (int j = 0; j < size; j++) {
                sum += x[j] * exp(complex<double>(0, -2 * M_PI * i * j / size));
            }

            out[i] = sum;
        }


        return out;
    }


    void separate(complex<double> *a, int n) {

        auto *tmp = new complex<double>[n / 2];

        for (int i = 0; i < n / 2; i++)
            tmp[i] = a[i * 2 + 1];
        for (int i = 0; i < n / 2; i++)
            a[i] = a[i * 2];
        for (int i = 0; i < n / 2; i++)
            a[i + n / 2] = tmp[i];

        delete[] tmp;
    }

    void FourierTransform::DFT_fast(complex<double> *X, int N) {

        if (N >= 2) {

            // all evens to lower half, all odds to upper half
            separate(X, N);

            DFT_fast(X, N / 2);
            DFT_fast(X + N / 2, N / 2);

            for (int k = 0; k < N / 2; k++) {

                complex<double> e = X[k];
                complex<double> o = X[k + N / 2];
                complex<double> factor = exp(complex<double>(0, -2. * M_PI * k / N));

                X[k] = e + factor * o;
                X[k + N / 2] = e - factor * o;
            }
        }

    }


}

int main() {


    std::unique_ptr<fourier_transform::FourierTransform> FourierTransform =
            std::make_unique<fourier_transform::FourierTransform>(fourier_transform::FourierTransform());


    std::vector<complex<double>> x = {
            1.0 + 2.3i,
            1.1 + 4.2i,
            1.05 + 3.05i,
            14.2 + 5.2i,
            1.3 + 2.3i,
            1.2 + 3.4i,
            1.3 + 3.3i,
            1.05 + 3.05i};


    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    std::vector<complex<double>> y = FourierTransform->DFT_slow(x);

    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(t2 - t1).count();

    cout << "time: " << duration << endl;


    for (auto &i : y) {
        std::cout << i.real() << " + " << i.imag() << " * i" << endl;
    }

    cout << endl;


    t1 = high_resolution_clock::now();

    FourierTransform->DFT_fast(x.data(), static_cast<int>(x.size()));

    t2 = high_resolution_clock::now();

    duration = duration_cast<microseconds>(t2 - t1).count();

    cout << "time: " << duration << endl;


    for (auto &i : x) {
        std::cout << i.real() << " + " << i.imag() << " * i" << endl;
    }


    return 0;
}