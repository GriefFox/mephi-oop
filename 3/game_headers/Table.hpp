#ifndef TABLE_H
#define TABLE_H

#include <unordered_map>
#include <memory>
#include <string>
#include <optional>

namespace zasada{
    template <typename T>
    class Table{
        private:
            struct Node {
                std::string& key;
                std::shared_ptr<T> value;
                Node* next;

                Node(std::string& k, std::shared_ptr<T> v) : key(k), value(v), next(nullptr) {}
            };
            const size_t _size = 26;
            Node **table;

            size_t hash_func(const std::string& k);
        public:
            Table();
            ~Table();

            std::optional<T&> get(const std::string& name);
            size_t getSize() const;
            void append(std::shared_ptr<T>);
            std::optional<T&> pop(const std::string& name);
            
            // class Iterator {
            //     private:
            //         Node** table;
            //         size_t bucketIndex;
            //         Node* currentNode;
            //         size_t tableSize;
            //         void advanceToNextValid() {
            //             while (bucketIndex < tableSize && !currentNode) {
            //                 currentNode = table[bucketIndex];
            //                 if (!currentNode) {
            //                     ++bucketIndex;
            //                 }
            //             }
            //         }
            //     public:
            //         Iterator(Node** table, size_t tableSize, size_t startIndex = 0)
            //             : table(table), bucketIndex(startIndex), currentNode(nullptr), tableSize(tableSize) {
            //             advanceToNextValid();
            //         }

            //         bool operator!=(const Iterator& other) const {
            //             return currentNode != other.currentNode;
            //         }

            //         Iterator& operator++() {
            //             if (currentNode) {
            //                 currentNode = currentNode->next;
            //             }
            //             if (!currentNode) {
            //                 ++bucketIndex;
            //                 advanceToNextValid();
            //             }
            //             return *this;
            //         }

            //         T& operator*() const {
            //             return *(currentNode->value);
            //         }
            //     };

            // Iterator begin() {
            //     return Iterator(table, _size);
            // }

            // Iterator end() {
            //     return Iterator(table, _size, _size);
            // }

    };
} // namespace zasada

#endif