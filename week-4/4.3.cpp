#include <iostream>
#include <memory>
#include <string>

class Widget {
public:
  Widget(const std::string &message);
  const std::string &message() const;

private:
  std::string _message;
};

Widget::Widget(const std::string &message) : _message{message} {}

const std::string &Widget::message() const { return _message; }

void fun(std::shared_ptr<Widget> p) {
  std::cout << p->message() << '\n';
  std::cout << p.use_count() << '\n';
}

int main() {
  auto w = std::make_unique<Widget>("Nice weather today.");
  fun(std::move(w));
  return 0;
}