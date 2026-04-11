#pragma once

template <typename T>
HashTableClosed<T>::HashTableClosed(int size) {
    M = size;
    table = new Entry[M];
    for (int i = 0; i < M; i++) {
        table[i].occupied = false;
    }
}

template <typename T>
HashTableClosed<T>::~HashTableClosed() {
    delete[] table;
}

template <typename T>
int HashTableClosed<T>::hash(const T& key) const {
    // Ensure the result is always positive
    return (static_cast<int>(key) % M + M) % M;
}

template <typename T>
int HashTableClosed<T>::insert(const T& key) {
    int probes = 0;
    for (int i = 0; i < M; i++) {
        int index = probeIndex(key, i);
        probes++;

        // If slot is empty, insert the key
        if (!table[index].occupied) {
            table[index].data = key;
            table[index].occupied = true;
            return probes;
        }

        // If duplicate is found, we stop and return the probes taken to find it
        if (table[index].data == key) {
            return probes;
        }
    }
    return probes; // Table is full
}

template <typename T>
pair<bool, int> HashTableClosed<T>::search(const T& key) const {
    int probes = 0;
    for (int i = 0; i < M; i++) {
        int index = probeIndex(key, i);
        probes++;

        if (table[index].occupied) {
            if (table[index].data == key) {
                return {true, probes};
            }
        } else {
            // STOP searching at the first empty slot.
            // This is required to match the lower "Average probes (search)" values.
            return {false, probes};
        }
    }
    return {false, probes};
}