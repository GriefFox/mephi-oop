#ifndef TABLE_HPP
#define TABLE_HPP

#include <cstddef>
#include <functional>
#include <memory>
#include <stdexcept>

namespace zasada {

/**
 * @class Table
 * @brief A template class implementing a hash table with separate chaining for key-value pairs.
 * 
 * This class provides basic functionality for inserting, erasing, finding, and iterating through 
 * key-value pairs stored in a hash table.
 * 
 * @tparam Key Type of the key used in the table.
 * @tparam T Type of the value associated with the key.
 * @tparam Hash Hash function used to hash the keys.
 * @tparam KeyEqual Function to compare the keys for equality.
 * @tparam Allocator Allocator used for memory management.
 */
template <class Key, class T, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>, class Allocator = std::allocator<std::pair<const Key, T>>>
class Table {
public:
    /**
     * @struct Node
     * @brief A structure representing a node in the hash table.
     * 
     * Each node contains a key, a value, and a pointer to the next node in case of a collision.
     */
    struct Node {
        Key key; ///< The key associated with the value.
        T value; ///< The value associated with the key.
        Node* next; ///< Pointer to the next node in the chain.

        /**
         * @brief Constructor for Node.
         * @param k The key to store.
         * @param v The value to store.
         */
        Node(const Key& k, const T& v) : key(k), value(v), next(nullptr) {}
    };

    /**
     * @brief Constructs a Table with the given capacity.
     * @param capacity The initial capacity of the table. Default is 26.
     */
    Table(size_t capacity = 26);

    /**
     * @brief Destructor that frees all dynamically allocated memory.
     */
    ~Table();

    /**
     * @brief Inserts a key-value pair into the table.
     * 
     * Throws an exception if the key already exists in the table.
     * @param key The key to insert.
     * @param value The value to associate with the key.
     * @throws std::runtime_error if the key already exists.
     */
    void insert(const Key& key, const T& value);

    /**
     * @brief Erases a key-value pair from the table.
     * @param key The key to erase.
     * @return True if the key was found and erased, false otherwise.
     */
    bool erase(const Key& key);

    /**
     * @brief Finds the value associated with a given key.
     * @param key The key to search for.
     * @return A pointer to the value associated with the key, or nullptr if not found.
     */
    T* find(const Key& key);

    /**
     * @brief Gets the number of key-value pairs in the table.
     * @return The size of the table.
     */
    size_t size() const;

    /**
     * @class Iterator
     * @brief An iterator for iterating through the key-value pairs in the table.
     */
    class Iterator {
    public:
        /**
         * @brief Constructor for the iterator.
         * @param table The hash table to iterate over.
         * @param tableSize The number of buckets in the table.
         * @param startIndex The index to start the iteration from (default is 0).
         */
        Iterator(Node** table, size_t tableSize, size_t startIndex = 0);

        /**
         * @brief Checks if two iterators are not equal.
         * @param other The other iterator to compare with.
         * @return True if the iterators are not equal, false otherwise.
         */
        bool operator!=(const Iterator& other) const;

        /**
         * @brief Advances the iterator to the next element.
         * @return A reference to the updated iterator.
         */
        Iterator& operator++();

        /**
         * @brief Dereferences the iterator to get the current key-value pair.
         * @return The key-value pair.
         */
        std::pair<const Key, T&> operator*() const;

    private:
        Node** table; ///< The hash table being iterated.
        size_t bucketIndex; ///< The current bucket index.
        Node* currentNode; ///< The current node in the iteration.
        size_t tableSize; ///< The total number of buckets in the table.

        /**
         * @brief Advances the iterator to the next valid node in the table.
         */
        void advanceToNextValid();
    };

    /**
     * @brief Returns an iterator to the first key-value pair in the table.
     * @return An iterator to the first element.
     */
    Iterator begin();

    /**
     * @brief Returns an iterator to one past the last key-value pair in the table.
     * @return An iterator to the end.
     */
    Iterator end();

private:
    Node** table; ///< The hash table represented as an array of pointers to nodes.
    size_t _size; ///< The number of key-value pairs in the table.
    size_t _capacity; ///< The capacity of the hash table.
    Hash hash_fn; ///< The hash function.
    KeyEqual key_eq; ///< The function to compare keys.

    /**
     * @brief Computes the hash value of a key.
     * @param key The key to hash.
     * @return The computed hash value.
     */
    size_t hash_func(const Key& key) const;
};

// Implementations of the methods
template <class Key, class T, class Hash, class KeyEqual, class Allocator>
zasada::Table<Key, T, Hash, KeyEqual, Allocator>::Table(size_t capacity)
    : _size(0), _capacity(capacity), hash_fn(Hash()), key_eq(KeyEqual()) {
    table = new Node*[_capacity];
    for (size_t i = 0; i < _capacity; ++i) {
        table[i] = nullptr;
    }
}

template <class Key, class T, class Hash, class KeyEqual, class Allocator>
zasada::Table<Key, T, Hash, KeyEqual, Allocator>::~Table() {
    if (table == nullptr) return;
    for (size_t i = 0; i < _capacity; ++i) {
        Node* current = table[i];
        while (current) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
    delete[] table;
    table = nullptr;
    _capacity = 0;
    _size = 0;
}

template <class Key, class T, class Hash, class KeyEqual, class Allocator>
void Table<Key, T, Hash, KeyEqual, Allocator>::insert(const Key& key, const T& value) {
    auto tmp = this->find(key);
    if (tmp != nullptr){
        throw std::runtime_error("Such element already exists");
    }
    size_t index = hash_func(key);
    Node* newNode = new Node(key, value);
    newNode->next = table[index];
    table[index] = newNode;
    ++_size;
}

template <class Key, class T, class Hash, class KeyEqual, class Allocator>
bool Table<Key, T, Hash, KeyEqual, Allocator>::erase(const Key& key) {
    size_t index = hash_func(key);
    Node* current = table[index];
    Node* prev = nullptr;

    while (current) {
        if (key_eq(current->key, key)) {
            if (prev) {
                prev->next = current->next;
            } else {
                table[index] = current->next;
            }
            delete current;
            --_size;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

template <class Key, class T, class Hash, class KeyEqual, class Allocator>
T* Table<Key, T, Hash, KeyEqual, Allocator>::find(const Key& key) {
    size_t index = hash_func(key);
    Node* current = table[index];

    while (current) {
        if (key_eq(current->key, key)) {
            return &(current->value);
        }
        current = current->next;
    }
    return nullptr;
}

template <class Key, class T, class Hash, class KeyEqual, class Allocator>
size_t Table<Key, T, Hash, KeyEqual, Allocator>::size() const {
    return _size;
}

template <class Key, class T, class Hash, class KeyEqual, class Allocator>
size_t Table<Key, T, Hash, KeyEqual, Allocator>::hash_func(const Key& key) const {
    return hash_fn(key) % _capacity;
}

template <class Key, class T, class Hash, class KeyEqual, class Allocator>
Table<Key, T, Hash, KeyEqual, Allocator>::Iterator::Iterator(Node** table, size_t tableSize, size_t startIndex)
    : table(table), bucketIndex(startIndex), currentNode(nullptr), tableSize(tableSize) {
    advanceToNextValid();
}

template <class Key, class T, class Hash, class KeyEqual, class Allocator>
bool Table<Key, T, Hash, KeyEqual, Allocator>::Iterator::operator!=(const Iterator& other) const {
    return currentNode != other.currentNode;
}

template <class Key, class T, class Hash, class KeyEqual, class Allocator>
typename Table<Key, T, Hash, KeyEqual, Allocator>::Iterator& Table<Key, T, Hash, KeyEqual, Allocator>::Iterator::operator++() {
    if (currentNode) {
        currentNode = currentNode->next;
    }
    if (!currentNode) {
        ++bucketIndex;
        advanceToNextValid();
    }
    return *this;
}

template <class Key, class T, class Hash, class KeyEqual, class Allocator>
std::pair<const Key, T&> Table<Key, T, Hash, KeyEqual, Allocator>::Iterator::operator*() const {
    return {currentNode->key, currentNode->value};
}

template <class Key, class T, class Hash, class KeyEqual, class Allocator>
void Table<Key, T, Hash, KeyEqual, Allocator>::Iterator::advanceToNextValid() {
    while (bucketIndex < tableSize && !currentNode) {
        currentNode = table[bucketIndex];
        if (!currentNode) {
            ++bucketIndex;
        }
    }
}

template <class Key, class T, class Hash, class KeyEqual, class Allocator>
typename Table<Key, T, Hash, KeyEqual, Allocator>::Iterator Table<Key, T, Hash, KeyEqual, Allocator>::begin() {
    return Iterator(table, _capacity);
}

template <class Key, class T, class Hash, class KeyEqual, class Allocator>
typename Table<Key, T, Hash, KeyEqual, Allocator>::Iterator Table<Key, T, Hash, KeyEqual, Allocator>::end() {
    return Iterator(table, _capacity, _capacity);
}

} // namespace zasada

#endif // TABLE_HPP
