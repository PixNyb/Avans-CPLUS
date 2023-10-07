#include "mrf.hpp" // your solution is in here
#include <iostream>
#include <vector>

void print_vector_of_int(const std::vector<int> &vec) {
  for (int i : vec) {
    std::cout << i << " ";
  }
  std::cout << '\n';
}

int main() {
  // start with a list of some numbers
  std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8};

  // map onto a list with numberstwice as big
  std::vector<int> twice{
      fun::map<int, int>(numbers, [](int elem) { return elem * 2; })};
  print_vector_of_int(twice);

  // filter all odd values from numbers
  std::vector<int> odd{
      fun::filter<int>(numbers, [](int elem) { return elem % 2 != 0; })};
  print_vector_of_int(odd);

  // calculate the sum of all numbers
  std::cout << fun::reduce<int, int>(numbers, 0, [](int elem, int acc) {
    return elem + acc;
  }) << '\n';
}