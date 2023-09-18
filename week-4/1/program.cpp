#include "myclib.c"
#include <iostream>

class DingesRaii {
public:
  DingesRaii(Dinges *d) { _d = d; }
  ~DingesRaii() { destroy_dinges(_d); }
  Dinges *get() { return _d; }

private:
  Dinges *_d;
};

int main() {
  Dinges *dinges = create_dinges();
  DingesRaii dinges_raii(dinges);
  dinges->name = "Dinges";
  dinges->value = 42;
  std::cout << "Naam : " << dinges->name;
  std::cout << ", Meaning of Life : " << dinges->value;
  std::cout << '\n';
}