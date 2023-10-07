#include <iostream>
using namespace std;

class Aap {
public:
  void klim() {}

private:
  int rugnummer;
  double gewicht;
  char *naam;
};

class Test {
public:
  Test() {
    // lijst = new Aap[10000000];
    cout << teller++ << endl;
    Test *test = new Test();
    int a, b, c, d, e, f, g, h, i, j;
  }

private:
  static int teller;
  static char *lijst;
};

int Test::teller = 0;
int main() {
  Test *t = new Test();
  return 0;
}