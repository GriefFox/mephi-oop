#include "game_headers/Ammo.hpp"
#include <stdexcept>

namespace zasada {

    // Конструктор по умолчанию
    Ammo::Ammo() 
        : name(""), price(0), storage_size(0), current(0), in_storage(0){}

    // Деструктор
    Ammo::~Ammo() {}

    // Геттер для имени
    std::string Ammo::getName() const {
        return name;
    }

    // Геттер для цены
    size_t Ammo::getPrice() const {
        return price;
    }

    // Геттер для размера хранилища
    size_t Ammo::getStorageSize() const {
        return storage_size;
    }

    // Геттер для текущего количества
    size_t Ammo::getCurrent() const {
        return current;
    }

    size_t Ammo::getInStorage() const {
        return in_storage;
    }

    Ammo& Ammo::setName(const std::string& newName) {
        this->name = newName;
        return *this;
    }

    Ammo& Ammo::setPrice(const size_t newPrice) {
        price = newPrice;
        return *this;
    }

    Ammo& Ammo::setStorageSize(const size_t newStorageSize) {
        storage_size = newStorageSize;
        return *this;
    }

    Ammo& Ammo::setCurrent(const size_t newCurrent) {
        current = newCurrent;
        return *this;
    }

    Ammo& Ammo::setInStorage(const size_t amount){
        in_storage = amount;
        return *this;
    }

    Ammo& Ammo::reduce(size_t amount) {
        if (amount > current) {
            throw std::out_of_range("Not enough ammo to reduce");
        }
        current -= amount;
        return *this;
    }

    size_t Ammo::reload(size_t max_am) {
        size_t needed_ammo = max_am - current;
        size_t ammo_to_reload = std::min(needed_ammo, in_storage);
        current += ammo_to_reload;
        in_storage -= ammo_to_reload;

        return ammo_to_reload;
    }

    size_t Ammo::consume(){
        if (current == 0)
            throw std::out_of_range("Not enough ammo to reduce");
        current -= 1;
        return storage_size;
    }

    size_t Ammo::cost(){
        return current * price + in_storage * current;
    }
}