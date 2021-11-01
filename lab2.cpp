#include <iostream>
#include <math.h>
#include <ctime>
#include <string>
#include <functional>

using namespace std;

const double a = 0, b = 1, eps = 0.001, delta = 0.05;
double x1 = 0.0, x2 = 0.5, x3 = 1.0;

inline double func(double x) {
    return sqrt(1 + x * x) + exp(-2*x);
}

inline double formula(double x1, double x2, double x3) {
    return ((x2*x2 - x3*x3)*func(x1) + (x3*x3 - x1*x1)*func(x2) + (x1*x1 - x2*x2)*func(x3)) /
           ((x2 - x3)*func(x1) + (x3 - x1)*func(x2) + (x1 - x2)*func(x3)) / 2;
}

double comparator(double x1, double x2, double x3) {
    double f1 = func(x1), f2 = func(x2), f3 = func(x3);
    if (f1 <= f2 && f1 <= f3) return x1;
    if (f2 <= f1 && f2 <= f3) return x2;
    return x3;
}

void interpolation(double x1, double x2, double x3, double eps, double delta) {
    double f1 = func(x1), f2 = func(x2);
    (f1 > f2) ? x3 = x1 + 2 * delta : x3 = x1 - delta;
    double f3 = func(x3);
    double xmin = comparator(x1, x2, x3);
    double fmin = func(xmin);
    double x_ = formula(x1, x2, x3);
    cout << "x1 = " << x1 << ' '
         << "x2 = " << x2 << ' '
         << "x3 = " << x3 << ' '
         << "x~ = " << x_ << endl;
    if ((fmin - func(x_))/func(x_) < eps && (xmin - x_)/x_ < eps)
        cout << "Min is " << func(x_) << " @x=" << x_ << endl;
    else interpolation(x1 + delta, x_, x3 - delta, eps, delta);
}

void execute(function<void (double, double, double, double, double)> f, string name) {
    clock_t start, end;
    double time_taken;
    start = clock();
    cout << name << " method results:" << endl;
    f(x1, x2, x3, eps, delta);
    end = clock();
    time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Computation took "
         << time_taken << " sec" << endl << endl;
}

int main() {
    execute(interpolation, "Interpolation");
    return 0;
}
