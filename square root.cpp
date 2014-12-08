// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <random>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::numeric_limits;
using std::random_device;
using std::uniform_real_distribution;

int Compare(double a, double b);

// @include
double SquareRoot(double x) {
    if (x==1.0)
        return 1.0;
    else if (x > 1.0) {
        double upper_bound = x;
        double lower_bound = 1.0;
        double t = lower_bound + 0.5*(upper_bound-lower_bound);
        while (Compare(t*t,x)!=0) {
            if (t*t < x)
                t = 0.5*upper_bound + 0.5*t;
            else if (t*t > x)
                t = 0.5*lower_bound + 0.5*t;
            else
                return t;
        }
        return t;
    }
}

// 0 means equal, -1 means smaller, and 1 means larger.
int Compare(double a, double b) {
  // Uses normalization for precision problem.
  double diff = (a - b) / b;
  return diff < -numeric_limits<double>::epsilon()
             ? -1
             : diff > numeric_limits<double>::epsilon();
}
// @exclude

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 5; ++times) {
    double x;
    if (argc == 2) {
      x = atof(argv[1]);
    } else {
      uniform_real_distribution<double> dis(0.0, 10000.0);
      x = dis(gen);
    }
    double res[2];
    cout << "x is " << x << endl;
    cout << (res[0] = SquareRoot(x)) << ' ' << (res[1] = sqrt(x)) << endl;
    assert(Compare(res[0], res[1]) == 0);
  }
  return 0;
}
