#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

// class Node ---------------------------------------------------

class Node {
public:
  Node(const std::string &name);
  const std::string &name() const;
  void add_neighbor(std::shared_ptr<Node> node);
  std::shared_ptr<Node> neighbor_with_name(const std::string &name);

private:
  std::string _name;
  std::vector<std::weak_ptr<Node>> _neighbors;
};

Node::Node(const std::string &name) : _name{name} {}

const std::string &Node::name() const { return _name; }

void Node::add_neighbor(std::shared_ptr<Node> node) {
  _neighbors.emplace_back(node);
}

std::shared_ptr<Node> Node::neighbor_with_name(const std::string &name) {
  for (auto &elem : _neighbors) {
    auto shp = elem.lock();
    if (shp && shp->name() == name) {
      return shp;
    }
  }
  throw std::out_of_range{"not found"};
}

// class Graph --------------------------------------------------

class Graph {
public:
  Graph() = default;
  void add_node(std::shared_ptr<Node> node);

private:
  std::vector<std::shared_ptr<Node>> _nodes;
};

void Graph::add_node(std::shared_ptr<Node> node) { _nodes.emplace_back(node); }

// main program -------------------------------------------------

int main() {
  Graph graph;
  auto n1 = std::make_shared<Node>("node 1");
  graph.add_node(n1);
  auto n2 = std::make_shared<Node>("node 2");
  graph.add_node(n2);
  auto n3 = std::make_shared<Node>("node 3");
  graph.add_node(n3);
  auto n4 = std::make_shared<Node>("node 4");
  graph.add_node(n4);
  n1->add_neighbor(n2);
  n1->add_neighbor(n3);
  n1->add_neighbor(n4);
  n2->add_neighbor(n4);
  std::cout << n1->neighbor_with_name("node 3")->name() << '\n';
}