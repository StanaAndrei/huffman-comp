#pragma once

#include <vector>
#include <cstdint>

constexpr int BITS_IN_BYTE = 8;
constexpr int CHUNK_SIZE = 32;

class BitArr {
public:
    void setBit(size_t index, bool value);
    void appendBit(bool value);
    bool operator[](size_t index) const;
    inline size_t getLen() const;
private:
    std::vector<uint8_t> buffer;
    size_t len;
};