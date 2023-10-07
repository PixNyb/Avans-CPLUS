#ifndef MFR_H_
#define MFR_H_

#include <algorithm>
#include <functional>
#include <vector>

namespace fun {

template <class T, class M>
std::vector<M> map(const std::vector<T> &seq, std::function<M(T)> fun) {
  std::vector<M> result;
  result.reserve(seq.size());
  std::transform(seq.begin(), seq.end(), std::back_inserter(result), fun);
  return result;
}

template <class T>
std::vector<T> filter(const std::vector<T> &seq, std::function<bool(T)> fun) {
  std::vector<T> result;
  result.reserve(seq.size());
  std::copy_if(seq.begin(), seq.end(), std::back_inserter(result), fun);
  return result;
}

template <class T, class R>
R reduce(const std::vector<T> &seq, R seed, std::function<R(T, R)> fun) {
  std::vector<R> result;
  result.reserve(seq.size());
  std::transform(seq.begin(), seq.end(), std::back_inserter(result),
                 [seed, fun](T elem) { return fun(elem, seed); });
  return result.back();
}

} // namespace fun

#endif // MFR_H_
