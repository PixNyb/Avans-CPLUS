#include "alpacallama.cpp"
#include <iostream>

int main() {
  Farm f{};
  f.add_llama(std::make_unique<Llama>(10));
  f.add_alpaca(std::make_unique<Alpaca>(false));

  Farm g{};
  g.add_animal<Llama>(20);
  g.add_animal<Alpaca>(true);

  std::cout << "Farm f:\n";
  f.inspect();
  std::cout << "Farm g:\n";
  g.inspect();

  std::cout << "Farm f reversed:\n";
  f.reverse_inspect();
  std::cout << "Farm g reversed:\n";
  g.reverse_inspect();
}
