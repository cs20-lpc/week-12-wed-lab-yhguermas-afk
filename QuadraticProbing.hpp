#pragma once
#include "HashTableClosed.hpp"

template <typename T>
class QuadraticProbing : public HashTableClosed<T> {
public:
    QuadraticProbing(int size = 101)
        : HashTableClosed<T>(size) {}

    int probeIndex(const T& key, int i) const override {
        // Formula: (hash(key) + i^2) % M
        return (this->hash(key) + i * i) % this->M;
    }
};