#include <iostream>

void copy_string(const char *from, char *to) {
  while (*from) {
    *to = *from;
    from++;
    to++;
  }
  *to = 0;
}

int main(int argc, char **argv) {
  char llama[6];
  copy_string("Llama", llama);
  std::cout << llama << std::endl;
  return 0;
}