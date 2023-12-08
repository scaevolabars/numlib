#include <iostream>
#include <vector>
#include <cmath>
#include <numbers>
#include <iomanip>


inline int ispositive(int m) {
        return m > 0;
    } 

inline int is_nonneg_bounded(int x, int m) {
        return x >= 0 && x < m;
} 


class Generator {

};

class LinearCongruent : public Generator {
    int m_mod;
    int m_seed;
    int m_mult;
    int m_shift;

    LinearCongruent() : m_mod(1), m_seed(0), m_mult(1), m_shift(1) {
        std::cout << "Default Constructor is called";
    };
    LinearCongruent(int x, int a, int b, int m) : m_mod(m), m_seed(x), m_mult(a), m_shift(b) {};
    public:
    static LinearCongruent create(int x, int a, int b, int m) {
        if (bounds_check(x,  a,  b,  m)) {
            return LinearCongruent(x, a, b, m);
        } else {
            return LinearCongruent();
        }
    } 

    std::vector<double> generate(size_t n) {
        if (n) {
            std::vector<double> rv_vec(n);
            rv_vec[0] = static_cast<double>(m_seed) / m_mod; 
            long long x_curr = m_seed;
            for (size_t i = 1; i < n; ++i) {
                x_curr = (m_mult * x_curr + m_shift) % m_mod;
                rv_vec[i] = static_cast<double>(x_curr) / m_mod;
            }
            return rv_vec;

        } else {
            return {};
        }
    }

    private: 
    static bool bounds_check(int x, int a, int b, int m) {
        return ispositive(m) && is_nonneg_bounded(x, m) &&
                                is_nonneg_bounded(a, m) &&
                                is_nonneg_bounded(b, m);
    }

};

using PairVecDouble = std::pair<std::vector<double>, std::vector<double>>;

std::pair<std::vector<double>, std::vector<double>> box_muller(const std::vector<double>& u1, const std::vector<double>& u2) {
    if (u1.size() > 0  && u1.size() == u2.size()) {
        int n = u1.size();
        std::vector<double> z1(n); // How to eliminate initialization
        std::vector<double> z2(n);
        for (size_t i = 0; i < n; ++i) {
            z1[i] = std::sqrt(-2.0 * std::log(u1[i])) * std::cos(2.0 * std::numbers::pi * u2[i]);
            z2[i] = std::sqrt(-2.0 * std::log(u1[i])) * std::sin(2.0 * std::numbers::pi * u2[i]);
        }
        return {z1, z2};
        
    } else {
        {};
    }

    return {};
}


int main() {
    //std::cout << "Linear Congruent Generator\n";
    /*size_t n = 100000;
    int a = 106;
    int b = 1283;
    int m = 6075;
    int x0 = 1;
    */
    //auto lcg = LinearCongruent::create(x0, a, b, m);
    //auto rv = lcg.generate(n);

    {
    /*
        size_t n = 100000;
        int a = 1664525;
        int b = 1013904223;
        int m = INT32_MAX;
        int x0 = 15;
    */
        size_t n = 100000;
        int m = 2048;
        int a = 43;
        int b = 0;
        int x0 = 1;



        auto lcg1 = LinearCongruent::create(x0, a, b, m);
        auto lcg2 = LinearCongruent::create(x0 + 12, a, b, m);

        auto urv1 = lcg1.generate(n);
        auto urv2 = lcg2.generate(n);

        auto nrv2d = box_muller(urv1, urv2);

        for (size_t i = 0; i < n; ++i) {
             std:: cout << std::setprecision(20) << nrv2d.first[i] << ", " << nrv2d.second[i]  << '\n';
        }

    }
   
    return 0;
}