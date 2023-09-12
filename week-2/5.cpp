#include <iostream>
#include <string>
using namespace std;

class Week {
private:
  int _week_num;

public:
  Week(int num) : _week_num{num} {};
  int week_number() { return _week_num; }
};

class Day {
private:
  string _name;
  Week *_week;

public:
  Day(string name, Week *week) : _name{name}, _week{week} {};
  string &name_of_day() { return _name; }
  Week *week() { return _week; }
};

int main() {
  Day *day = nullptr;
  // your code here

  Week *week = new Week(2);
  day = new Day("Monday", week);

  // end of your code
  cout << "It's the " << day->name_of_day() << " in week "
       << day->week()->week_number() << "!" << endl;
  // your code here

  delete day;
  delete week;

  // end of your code
  return 0;
}