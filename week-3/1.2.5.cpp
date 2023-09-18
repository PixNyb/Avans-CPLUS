#include "IntVector.hpp"
#include <utility> // for std::move

int main() {
  IntVector v{10};
  IntVector w{v};
  IntVector x = std::move(v);
  x = w;
  x = x;
  w = std::move(w);
  return 0;
}