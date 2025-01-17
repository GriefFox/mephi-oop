#include "game_headers/Weapon.hpp"

namespace zasada {

    // Определение конструктора по умолчанию
    Weapon::Weapon()
        : damage(0), ammo(nullptr), name(""), activity(false), range(0),
          fire_rate(0), reload_time(0), reload_left(0), price(0) {}
    
    Weapon::~Weapon() {}

    Weapon::Weapon(size_t _damage, 
        std::shared_ptr<Ammo> _ammo, 
        std::string _name, 
        bool _activity, 
        const size_t _max_ammo, 
        size_t _range, 
        size_t _fire_rate, 
        const size_t _reload_time, 
        size_t _reload_left, 
        size_t _price): 
        damage(_damage),
        ammo(_ammo),
        name(_name),
        activity(_activity),
        max_ammo(_max_ammo),
        range(_range),
        fire_rate(_fire_rate),
        reload_time(_reload_time),
        reload_left(_reload_left),
        price(_price)
        {}

    // getters
    weapon_t Weapon::getType() const{
        return type;
    }

    size_t Weapon::getDamage() const {
        return damage;
    }

    std::shared_ptr<Ammo> Weapon::getAmmo() const {
        if (ammo == nullptr) {
            throw std::runtime_error("Ammo is not set");
        }
        return ammo;
    }

    std::string Weapon::getName() const {
        return name;
    }

    bool Weapon::getActivity() const {
        return activity;
    }

    size_t Weapon::getRange() const {
        return range;
    }

    size_t Weapon::getMaxAmmo() const {
        return max_ammo;
    }

    size_t Weapon::getFireRate() const {
        return fire_rate;
    }

    size_t Weapon::getReloadTime() const {
        return reload_time;
    }

    size_t Weapon::getReloadLeft() const
    {
        return reload_left;
    }
    size_t Weapon::getPrice() const
    {
        return price;
    }

    // Реализация сеттеров
    Weapon& Weapon::setDamage(size_t dmg) {
        damage = dmg;
        return *this;
    }

    Weapon& Weapon::setAmmo(std::shared_ptr<Ammo>  newAmmo) {
        ammo = newAmmo;
        return *this;
    }

    Weapon& Weapon::setName(const std::string& newName) {
        name = newName;
        return *this;
    }

    Weapon& Weapon::setActivity(bool isActive) {
        activity = isActive;
        return *this;
    }

    Weapon& Weapon::setRange(size_t newRange) {
        range = newRange;
        return *this;
    }

    Weapon& Weapon::setFireRate(size_t newFireRate) {
        fire_rate = newFireRate;
        return *this;
    }

    Weapon& Weapon::setReloadLeft(size_t newReloadTime) {
        reload_left = newReloadTime;
        return *this;
    }

    Weapon& Weapon::setPrice(size_t newPrice) {
        price = newPrice;
        return *this;
    }

size_t Weapon::reload() {
    if (!activity)
        return 0;

    size_t ammo_to_reload = ammo->reload(max_ammo);

    // Set reload time and deactivate the weapon
    reload_left = reload_time;
    activity = false;

    return ammo_to_reload * ammo->getStorageSize();
}

    void Weapon::tick(){
        if (reload_left == 0)
            activity = true;
        if (reload_left > 0)
            reload_left--;
    }

    size_t Weapon::fire(double distance, std::shared_ptr<Ship> to){
        throw std::runtime_error("This weapon cannot fire at ships");
    }

    size_t Weapon::fire(double distance, std::shared_ptr<Plane> to){
        throw std::runtime_error("This weapon cannot fire at planes");
    }

    void Weapon::fireAsync(double distance, std::shared_ptr<Ship> to) {
        std::thread([this, distance, to]() {
            std::lock_guard<std::mutex> lock(mtx);
            this->fire(distance, to);
        }).detach();  // Detach thread to run asynchronously
    }

    void Weapon::fireAsync(double distance, std::shared_ptr<Plane> to) {
        std::thread([this, distance, to]() {
            std::lock_guard<std::mutex> lock(mtx);
            this->fire(distance, to);
        }).detach();  // Detach thread to run asynchronously
    }

    size_t Weapon::cost(){
        return price;
    }

    LightWeapon::LightWeapon(size_t _damage, 
        std::shared_ptr<Ammo> _ammo, 
        std::string _name, 
        bool _activity, 
        const size_t _max_ammo, 
        size_t _range, 
        size_t _fire_rate, 
        const size_t _reload_time, 
        size_t _reload_left, 
        size_t _price)
        : Weapon(_damage, _ammo, _name, _activity, _max_ammo, _range, _fire_rate, _reload_time, _reload_left, _price) {
        type = light;
    }

    HeavyWeapon::HeavyWeapon(size_t _damage, 
        std::shared_ptr<Ammo> _ammo, 
        std::string _name, 
        bool _activity, 
        const size_t _max_ammo, 
        size_t _range, 
        size_t _fire_rate, 
        const size_t _reload_time, 
        size_t _reload_left, 
        size_t _price)
        : Weapon(_damage, _ammo, _name, _activity, _max_ammo, _range, _fire_rate, _reload_time, _reload_left, _price){
            type=heavy;
    }

    size_t HeavyWeapon::fire(double distance, std::shared_ptr<Ship> to) {
        if (!activity)
            return 0;

        // Check if the target is within range
        if (distance > range) {
            return 0; // Target is out of range
        }

        size_t consumed = 0;
        try {
            consumed = ammo->consume();
        } catch (const std::out_of_range& e) {
            return 0; // No ammo left to fire
        }

        to->takeDamage(damage);
        return consumed;
    }

    size_t LightWeapon::fire(double distance, std::shared_ptr<Plane> to) {
        if (!activity)
            return 0;

        // Check if the target is within range
        if (distance > range) {
            return 0; // Target is out of range
        }

        size_t consumed = 0;
        try {
            consumed = ammo->consume();
        } catch (const std::out_of_range& e) {
            return 0; // No ammo left to fire
        }

        to->takeDamage(damage);
        return consumed;
    }

    size_t LightWeapon::fire(double, std::shared_ptr<Ship>){
        throw std::runtime_error("Can't hit a ship with light weapon");
    }

    size_t HeavyWeapon::fire(double, std::shared_ptr<Plane>){
        throw std::runtime_error("Heavy weapon will always miss");
    }
}