#pragma once
#include <utility>
using namespace std;

template <typename T>
HashTableClosed<T>::HashTableClosed(int size)
{
    M = size;
    table = new Entry[M];

    for (int i = 0; i < M; i++) {
        table[i].occupied = false;
    }
}

template <typename T>
HashTableClosed<T>::~HashTableClosed()
{
    delete[] table;
}

template <typename T>
int HashTableClosed<T>::hash(const T& key) const
{
    return static_cast<int>(key) % M;
}

template <typename T>
int HashTableClosed<T>::insert(const T& key)
{
    int probes = 0;

    for (int i = 0; i < M; i++) {
        int index = probeIndex(key, i);
        probes++;

        // empty slot → insert
        if (!table[index].occupied) {
            table[index].data = key;
            table[index].occupied = true;
            return probes;
        }

        // duplicate key → stop
        if (table[index].data == key) {
            return probes;
        }
    }

    return probes;
}

template <typename T>
pair<bool, int> HashTableClosed<T>::search(const T& key) const
{
    int probes = 0;

    for (int i = 0; i < M; i++) {
        int index = probeIndex(key, i);
        probes++;

        // found key
        if (table[index].occupied && table[index].data == key) {
            return {true, probes};
        }

        // IMPORTANT: stop early if empty slot is hit
        if (!table[index].occupied) {
            return {false, probes};
        }
    }

    return {false, probes};
}