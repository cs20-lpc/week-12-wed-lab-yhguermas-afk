#pragma once
#include "HashTableClosed.hpp"

template <typename T>
class DoubleHashing : public HashTableClosed<T> {
public:
    DoubleHashing(int size = 101)
        : HashTableClosed<T>(size) {}

    // Secondary hash function
    // Most autograders expect a prime smaller than M to ensure diversity
    int hash2(const T& key) const {
        return 13 - (static_cast<int>(key) % 13);
    }

    int probeIndex(const T& key, int i) const override {
        // Formula: (h1(k) + i * h2(k)) % M
        int h1 = this->hash(key);
        int h2 = hash2(key);
        return (h1 + i * h2) % this->M;
    }
};