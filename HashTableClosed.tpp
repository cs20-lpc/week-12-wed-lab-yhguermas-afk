#pragma once
// Removed #include "HashTableClosed.hpp" to avoid circular dependency

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
    // Ensure negative keys are handled if necessary, 
    // though for this lab, keys are positive.
    return (static_cast<int>(key) % M + M) % M; 
}

template <typename T>
int HashTableClosed<T>::insert(const T& key)
{
    int probes = 0;

    for (int i = 0; i < M; i++) {
        int index = probeIndex(key, i);
        probes++;

        if (!table[index].occupied) {
            table[index].data = key;
            table[index].occupied = true;
            return probes;
        }

        if (table[index].data == key) {
            return probes; // Duplicate found
        }
    }

    return probes; // Table full
}

template <typename T>
pair<bool, int> HashTableClosed<T>::search(const T& key) const
{
    int probes = 0;

    for (int i = 0; i < M; i++) {
        int index = probeIndex(key, i);
        probes++;

        if (table[index].occupied && table[index].data == key) {
            return {true, probes};
        }
        
        // Note: In a standard hash table, you'd stop at an empty slot.
        // However, your lab instructions specify: 
        // "do NOT stop early (grader expects full probe sequence behavior)"
    }

    return {false, probes};
}