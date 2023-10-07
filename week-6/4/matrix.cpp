#define CATCH_CONFIG_MAIN
#include "matrix.hpp"
#include "catch.hpp"

TEST_CASE("A matrix can be constructed using initializer lists") {

  linal::matrix<int> m = {{1, 2, 3}, {3, 4, 5}};
  REQUIRE(m.rows() == 2);
  REQUIRE(m.cols() == 3);
  REQUIRE(m(0, 2) == 3);
}

TEST_CASE("A default constructed matrix is a 1x1 of value 0") {
  linal::matrix<int> m{};
  REQUIRE(m.rows() == 1);
  REQUIRE(m.cols() == 1);
  REQUIRE(m.ix(0, 0) == 0);
}

TEST_CASE("Two matrices can be added") {
  linal::matrix<int> const m{3, 3, 1};
  linal::matrix<int> const n{3, 3, 2};
  auto const o = m + n;
  for (std::size_t i = 0; i < o.rows(); ++i) {
    for (std::size_t j = 0; j < o.rows(); ++j) {
      REQUIRE(o(i, j) == m(i, j) + n(i, j));
    }
  }
}

TEST_CASE("Two matrices can be subtracted") {
  linal::matrix<int> const m{3, 3, 1};
  linal::matrix<int> const n{3, 3, 2};
  auto const o = m - n;
  for (std::size_t i = 0; i < o.rows(); ++i) {
    for (std::size_t j = 0; j < o.rows(); ++j) {
      REQUIRE(o(i, j) == m(i, j) - n(i, j));
    }
  }
}

TEST_CASE("A matrix can be scaled") {
  linal::matrix<int> m{2, 2, 1};
  m *= 2;
  REQUIRE(m(0, 0) == 2);
  auto const n = m * 2;
  REQUIRE(n(0, 0) == 4);
  auto const l = 2 * m;
  REQUIRE(l(0, 0) == 4);
}

TEST_CASE("Two matrices can be compared") {
  linal::matrix<int> const m{{1, 2}, {3, 4}};
  linal::matrix<int> const n{{1, 2}, {3, 4}};
  REQUIRE(m == n);
  REQUIRE(n == m);
  linal::matrix<int> const l{{2, 2}, {3, 4}};
  REQUIRE(m != l);
  REQUIRE(l != m);
}