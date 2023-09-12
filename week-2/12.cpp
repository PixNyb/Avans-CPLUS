#include <iostream>
#include <string>

class City {
  int _population;
  std::string _name;

public:
  City(int population, const std::string &name)
      : _population{population}, _name{name} {};

  int getPopulation() const;
  void setPopulation(int newPopulation);

  std::string &getName();
  void setName(const std::string &newName);
};

int populationDifference(const City &city, const City &other) {
  return city.getPopulation() - other.getPopulation();
}

int City::getPopulation() const { return _population; }
void City::setPopulation(int newPopulation) { _population = newPopulation; }
std::string &City::getName() { return _name; }
void City::setName(const std::string &newName) { _name = newName; }