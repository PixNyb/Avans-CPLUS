#include <iostream>
#include <stdexcept>

double calc(double a, double b) {
  double *numbers = new double[1000];
  try {
    if (b == 0)
      throw std::runtime_error("divide by zero");
    double result = a / b;
    return result;
  } catch (...) {
    delete[] numbers;
    throw;
  }
}

int main() {
  std::cout << calc(3, 2) << '\n';
  std::cout << calc(1, 0) << '\n';
  std::cout << calc(6, 7) << '\n';
  std::cout << calc(355, 113) << '\n';
}