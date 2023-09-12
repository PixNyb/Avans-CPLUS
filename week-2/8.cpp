#include <iostream>

int string_length(char *str) {
  int result = 0;
  while (*str) { // don't change this line!
    result++;
    str++;
  }
  return result;
}

void not_safe() {
  char lowercase[17];
  char uppercase[17];
  for (int i = 0; i < 16; ++i)
    lowercase[i] = 'a' + i;
  for (int i = 0; i < 16; ++i)
    uppercase[i] = 'A' + i;

  lowercase[16] = 0;
  uppercase[16] = 0;

  std::cout << string_length(lowercase) << std::endl;
  std::cout << string_length(uppercase) << std::endl;
}

int main() {
  char my_favourite_animal[] = "Llama"; // an array of 6 elements!
  char harrys_favourite_animal[] = {'L', 'l', 'a', 'm', 'a', 0};

  std::cout << "string_length(\"Llama\") == " << string_length("Llama")
            << std::endl;
  std::cout << "string_length(\"Guanaco\") == " << string_length("Guanaco")
            << std::endl;

  std::cout << "string_length(my_favourite_animal) == "
            << string_length(my_favourite_animal) << std::endl;
  std::cout << "string_length(harrys_favourite_animal) == "
            << string_length(harrys_favourite_animal) << std::endl;

  not_safe();
}