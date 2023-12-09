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

    for (size_t i = 0; i < beta_distr.size(); ++i) {
        std::cout << interval[i] << ", " << beta_distr[i] << '\n';
    }
}