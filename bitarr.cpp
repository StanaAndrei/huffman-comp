#include "bitarr.hpp"

#include <cassert>

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

void BitArr::appendBit(bool value) {
    if (len == BITS_IN_BYTE * this->buffer.size()) {
        this->buffer.resize(this->buffer.size() + CHUNK_SIZE);
    }
    this->setBit(len++, value);
}

bool BitArr::operator[](size_t index) const {
    size_t byteId = index / BITS_IN_BYTE;
    size_t bitId = index % BITS_IN_BYTE;
    return (this->buffer[byteId] >> bitId) & 1;
}

inline size_t BitArr::getLen() const {
    return this->len;
}