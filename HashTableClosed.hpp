#pragma once
#include <utility>
using namespace std;

template <typename T>
class HashTableClosed {
protected:
    struct Entry {
        T data;
        bool occupied;

        Entry() : occupied(false) {}
    };

    Entry* table;
    int M;

public:
    HashTableClosed(int size = 101);
    ~HashTableClosed();

    int hash(const T& key) const;

    virtual int probeIndex(const T& key, int i) const = 0;

    int insert(const T& key);
    pair<bool, int> search(const T& key) const;
};

#include "HashTableClosed.tpp"