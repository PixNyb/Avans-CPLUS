#include <algorithm> // copy
#include <fstream>   // ifstream
#include <iostream>  // cout
#include <iterator>  // input_iterator
#include <numeric>   // accumulate
#include <vector>

void reset(std::istream &is) {
  is.clear();
  is.seekg(0);
}

int main() {
  std::ifstream f{"input.txt"};

  // Print all even numbers
  std::cout << "Even numbers" << std::endl;
  std::copy_if(std::istream_iterator<int>{f}, std::istream_iterator<int>{},
               std::ostream_iterator<int>{std::cout, "\n"},
               [](int i) { return i % 2 == 0; });
  reset(f);

  // Print all doubled numbers
  std::cout << "Double all numbers and print them" << std::endl;
  std::transform(std::istream_iterator<int>{f}, std::istream_iterator<int>{},
                 std::ostream_iterator<int>{std::cout, "\n"},
                 [](int i) { return i * 2; });
  reset(f);

  // Copy all numbers to a vector using the back_inserter
  std::vector<int> v{};
  std::copy(std::istream_iterator<int>{f}, std::istream_iterator<int>{},
            std::back_inserter(v));
  reset(f);

  // Sort them and print them
  std::cout << "Sorted numbers" << std::endl;
  std::sort(v.begin(), v.end());
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>{std::cout, "\n"});

  std::istream_iterator<int> i_begin{f};
  std::istream_iterator<int> i_end{};
  std::ostream_iterator<int> o_begin{std::cout, "\n"};

  // Calculate the product of all numbers and write them to console using
  // o_begin
  std::cout << "Product of all numbers" << std::endl;
  *o_begin++ =
      std::accumulate(i_begin, i_end, 1, [](int a, int b) { return a * b; });
  // std::sort(i_begin, i_end);
  // std::copy(i_begin, i_end, o_begin);
}
