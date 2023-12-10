#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>

class Beta {
    double alpha;
    double beta;
    double C;

    public:
    Beta(double a, double b): alpha(a), beta(b), C(_normalization(a, b)) {};

    double operator()(const double x) const {
        return std::pow(x, alpha - 1.0) * 
            std::pow(1.0 - x, beta - 1.0 ) * C;
    }

    private:
    double _normalization(double a, double b) {
        return std::tgamma(alpha + beta) / 
            (std::tgamma(alpha) * std::tgamma(beta));
    }
};

template <typename T>
std::vector<T> linspace(T a, T b, size_t N) {
    T h = (b - a) / static_cast<T>(N-1);
    std::vector<T> xs(N);
    typename std::vector<T>::iterator x;
    T val;
    for (x = xs.begin(), val = a; x != xs.end(); ++x, val += h)
        *x = val;
    return xs;
}



int main() {

    Beta dist{2.0, 5.0};
    auto interval = linspace(0.0, 1.0, 1000);
    auto beta_distr = interval;
    for(auto it  = beta_distr.begin(); it != beta_distr.end(); ++it) {
        *it = dist(*it);
    }

    auto p_star = *std::max_element(
        beta_distr.begin(),
        beta_distr.end()
        );

    {
        size_t samples = 5000;
        std::random_device rd;

        std::mt19937 e2(rd());

        std::uniform_real_distribution<> uniform01(0, 1);
        std::uniform_real_distribution<> uniform0p(0, p_star);

        std::vector<double> hist{};
        std::vector<double> samp{};

        for (size_t i = 0; i < samples; ++i) {
            double x = uniform01(e2);
            double u = uniform0p(e2);

            if (u <= dist(x)) {
                hist.push_back(u);
                samp.push_back(x);
            }

        }

        for (size_t i = 0; i < hist.size(); ++i) {
            std::cout << samp[i] << ", " << hist[i] << '\n';
        }

    }
}