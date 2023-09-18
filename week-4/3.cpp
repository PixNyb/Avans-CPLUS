#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string text = "Hello, world!";
  std::vector<char> buffer(text.begin(), text.end());

  // Copy via indexing
  std::vector<char> buffer_index(text.size());
  for (int i = 0; i < text.size(); i++) {
    buffer_index[i] = text[i];
  }

  // Copy via pointers
  std::vector<char> buffer_pointer(text.size());
  char *ptr = &buffer_pointer[0];
  for (char c : text) {
    *ptr++ = c;
  }

  // Print contents of vector
  std::cout << "Buffer: ";
  for (char c : buffer) {
    std::cout << c;
  }
  std::cout << std::endl;

  std::cout << "Buffer (indexing): ";
  for (char c : buffer_index) {
    std::cout << c;
  }
  std::cout << std::endl;

  std::cout << "Buffer (pointers): ";
  for (char c : buffer_pointer) {
    std::cout << c;
  }
  std::cout << std::endl;

  return 0;
}
