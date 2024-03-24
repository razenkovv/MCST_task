#include <bitset>
#include <iomanip>
#include <iostream>
#include <vector>

#include "bitvector.hpp"
#include "functions.hpp"

int main() {
  // является ли число степенью 2
  // std::vector<short> vec{0, 2, 4, 8, 16, 32, 1, 67, -1, 56, 111};
  // for (auto& v : vec)
  //   std::cout << std::setw(5) << v << ": " << std::boolalpha << func::is_power_of_2(v) << std::endl;

  // генерация случайной выборки
  // std::vector<int> vec{0, -9, 5, 6, 7, -4, 11, 23};
  // auto res = func::random_n(vec, 5);
  // for (auto& r : res)
  //   std::cout << r << " ";
  // std::cout << std::endl;

  std::vector<unsigned char> vec{1, 2, 10, 11, 16, 120, 255};

  bit::BitVector bitvec(35);
  // bit::BitVector bitvec(vec);
  bitvec.flip_bit(3);
  bitvec.flip_bit(5);
  bitvec.flip_bit(8);
  bitvec.flip_bit(9);
  bitvec.flip_bit(10);
  std::cout << "bitvec: " << std::endl;
  std::cout << bitvec.hex_str() << std::endl;
  std::cout << bitvec.binary_str() << std::endl;

  std::cout << std::endl << "bitvec2: " << std::endl;
  auto bitvec2 = bitvec.get_bitvec(0, 16);
  std::cout << bitvec2.hex_str() << std::endl;
  std::cout << bitvec2.binary_str() << std::endl;

  std::cout << std::endl << "bitvec: " << std::endl;
  bitvec.set_bitvec(bitvec2, 9);
  std::cout << bitvec.hex_str() << std::endl;
  std::cout << bitvec.binary_str() << std::endl;

  std::cout << std::endl << "ullong: " << std::endl;
  std::cout << bitvec.to_ullong(1, 18) << std::endl;
  return 0;
}