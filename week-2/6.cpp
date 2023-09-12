#include <iostream>

int *multiply(int x, int y) {
  int *result = new int;
  *result = x * y;
  return result;
}

int main(int argc, char **argv) {
  int *two_times_three = multiply(2, 3);
  std::cout << "2 x 3 = " << *two_times_three << std::endl;
  delete two_times_three;
  return 0;
}