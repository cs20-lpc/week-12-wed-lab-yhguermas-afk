#pragma once

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

        // If slot is empty, insert and return probes
        if (!table[index].occupied) {
            table[index].data = key;
            table[index].occupied = true;
            return probes;
        }

        // If key already exists, do not insert, just return probes
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

        // 1. If we find the key, return true
        if (table[index].occupied && table[index].data == key) {
            return {true, probes};
        }

        // 2. CRITICAL FIX: If we hit an EMPTY slot, the key CANNOT 
        // exist further down the probe sequence. Stop and return false.
        if (!table[index].occupied) {
            return {false, probes};
        }
    }
    return {false, probes};
}