#include <iostream>

class Student {
  int _number;
  int _age;

public:
  Student(int number) : _number{number} {};
  int getNumber() const { return _number; }
  void setNumber(int newNumber) { _number = newNumber; }
  int getAge() const { return _age; }
  void setAge(int newAge) { _age = newAge; }
  int ageDifference(const Student &other) const {
    return getAge() - other.getAge();
  }
  int futureAge() const { return getAge() + 1; }
};

int main() {
  Student student1{1};
  Student student2{2};

  student1.setAge(20);
  student2.setAge(25);

  std::cout << "Student 1 age: " << student1.getAge() << std::endl;
  std::cout << "Student 2 age: " << student2.getAge() << std::endl;

  std::cout << "Student 1 age difference: " << student1.ageDifference(student2)
            << std::endl;
  std::cout << "Student 2 age difference: " << student2.ageDifference(student1)
            << std::endl;

  std::cout << "Student 1 future age: " << student1.futureAge() << std::endl;
  std::cout << "Student 2 future age: " << student2.futureAge() << std::endl;
}