#include "array.h"
#include <random>
#include <iostream>
#include <boost/format.hpp>
#include <chrono>

using namespace std;

uniform_real_distribution<double> generator { -10, 10 };
default_random_engine re;

const double GB = 1024 * 1024 * 1024;

double gen() {
    return generator(re);
}

template <typename T>
void randomize(T & a) {
    int n = a.get_n();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a(i, j) = gen();
        }
    }
}

template <typename U, typename V>
void copy(const U & a, V & b) {
    int n = a.get_n();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b(i, j) = a(i, j);
        }
    }
}

template <typename U, typename V>
void check_equals(const U & a, V & b) {
    int n = a.get_n();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (b(i, j) != a(i, j)) {
                cout << "Elements " << i << ", " << j << " are not equal!" << endl;
            }
        }
    }
}

int main() {
    re.seed(chrono::system_clock::now().time_since_epoch().count());

    int size = 16384;
    simple_array<double> a(size);
    cached_array<double> b(size);
    morton_array<double> c(size);

    randomize(a);
    copy(a, b);
    copy(a, c);

    cout << "Checking a == b" << endl;
    check_equals(a, b);

    cout << "Checking a == c" << endl;
    check_equals(a, c);

    cout << "Checking b == c" << endl;
    check_equals(b, c);
}
