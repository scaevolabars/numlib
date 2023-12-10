#include <iostream>
#include <queue>
#include <random>
#include <cmath>
#include <numbers>

template <typename T>
class OnlineStats {
    std::queue<T> x1;
    std::queue<T> x2;
    size_t window_size;
    size_t size;
    T sum_x1;
    T sum_x2;

    public:
    OnlineStats(size_t sz): window_size(sz), size(0), x1{}, x2{}, sum_x1{}, sum_x2{} {}
    OnlineStats() = delete;

    T online_mean() {
        if (size == 0) return T();
        else return sum_x1 / size;
    }
    T online_variance() {
        if (size == 0) return T();
        else {
            T sq = sum_x1 / size;
            return (sum_x2 / size) - (sq * sq);
        } 
    }
    T online_covariance() {return T();}
    void update(T val) {
        if (size < window_size) size++;
        else {
            T decrement1 = x1.front();
            T decrement2 = x2.front();
            x1.pop();
            x2.pop();
            sum_x1 -= decrement1;
            sum_x2 -= decrement2;
        }
        T increment1 = val;
        T increment2 = pow_n(val, 2); 
        sum_x1 += increment1;
        sum_x2 += increment2;
        x1.push(increment1);
        x2.push(increment2);
    }

    private:
    T pow_n(T x, int p) {
        if (p == 0) return 1.0;
        T prod = x;
        while(--p) {
            prod *= x;
        }
        return prod;
    }

};


int main() {
    
    auto s = OnlineStats<double>(100);


    std::random_device rd;

    std::mt19937 e2(rd());

    std::uniform_real_distribution<> uniform01(0, 1);

    double period = 200.0;
    double ampl = 10.0;
    double x{};
    double y{};
    for (int i = 0; i < 1000; ++i) {
        s.update(y);
        std::cout << y << ", " << s.online_mean() << ", " << s.online_variance() << '\n';
        y = uniform01(e2) + (ampl * std::sin( 2.0 * std::numbers::pi * x / period));
        x += 1.0;
    }

    return 0;
}