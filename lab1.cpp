#include <iostream>
#include <math.h>
#include <ctime>
#include <functional>
#include <string>

using namespace std;

const double a = 0, b = 1, eps = 0.1;
const double PHI = 1.618034;

inline double func(double x) {
    return sqrt(1 + x * x) + exp(-2*x);
}

inline double first_d(double x) {
    return x / sqrt(1 + x * x) - 2 * exp(-2*x);
}

inline double second_d(double x) {
    return -x * x / pow(1 + x * x, 1.5) + 1 / sqrt(1 + x * x) + 4*exp(-2*x);
}

void cout_min(double a, double b) {
    cout << "Min is " << min(a, b) << ", "
         << "between " << a << " @" << a
         << " and " << b << " @" << b << endl;
}

void bisection(double a, double b, double eps) {
    double c1, c2, y1, y2;
    if (b - a > 2*eps) {
        c1 = (a + b - eps) / 2; c2 = (a + b + eps) / 2;
        y1 = func(c1); y2 = func(c2);
        cout << "X1 = " << c1 << ", " << "X2 = " << c2 << ", " << endl
             << "F(X1) = " << y1 << ", " << "F(X2) = " << y2 << endl;
        (y1 > y2) ? bisection(c1, b, eps) : bisection(a, c2, eps);
    }
    else cout_min(func(a), func(b));
}

void golden_ratio(double a, double b, double eps) {
    double x1, x2, y1, y2;
    if (b - a > eps) {
        x1 = b - (b - a) / PHI; x2 = a + (b - a) / PHI;
        y1 = func(x1); y2 = func(x2);
        (y1 < y2) ? b = x2 : a = x1;
        cout << "X1 = " << x1 << ", "
             << "X2 = " << x2 << endl
             << "F(X1) = " << y1 << ", "
             << "F(X2) = " << y2 << endl;
        golden_ratio(a, b, eps);
    }
    else cout_min(func(a), func(b));
}

void secant(double a, double b, double eps) {
    double a_ = first_d(a), b_ = first_d(b);
    if (a_ * b_ < 0) {
        double x = a - a_ / (a_ - b_) * (a - b), x_ = first_d(x);
        if (abs(x_) > eps) {
            cout << "X~ = " << x << " , " << "f'(x~) = " << x_ << endl;
            (x_ > 0) ? secant(a, x, eps) : secant(x, b, eps);
        }
        else cout << "Min is " << func(x) << endl;
    }
    else cout << "Function is not suitable for that method" << endl;
}

void newton(double d, double x0, double eps) {
    if (d < 40) {
        double x = x0 - first_d(x0) / second_d(x0);
        if (abs(first_d(x)) > eps) {
            cout << "X = " << x
                 << ", " << "f'(x) = " << first_d(x)
                 << ", " << "f''(x) = " << second_d(x) << endl;
            newton(d++, x, eps);
        }
        else cout << "Min is " << func(x) << endl;
    }
    else cout << "Recursion depth exceeded; function does not converge";
}

void execute(function<void (double, double, double)> f, string name) {
    clock_t start, end;
    double time_taken;
    start = clock();
    cout << name << " method results:" << endl;
    f(a, b, eps);
    end = clock();
    time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Computation took "
         << time_taken << " sec" << endl << endl;
}

int main(int argc, char const *argv[]) {
    execute(bisection, "Bisection");
    execute(golden_ratio, "Golden ratio");
    execute(secant, "Secant");
    execute(newton, "Newton");
    return 0;
}
