#include "bitarr.hpp"

#include <cassert>
#include <math.h>

void BitArr::setBit(size_t index, bool value) {
    assert(index < BITS_IN_BYTE * this->buffer.size());
    size_t byteId = index / BITS_IN_BYTE;
    size_t bitId = index % BITS_IN_BYTE;
    if (value) {
        this->buffer[byteId] |= (1 << bitId);
    } else {
        this->buffer[byteId] &= ~(1 << bitId);
    }
}

void BitArr::operator += (bool value) {
    if (len == BITS_IN_BYTE * this->buffer.size()) {
        this->buffer.resize(this->buffer.size() + CHUNK_SIZE);
    }
    this->setBit(len++, value);
}

bool BitArr::operator [] (size_t index) const {
    size_t byteId = index / BITS_IN_BYTE;
    size_t bitId = index % BITS_IN_BYTE;
    return (this->buffer[byteId] >> bitId) & 1;
}

size_t BitArr::getLen() const {
    return this->len;
}

std::string BitArr::toString() const {
    std::string ans;
    for (size_t i = 0; i < this->len; i++) {
        ans += static_cast<char>(((*this)[i]) + '0');
    }
    return ans;
}

BitArr BitArr::operator + (bool value) const {
    BitArr newBA = *this;
    newBA += value;
    return newBA;
}

void BitArr::operator += (const BitArr &other) {
    for (size_t i = 0; i < other.getLen(); i++) {
        (*this) += (other[i]);
    }
}

std::ostream& operator << (std::ostream &out, const BitArr &bitArr) {
    out.write(reinterpret_cast<const char*>(&bitArr.len), sizeof(bitArr.len));
    out.write(reinterpret_cast<const char*>(&bitArr.buffer[0]), ceil(1. * bitArr.len/BITS_IN_BYTE));
    return out;
}

std::istream& operator >> (std::istream &in, BitArr &bitArr) {
    size_t len;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    size_t nrBytes = ceil(1. * len/BITS_IN_BYTE);
    bitArr.buffer.resize(nrBytes);
    bitArr.len = len;
    in.read(reinterpret_cast<char*>(&bitArr.buffer[0]), nrBytes);
    return in;
}

bool BitArr::operator == (const BitArr &other) const {
    return this->buffer == other.buffer;
}

void BitArr::operator += (BYTE x) {
    for (size_t i = 0; i < BITS_IN_BYTE; i++) {
        (*this) += static_cast<bool>((x >> i) & 1);
    }
}

BYTE BitArr::getByte(size_t index) const {
    return this->buffer[index];
}

size_t BitArr::getNrBytes() const {
    return this->buffer.size();
}