#include "IntVector.hpp"
#include <iostream>

void describe(const IntVector &v) {
  std::cout << "IntVector" << std::endl;
  std::cout << "capacity : " << v.capacity() << std::endl;
  std::cout << "size : " << v.size() << std::endl;
  for (size_t i = 0; i < v.size(); ++i) {
    std::cout << "Element " << i << ": " << v.get(i) << std::endl;
  }
}

int main() {
  IntVector v{10};
  v.push_back(1);
  v.push_back(2);
  describe(v);
}