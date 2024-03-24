#pragma once

#include <algorithm>
#include <random>
#include <type_traits>
#include <vector>

namespace func {

template <typename T>
bool is_power_of_2(T a);

template <typename T>
std::vector<T> random_n(const std::vector<T>& vec, std::size_t n);

}  // namespace func

template <typename T>
bool func::is_power_of_2(T a) {
  if (std::is_floating_point<T>::value)
    return false;
  if (a <= 0)
    return false;
  a = a & (a - 1);  // если a - степень двойки, то в ее двоичном представлении только одна единица
  if (a > 0)
    return false;
  return true;
}

template <typename T>
std::vector<T> func::random_n(const std::vector<T>& vec, std::size_t n) {
  if (n > vec.size()) {
    throw std::runtime_error("n > vec.size()");
  }
  std::random_device rd;
  auto rng = std::default_random_engine(rd());
  std::vector<std::size_t> tmp(vec.size());
  std::iota(tmp.begin(), tmp.end(), 0);
  std::shuffle(tmp.begin(), tmp.end(), rng);
  std::vector<T> res;
  res.reserve(n);
  for (std::size_t i = 0; i < n; ++i) {
    res.push_back(vec[tmp[i]]);
  }
  return res;
}