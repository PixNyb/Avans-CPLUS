#include <iostream>

void cbv(int param) { param += 10; }

int main() {
  int a = 5;
  cbv(a);
  std::cout << "a: " << a << std::endl;
  return 0;
}
