#include <iostream>
#include <vector>
#include <array>
#include <math.h>
#include <algorithm>
#include <memory>

typedef std::vector<std::array<float, 2>> PointsList2D;

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

namespace exceptions {
    /// <summary>
    /// Helper class used for throwing not implemented error
    /// </summary>
    class NotImplementedException : public std::logic_error {
    public:
        NotImplementedException() : std::logic_error{"Function not yet implemented."} {}
    };
}

namespace interpolation {
    /// <summary>
    /// Defines interface for interpolation classes
    /// </summary>
    class IInterpolation {
        // public construction and destruction methods
    public:
        virtual ~IInterpolation() = default;

        // public interface methods
    public:
        virtual void Interpolate1D(int pointsToInterpolate) = 0;

        virtual void Interpolate2D(int pointsToInterpolate) = 0;

    };

    /// <summary>
    /// Defines Hermite Cubic Interpolation
    /// </summary>
    class CubicInterpolation : public IInterpolation {
        // public construction methods
    public:
        CubicInterpolation(const PointsList2D &points) : pointsList(points) {}

        // IInterpolation methods
    public:
        void Interpolate2D(int pointsToInterpolate) override {
            std::vector<int> index(pointsToInterpolate);
            std::vector<float> t;
            std::vector<float> tx;

            int i = 0, points_size = pointsList.size() - 1;
            std::generate(index.begin(), index.end(), [&i, &pointsToInterpolate, &points_size, &t, &tx]() {
                float percent = ((float) i) / (float(pointsToInterpolate - 1));
                tx.push_back((points_size) * percent);
                t.push_back(tx[i] - floor(tx[i]));
                return int(tx[i++]);
            });

            for (int i = 0; i < pointsToInterpolate; ++i) {
                std::array<PolynomialCoeffs, 2> coeffs;
                std::array<float, 2> A = GetIndexClamped(pointsList, index[i] - 1);
                std::array<float, 2> B = GetIndexClamped(pointsList, index[i]);
                std::array<float, 2> C = GetIndexClamped(pointsList, index[i] + 1);
                std::array<float, 2> D = GetIndexClamped(pointsList, index[i] + 2);

                for (int j = 0; j < 2; j++) {
                    coeffs[j].A = A[j];
                    coeffs[j].B = B[j];
                    coeffs[j].C = C[j];
                    coeffs[j].D = D[j];
                }

                float x = CubicHermite(coeffs[0], t[i]);
                float y = CubicHermite(coeffs[1], t[i]);

                std::cout << "Value at " << tx[i] << " = " << x << "  " << y << std::endl;
            }
        };

        void Interpolate1D(int pointsToInterpolate) override {

            std::vector<int> index(pointsToInterpolate);
            std::vector<float> t;
            std::vector<float> tx;

            int i = 0, points_size = pointsList.size() - 1;
            std::generate(index.begin(), index.end(), [&i, &pointsToInterpolate, &points_size, &t, &tx]() {
                float percent = ((float) i) / (float(pointsToInterpolate - 1));
                tx.push_back((points_size) * percent);
                t.push_back(tx[i] - floor(tx[i]));
                return int(tx[i++]);
            });


            for (int i = 0; i < pointsToInterpolate; ++i) {
                std::array<PolynomialCoeffs, 1> coeffs;
                std::array<float, 2> A = GetIndexClamped(pointsList, index[i] - 1);
                std::array<float, 2> B = GetIndexClamped(pointsList, index[i]);
                std::array<float, 2> C = GetIndexClamped(pointsList, index[i] + 1);
                std::array<float, 2> D = GetIndexClamped(pointsList, index[i] + 2);

                coeffs[0].A = A[0];
                coeffs[0].B = B[0];
                coeffs[0].C = C[0];
                coeffs[0].D = D[0];

                float x = CubicHermite(coeffs[0], t[i]);

                std::cout << "Value at " << tx[i] << " = " << x << "  " << std::endl;
            }

        }

        // private methods
    private:
        struct PolynomialCoeffs {
            float A, B, C, D, t;
        };

        float CubicHermite(PolynomialCoeffs coeffs, float t) const {
            float a = -coeffs.A / 2.0f + (3.0f * coeffs.B) / 2.0f - (3.0f * coeffs.C) / 2.0f + coeffs.D / 2.0f;
            float b = coeffs.A - (5.0f * coeffs.B) / 2.0f + 2.0f * coeffs.C - coeffs.D / 2.0f;
            float c = -coeffs.A / 2.0f + coeffs.C / 2.0f;
            float d = coeffs.B;

            return a * pow(t, 3) + b * pow(t, 2) + c * t + d;
        }


        // private members
    private:
        const PointsList2D &pointsList;

    };

    class LagrangeInterpolation : public IInterpolation {
    public:
        LagrangeInterpolation(const PointsList2D &points) : pointsList(points) {}

        void Interpolate1D(const std::vector<float> &pointsToCalc) {

            DividedDiff();

            for (int i = 0; i < pointsToCalc.size(); i++) {
                std::cout << "Value at " << pointsToCalc[i] << " = " << LaGrange(pointsToCalc[i]) << std::endl;
            }

        };

        void Interpolate1D(int pointsToInterpolate) override {
            // TASK2 : TODO
        };

        void Interpolate2D(int pointsToInterpolate) override {
            // TASK2 : TODO
        };

    private:

        std::vector<float> dividedDiff;

        float DividedDiff() {

            dividedDiff.push_back(pointsList[0][1]);
            dividedDiff.push_back((pointsList[1][1] - pointsList[0][1])/(pointsList[1][0] - pointsList[0][0]));

            calcDividedDiffRec(2);
        }

        void calcDividedDiffRec(int counter) {

            if (counter == pointsList.size()) {
                return;
            }

            dividedDiff.push_back((dividedDiff[counter] - dividedDiff[counter - 1]) /
                                  (pointsList[0][counter] - pointsList[0][counter - 1]));
            calcDividedDiffRec(counter+1);
        }

        float LaGrange(float x) const {

            float returnSum = 0.0;


            for (int i = 0; i < pointsList.size(); i++) {

                float newtonProduct = 1.0;
                for (int j = 0; j < i; j++) {
                    newtonProduct *= (x - pointsList[0][j]);
                }

                returnSum += dividedDiff[i] * newtonProduct;
            }


            return returnSum;
        }

        const PointsList2D &pointsList;
    };
}


int main() {

    const PointsList2D points2D =
            {
                    {0.0f, 1.1f},
                    {1.6f, 8.3f},
                    {2.3f, 6.5f},
                    {3.5f, 4.7f},
                    {4.3f, 3.1f},
                    {5.9f, 7.5f},
                    {6.8f, 0.0f}
            };

    const std::vector<float> pointsToCalc =
            {
                    {0.1f},
                    {0.2f},
                    {0.3f},
                    {0.4f},
                    {0.5f},
                    {0.6f},
                    {0.7f}
            };

//    std::unique_ptr<interpolation::CubicInterpolation> interpolation2D =
//            std::make_unique<interpolation::CubicInterpolation>(interpolation::CubicInterpolation(points2D));
//
//    interpolation2D->Interpolate2D(13);

//    std::unique_ptr<interpolation::CubicInterpolation> interpolation1D =
//            std::make_unique<interpolation::CubicInterpolation>(interpolation::CubicInterpolation(points2D));
//
//    interpolation1D->Interpolate1D(13);

    std::unique_ptr<interpolation::LagrangeInterpolation> interpolation1D =
            std::make_unique<interpolation::LagrangeInterpolation>(interpolation::LagrangeInterpolation(points2D));

    interpolation1D->Interpolate1D(pointsToCalc);


    return 0;
}