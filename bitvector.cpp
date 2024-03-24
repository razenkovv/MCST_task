#include "bitvector.hpp"

std::vector<unsigned char>::const_iterator bit::BitVector::begin() const {
  return bitvector_.begin();
}

std::vector<unsigned char>::iterator bit::BitVector::begin() {
  return bitvector_.begin();
}

std::vector<unsigned char>::const_iterator bit::BitVector::end() const {
  return bitvector_.end();
}

std::vector<unsigned char>::iterator bit::BitVector::end() {
  return bitvector_.end();
}

std::string bit::BitVector::binary_str() const {
  std::stringstream buffer;
  std::vector<unsigned char>::const_iterator it_end;
  if (size_ % CHAR_BIT == 0)
    it_end = bitvector_.end();
  else
    it_end = std::prev(bitvector_.end());
  for (auto it = bitvector_.begin(); it != it_end; ++it)
    buffer << std::bitset<CHAR_BIT>(*it) << " ";
  std::size_t remained = size_ % CHAR_BIT;
  if (remained) {
    for (std::size_t i = size_ - remained; i < size_; ++i)
      buffer << get_bit(i);
  }
  return buffer.str();
}

std::string bit::BitVector::hex_str() const {
  std::stringstream buffer;
  std::bitset<CHAR_BIT> mask(0b00001111);  // assert(CHAR_BIT == 8);
  std::vector<unsigned char>::const_iterator it_end;
  if (size_ % CHAR_BIT == 0)
    it_end = bitvector_.end();
  else
    it_end = std::prev(bitvector_.end());
  for (auto it = bitvector_.begin(); it != it_end; ++it) {
    auto byte = std::bitset<CHAR_BIT>(*it);
    auto lft = std::bitset<CHAR_BIT / 2>(((byte >> 4) & mask).to_ulong()).to_ulong();
    auto rgt = std::bitset<CHAR_BIT / 2>((byte & mask).to_ulong()).to_ulong();
    buffer << std::hex << std::uppercase << lft << rgt << " ";
  }
  std::size_t remained = size_ % CHAR_BIT;
  if (remained) {
    std::bitset<CHAR_BIT> bits(*it_end);
    buffer << std::hex << std::uppercase << (bits >> (CHAR_BIT - remained)).to_ulong();
  }
  return buffer.str();
}

std::size_t bit::BitVector::size() const {
  return size_;
}

bool bit::BitVector::get_bit(std::size_t pos) const {
  std::size_t byte_pos = pos / CHAR_BIT;
  auto byte = std::bitset<CHAR_BIT>(bitvector_[byte_pos]);
  std::bitset<CHAR_BIT> mask(0b10000000);
  mask >>= pos % CHAR_BIT;
  byte &= mask;
  if (byte.count())
    return true;
  return false;
}

void bit::BitVector::set_bit(std::size_t pos, bool val) {
  std::size_t byte_pos = pos / CHAR_BIT;
  auto byte = std::bitset<CHAR_BIT>(bitvector_[byte_pos]);
  std::bitset<CHAR_BIT> mask(0b10000000);
  mask >>= pos % CHAR_BIT;
  if (val) {
    byte |= mask;
  } else {
    mask = ~mask;
    byte &= mask;
  }
  bitvector_[byte_pos] = static_cast<unsigned char>(byte.to_ulong());
}

bool bit::BitVector::flip_bit(std::size_t pos) {
  if (get_bit(pos)) {
    set_bit(pos, false);
    return false;
  } else {
    set_bit(pos, true);
    return true;
  }
}

bit::BitVector bit::BitVector::get_bitvec(std::size_t start, std::size_t end) const {
  if (start % CHAR_BIT == 0 && end % CHAR_BIT == 0) {
    BitVector res(std::vector<unsigned char>(begin() + start / CHAR_BIT, begin() + end / CHAR_BIT));
    return res;
  }
  BitVector res(end - start);
  for (std::size_t i = start, j = 0; i < end; ++i, ++j)
    res.set_bit(j, get_bit(i));
  return res;
}

void bit::BitVector::set_bitvec(const BitVector& bitvec, std::size_t start) {
  if (start % CHAR_BIT == 0 && bitvec.size() % 8 == 0) {
    std::copy(bitvec.begin(), bitvec.end(), begin() + start / CHAR_BIT);
  } else {
    for (std::size_t i = start, j = 0; j < bitvec.size(); ++i, ++j)
      set_bit(i, bitvec.get_bit(j));
  }
}

unsigned int bit::BitVector::to_ullong(std::size_t pos, std::size_t size) const {
  std::bitset<CHAR_BIT * sizeof(unsigned long long)> res;
  for (int i = 0, j = size - 1; j >= 0; ++i, --j)
    res[i] = get_bit(pos + j);
  return res.to_ullong();
}