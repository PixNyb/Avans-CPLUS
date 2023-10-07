#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>

class observable {
public:
  observable(int value) : value_{value} {};
  void value(int value) {
    value_ = value;
    for (auto o : observers_) {
      o(value_);
    }
  }
  template <typename Observer> void add_observer(Observer o) {
    observers_.push_back(o);
  }

private:
  int value_;
  std::vector<std::function<void(int)>> observers_;
};

template <typename Iterator, typename Lambda>
void for_all(Iterator begin, Iterator end, Lambda lambda) {
  for (auto it = begin; it != end; ++it) {
    lambda(*it);
  }
}

int main() {
  // Test the observable class
  observable obs{42};
  obs.add_observer(
      [](int value) { std::cout << "Value changed to " << value << "\n"; });
  obs.value(23); // Should print "Value changed to 23"

  // Test the for_all function
  std::vector<int> v{1, 2, 3, 4, 5};
  for_all(v.begin(), v.end(), [](int elem) { return elem * 2; });
  // v should now be {2, 4, 6, 8, 10}
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";

  return 0;
}