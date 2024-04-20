#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <iostream>

#include "defs.hpp"


constexpr int BITS_IN_BYTE = 8;
constexpr int CHUNK_SIZE = 1;

class BitArr {
public:
    void setBit(size_t index, bool value);
    void operator += (bool value);
    bool operator[](size_t index) const;
    size_t getLen() const;
    std::string toString() const;
    BitArr operator + (bool value) const;
    void operator += (const BitArr&);
    friend std::ostream& operator << (std::ostream&, const BitArr&);
    friend std::istream& operator >> (std::istream&, BitArr&);
    bool operator == (const BitArr&) const;
    void operator += (BYTE);
    BYTE getByte(size_t) const;
    size_t getNrBytes() const;
private:
    std::vector<BYTE> buffer;
    size_t len = 0;
};