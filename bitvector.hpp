#pragma once

#include <bitset>
#include <iostream>
#include <vector>
#include <sstream>
#include <climits>

namespace bit {

class BitVector final {
 private:
  std::vector<unsigned char> bitvector_;
  std::size_t size_;

 public:
  BitVector(std::size_t size) : bitvector_(size / CHAR_BIT + (size % CHAR_BIT ? 1 : 0)), size_(size) {}
  BitVector(const std::vector<unsigned char>& vector) : bitvector_(vector), size_(vector.size() * CHAR_BIT) {}

  std::vector<unsigned char>::const_iterator begin() const;
  std::vector<unsigned char>::iterator begin();
  std::vector<unsigned char>::const_iterator end() const;
  std::vector<unsigned char>::iterator end();

  std::string binary_str() const;
  std::string hex_str() const;

  std::size_t size() const;

  bool get_bit(std::size_t pos) const;
  void set_bit(std::size_t pos, bool val = true);
  bool flip_bit(std::size_t pos);
  
  BitVector get_bitvec(std::size_t start, std::size_t end) const;
  void set_bitvec(const BitVector& bitvec, std::size_t start);

  unsigned int to_ullong(std::size_t pos, std::size_t size) const;
};

}  // namespace bit