#pragma once
#include "HashTableClosed.hpp"

template <typename T>
class DoubleHashing : public HashTableClosed<T> {
public:
    DoubleHashing(int size = 101)
        : HashTableClosed<T>(size) {}

    // Original formula from your snippet: 1 + (key % (M - 1))
    int hash2(const T& key) const {
        return 1 + (static_cast<int>(key) % (this->M - 1));
    }

    int probeIndex(const T& key, int i) const override {
        // Formula: (h1(key) + i * h2(key)) % M
        // Ensure the addition and multiplication happen before the modulo
        return (this->hash(key) + i * hash2(key)) % this->M;
    }
};