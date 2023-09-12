#include <iostream>

char *my_name() {
  char *myname = new char[6];
  myname[0] = 'J';
  myname[1] = 'e';
  myname[2] = 'r';
  myname[3] = 'o';
  myname[4] = 'e';
  myname[5] = 'n';
  return myname;
}

int main(int argc, char **argv) {
  char *your_name = my_name();
  for (int i = 0; i < 6; ++i)
    std::cout << your_name[i];
  std::cout << std::endl;
}