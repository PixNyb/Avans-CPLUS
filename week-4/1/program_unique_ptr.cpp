#include "myclib.c"
#include <iostream>
#include <memory>

int main() {
  std::unique_ptr<Dinges, decltype(&destroy_dinges)> dinges(create_dinges(),
                                                            &destroy_dinges);
  dinges->name = "Dinges";
  dinges->value = 42;
  std::cout << "Naam : " << dinges->name;
  std::cout << ", Meaning of Life : " << dinges->value;
  std::cout << '\n';
}