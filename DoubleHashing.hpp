#pragma once
#include "HashTableClosed.hpp"

template <typename T>
class DoubleHashing : public HashTableClosed<T> {
public:
    DoubleHashing(int size = 101)
        : HashTableClosed<T>(size) {}

    int hash2(const T& key) const {
        // Primary hash is key % M, Secondary is 1 + (key % (M-1))
        return 1 + (static_cast<int>(key) % (this->M - 1));
    }

    int probeIndex(const T& key, int i) const override {
        // Formula: (h1(key) + i * h2(key)) % M
        int h1 = this->hash(key);
        int h2 = hash2(key);
        return (h1 + i * h2) % this->M;
    }
};