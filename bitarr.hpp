#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <iostream>

constexpr int BITS_IN_BYTE = 8;
constexpr int CHUNK_SIZE = 32;

class BitArr {
public:
    void setBit(size_t index, bool value);
    void operator += (bool value);
    bool operator[](size_t index) const;
    size_t getLen() const;
    std::string toString();
    BitArr operator + (bool value) const;
    void operator += (const BitArr&);
    friend std::ostream& operator << (std::ostream&, const BitArr&);
private:
    std::vector<uint8_t> buffer;
    size_t len = 0;
};