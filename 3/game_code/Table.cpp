#include "game_headers/Table.hpp"
#include <unordered_map>

namespace zasada {

    template <typename T>
    Table<T>::Table(){
        table = new Node*[_size];
        for (size_t i = 0; i < _size; ++i){
            table[i] = nullptr;
        }
    }

    template <typename T>
    Table<T>::~Table(){
        for (size_t i=0; i<_size; i++){
            Node *head = table[i];
            while(head){
                Node *prev = head;
                head = head->next;
                delete prev;
            }
        }
        delete[] table;
    }

    template <typename T>
    size_t Table<T>::hash_func(const std::string& k){
        int sum = 0;
        for(char c : k){
            sum += c;
        }
        char res = sum%_size;
        return res;
    }

    // Метод для получения корабля по имени
    template <typename T>
    std::optional<T&> Table<T>::get(const std::string& name) {
        size_t ind = hash_func(name);
        Node*head = table[ind];
        while(head != nullptr){
            if(head->key == name){
                return *(head->value);
            }
            head = head->next;
        }
        return std::nullopt;
}

    // Метод для получения размера таблицы
    template <typename T>
    size_t Table<T>::getSize() const {
        size_t amount = 0;
        for (size_t i=0;i<_size;i++){
            Node*head = table[i];
            while(head){
                amount += 1;
                head = head->next;
            }
        }

        return amount;
    }

    // Метод для добавления нового корабля в таблицу
    template <typename T>
    void Table<T>::append(std::shared_ptr<T> new_el) {
        if (!new_el) {
            throw std::invalid_argument("Cannot append a null.");
        }

        // Assume T has a method getName() to retrieve the name
        std::string name;
        try{
            name = new_el->getName();
        } catch(...){
            throw std::runtime_error("Need getName operator");
        }

        // Check for duplicate names
        auto dup = this->get(name);
        if (dup != std::nullopt)
            throw std::invalid_argument("Duplicate!");
        
        size_t ind = hash_func(name);
        Node*head = table[ind];
        Node*nnode = new Node(name, new_el);
        if (head){
            nnode->next = head;
        }
        table[ind] = nnode;
    }

    // Метод для удаления корабля из таблицы
    template <typename T>
    std::optional<T&> Table<T>::pop(const std::string& name) {
        size_t ind = hash_func(name);
        Node*head = table[ind];
        Node*prev = nullptr;

        while(head){
            if (head->key == name){
                if (prev)
                    prev->next = head->next;
                else 
                    table[ind] = head->next;
                auto val = *(head->value);
                delete head;
                return val;
            }

            prev = head;
            head = head->next;
        }
        return std::nullopt;
    }

} // namespace zasada