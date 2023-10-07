#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace linal {

template <typename T> class matrix {
public:
  matrix(std::size_t rows, std::size_t cols)
      : rows_{rows}, cols_{cols}, data_(rows * cols) {}

  matrix() : matrix(0, 0) {}

  matrix(matrix const &other)
      : rows_{other.rows_}, cols_{other.cols_}, data_{other.data_} {}

  matrix(matrix &&other) noexcept
      : rows_{other.rows_}, cols_{other.cols_}, data_{std::move(other.data_)} {}

  matrix &operator=(matrix const &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    data_ = other.data_;
    return *this;
  }

  matrix &operator=(matrix &&other) noexcept {
    rows_ = other.rows_;
    cols_ = other.cols_;
    data_ = std::move(other.data_);
    return *this;
  }

  std::size_t rows() const noexcept { return rows_; }

  std::size_t cols() const noexcept { return cols_; }

  T &operator()(std::size_t row, std::size_t col) { return ix(row, col); }

  T const &operator()(std::size_t row, std::size_t col) const {
    return ix(row, col);
  }

  matrix &operator+=(matrix const &other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
      throw std::invalid_argument{"matrix dimensions do not match"};
    }
    std::transform(data_.begin(), data_.end(), other.data_.begin(),
                   data_.begin(), std::plus<>{});
    return *this;
  }

  matrix &operator-=(matrix const &other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
      throw std::invalid_argument{"matrix dimensions do not match"};
    }
    std::transform(data_.begin(), data_.end(), other.data_.begin(),
                   data_.begin(), std::minus<>{});
    return *this;
  }

  matrix &operator*=(T const &scalar) {
    std::transform(data_.begin(), data_.end(), data_.begin(),
                   [scalar](T const &x) { return x * scalar; });
    return *this;
  }

  friend matrix operator+(matrix const &lhs, matrix const &rhs) {
    matrix result{lhs};
    result += rhs;
    return result;
  }

  friend matrix operator-(matrix const &lhs, matrix const &rhs) {
    matrix result{lhs};
    result -= rhs;
    return result;
  }

  friend matrix operator*(matrix const &lhs, T const &scalar) {
    matrix result{lhs};
    result *= scalar;
    return result;
  }

  friend matrix operator*(T const &scalar, matrix const &rhs) {
    return rhs * scalar;
  }

  friend bool operator==(matrix const &lhs, matrix const &rhs) {
    return lhs.rows_ == rhs.rows_ && lhs.cols_ == rhs.cols_ &&
           std::mismatch(lhs.data_.begin(), lhs.data_.end(), rhs.data_.begin())
                   .first == lhs.data_.end();
  }

  friend bool operator!=(matrix const &lhs, matrix const &rhs) {
    return !(lhs == rhs);
  }

private:
  std::size_t rows_;
  std::size_t cols_;
  std::vector<T> data_;

  T &ix(std::size_t row, std::size_t col) { return data_[row * cols_ + col]; }

  T const &ix(std::size_t row, std::size_t col) const {
    return data_[row * cols_ + col];
  }
};

} // namespace linal