#include <iostream>

void cbr(int &param) { param += 10; }

int main() {
  int a = 5;
  cbr(a);
  std::cout << "a: " << a << std::endl;
  return 0;
}