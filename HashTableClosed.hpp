#pragma once
#include <utility>
using namespace std;

template <typename T>
class HashTableClosed {
protected:
    struct Entry {
        T data;
        bool occupied;
    };

    Entry* table;
    int M;

    virtual int probeIndex(const T& key, int i) const = 0;

public:
    HashTableClosed(int size);
    virtual ~HashTableClosed();

    int hash(const T& key) const;

    int insert(const T& key);
    pair<bool, int> search(const T& key) const;
};