#include <iostream>

struct Favourites {
  char letter;
  int prime;
  char digit;
};

// pass by value
void show_favourites_by_value(Favourites f) {
  std::cout << "Favourite letter: " << f.letter << std::endl;
  std::cout << "Favourite prime: " << f.prime << std::endl;
  std::cout << "Favourite digit: " << f.digit << std::endl;
  std::cout << std::endl;
}

// pass by reference
void show_favourites_by_reference(Favourites &f) {
  std::cout << "Favourite letter: " << f.letter << std::endl;
  std::cout << "Favourite prime: " << f.prime << std::endl;
  std::cout << "Favourite digit: " << f.digit << std::endl;
  std::cout << std::endl;
}

// pass by pointer
void show_favourites_by_pointer(Favourites *p) {
  std::cout << "Favourite letter: " << p->letter << std::endl;
  std::cout << "Favourite prime: " << p->prime << std::endl;
  std::cout << "Favourite digit: " << p->digit << std::endl;
  std::cout << std::endl;
}

void set_prime(Favourites &f, int prime) { f.prime = prime; }

int main() {
  Favourites my_favourites;
  my_favourites.letter = 'J';
  my_favourites.prime = 11;
  my_favourites.digit = '9';
  std::cout << "Hey, my favourite letter is " << my_favourites.letter
            << std::endl
            << std::endl;

  std::cout << "show_favourites_by_value:" << std::endl;
  show_favourites_by_value(my_favourites);
  std::cout << "show_favourites_by_reference:" << std::endl;
  show_favourites_by_reference(my_favourites);
  std::cout << "show_favourites_by_pointer:" << std::endl;
  show_favourites_by_pointer(&my_favourites);
}
