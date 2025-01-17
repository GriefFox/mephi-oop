#include "game_headers/Ship.hpp"
#include <iostream>

namespace zasada {

    // structors
    Ship::Ship()
        : name(""), speed(0), health(0), coordinates({0, 0}), 
          finish({0, 0}), price(0) {}

    Ship::Ship(std::string _name, size_t _health)
        : name(_name), speed(0), health(_health),coordinates({0, 0}), 
          finish({0, 0}), price(0) {}
    
    Ship::Ship(std::string _name, size_t _speed, size_t _health, size_t _price): 
        name(_name), speed(_speed), health(_health),coordinates({0, 0}), 
          finish({0, 0}), price(_price) {}

    Ship::~Ship() {}

    // getters
    std::string Ship::getName() const {
        return name;
    }

    capitan_info Ship::getCapitan() const {
        return capitan;
    }

    size_t Ship::getSpeed() const {
        return speed;
    }

    size_t Ship::getHealth() const {
        return health;
    }

    point Ship::getPosition() const {
        return coordinates;
    }

    point Ship::getFinish() const {
        return finish;
    }

    size_t Ship::getPrice() const {
        return price;
    }

    // setters
    Ship& Ship::setName(const std::string& newName){
        name = newName;
        return *this;
    }

    Ship& Ship::setCapitan(const capitan_info& newCapitan) {
        capitan = newCapitan;
        return *this;
    }

    Ship& Ship::setSpeed(size_t newSpeed) {
        speed = newSpeed;
        return *this;
    }

    Ship& Ship::setHealth(size_t newHealth) {
        health = newHealth;
        return *this;
    }

    Ship& Ship::setPosition(const point& newCoordinates) {
        coordinates = newCoordinates;
        return *this;
    }

    Ship& Ship::setFinish(const point& newFinish) {
        finish = newFinish;
        return *this;
    }

    Ship& Ship::setPrice(size_t newPrice) {
        price = newPrice;
        return *this;
    }

    // methods

    size_t Ship::cost(){
        return price;
    }

    void Ship::move(point n_pos){
        double distance = calculate_distace(n_pos, coordinates);
        if (distance == 0)
            return;
        
        double nx = (n_pos.x - coordinates.x) / distance;
        double ny = (n_pos.y - coordinates.y) / distance;

        double moveDistance = std::min(static_cast<double>(speed), distance);
        coordinates.x += nx * moveDistance;
        coordinates.y += ny * moveDistance;
    }

    void Ship::takeDamage(size_t damage) {
        if (health > damage) {
            health -= damage;
        } else {
            health = 0; // Корабль уничтожен
        }
    }

    // Реализация Cruiser
    Cruiser::~Cruiser() {
        // Освобождение ресурсов, если необходимо
        weapons.clear();
    }

    std::shared_ptr<Weapon> AWeaponShip::getWeapon(const std::string& name) const {
        auto it = weapons.find(name);
        if (it != weapons.end()) {
            return it->second;
        }
        return nullptr; // Return nullptr if not found
    }

    std::unordered_map<std::string, std::shared_ptr<Weapon>> AWeaponShip::getWeapons() const
    {
        return weapons;
    }

    std::shared_ptr<Ammo> AWeaponShip::getAmmo(const std::string &name) const
    {
        auto it = ammo_list.find(name);
        if (it != ammo_list.end()){
            return it->second;
        }
        return nullptr; // if not found
    }

    AWeaponShip& AWeaponShip::setWeapon(std::shared_ptr<Weapon> weapon) {
        weapons[weapon->getName()] = weapon;
        return *this;
    }

    AWeaponShip& AWeaponShip::setAmmo(std::shared_ptr<Ammo> newAmmo) {
        ammo_list[newAmmo->getName()] = newAmmo;
        return *this;
    }

    AWeaponShip& AWeaponShip::removeWeapon(const std::string& wpname){
        auto it = weapons.find(wpname);
        // std::cout << it->first << std::endl;
        if (it != weapons.end()){
            weapons.erase(it);
        } else {
            throw std::runtime_error("Such plane doesn't exist");
        }
        return *this;
    }

    void AWeaponShip::performAttack(std::shared_ptr<Weapon> weapon, double distance, std::shared_ptr<Ship> ship) {
        std::lock_guard<std::mutex> lock(attackMutex);  // Ensure only one thread performs attack at a time on shared resources
        weapon->fire(distance, ship);
    }

    void AWeaponShip::performAttack(std::shared_ptr<Weapon> weapon, double distance, std::shared_ptr<Plane> plane) {
        std::lock_guard<std::mutex> lock(attackMutex);  // Ensure thread-safety
        weapon->fire(distance, plane);
    }

    void Carrier::performFlight(std::shared_ptr<Plane> plane, double distance, std::shared_ptr<Plane> target){
        std::lock_guard<std::mutex> lock(flightMutex);
        plane->attack(distance, target);
    }

    void Carrier::performFlight(std::shared_ptr<Plane> plane, double distance, std::shared_ptr<Ship> target){
        std::lock_guard<std::mutex> lock(flightMutex);
        plane->attack(distance, target);
    }

    size_t Cruiser::getSpace() const {
        size_t buffer = storage_space;

        for (const auto& ammoPair : ammo_list) {
            const auto& ammo = ammoPair.second;
            size_t occupiedSpace = ammo->getCurrent() * ammo->getStorageSize();
        
            if (buffer <= occupiedSpace) {
                return 0;
            }
            buffer -= occupiedSpace;
        }

        return buffer;
    }

    void Cruiser::reload(std::string& name) {
        std::shared_ptr<Weapon> weap = this->getWeapon(name);
        weap->reload();
    }

    std::thread Cruiser::attack(std::string& weaponName, std::shared_ptr<Plane> plane) {
        std::shared_ptr<Weapon> weapon = this->getWeapon(weaponName);
        if (!weapon) {
            throw std::runtime_error("Weapon not found");
        }
        double distance = calculate_distace(this->getPosition(), plane->getPosition());
        weapon->fire(distance, plane);
        std::thread attackThread([this, weapon, distance, plane] {
            performAttack(weapon, distance, plane);
        });

        // attackThread.detach(); 
        return attackThread;
    }

    std::thread Cruiser::attack(std::string& weaponName, std::shared_ptr<Ship> ship){
        std::shared_ptr<Weapon> weapon = this->getWeapon(weaponName);
        if (!weapon) {
            throw std::runtime_error("Weapon not found");
        }
        double distance = calculate_distace(this->getPosition(), ship->getPosition());

        std::lock_guard<std::mutex> lock(attackMutex);

        // std::thread attackThread(performAttack, weapon, distance, ship);
        std::thread attackThread([this, weapon, distance, ship] {
            performAttack(weapon, distance, ship);
        });

        // attackThread.detach(); 
        weapon->fire(distance, ship);
        return attackThread;
    }

    size_t Cruiser::cost() {
        size_t totalCost = Ship::cost();
        for (const auto& [_, weapon] : weapons) {
            totalCost += weapon->cost();
        }
        return totalCost;
    }

    // Реализация Carrier
    std::shared_ptr<Plane> Carrier::getPlane(const std::string& name) const {
        auto it = planes.find(name);
        if (it != planes.end()){
            return it->second;
        }
        return nullptr;
    }

    std::unordered_map<std::string, std::shared_ptr<Plane>> Carrier::getPlanes() const {
        return planes;
    }

    Carrier& Carrier::setPlane(std::shared_ptr<Plane> plane) {
        planes[plane->getName()] = plane;
        return *this;
    }

    Carrier& Carrier::erasePlane(const std::string& plname){
        auto it = planes.find(plname);
        // std::cout << it->first << std::endl;
        if (it != planes.end()){
            planes.erase(it);
        } else {
            throw std::runtime_error("Such plane doesn't exist");
        }
        return *this;
    }

    void Carrier::flight(std::string& plane_name, std::shared_ptr<Ship> ship) {
        std::shared_ptr<Plane> plane = this->getPlane(plane_name);
        if (!plane) {
            throw std::runtime_error("Plane not found");
        }
        double distance = calculate_distace(this->getPosition(), ship->getPosition());
        // plane->attack(distance, ship);

        std::thread flightThread([this, plane, distance, ship] {
        // Perform the flight operation (attack) on the target plane
            performFlight(plane, distance, ship);
        });
        flightThread.detach();
    }

    void Carrier::flight(std::string& plane_name, std::shared_ptr<Plane> target_plane) {
        std::shared_ptr<Plane> plane = this->getPlane(plane_name);
        if (!plane) {
            throw std::runtime_error("Plane not found");
        }
        double distance = calculate_distace(this->getPosition(), target_plane->getPosition());
        // plane->attack(distance, target_plane);
        std::thread flightThread([this, plane, distance, target_plane] {
            // Perform the flight operation (attack) on the target plane
            performFlight(plane, distance, target_plane);
        });
        flightThread.detach();
    }

    size_t Carrier::cost(){
        size_t totalCost = Ship::cost();

        for (const auto& [_, plane] : planes) {
            totalCost += plane->cost();
        }
        return totalCost;
    }
    // Реализация AttackCarrier
    AttackCarrier& AttackCarrier::setWeapon(std::shared_ptr<Weapon> weapon) {
        if (weapon->getType() == weapon_t::heavy){
            throw std::runtime_error("AttackCarrier can't have heavy weapon");
        }
        weapons[weapon->getName()] = weapon;
        return *this;
    }

    size_t AttackCarrier::cost(){
        size_t totalCost = Carrier::cost();

        for (const auto& [_, weapon] : weapons) {
            totalCost += weapon->cost();
        }
        
        return totalCost;
    }

    std::thread AttackCarrier::attack(std::string& weaponName, std::shared_ptr<Plane> plane) {
        std::shared_ptr<Weapon> weapon = this->getWeapon(weaponName);
        if (!weapon) {
            throw std::runtime_error("Weapon not found");
        }
        double distance = calculate_distace(this->getPosition(), plane->getPosition());
        weapon->fire(distance, plane);
    }

    std::thread AttackCarrier::attack(std::string& weaponName, std::shared_ptr<Ship> ship){
        std::shared_ptr<Weapon> weapon = this->getWeapon(weaponName);
        if (!weapon) {
            throw std::runtime_error("Weapon not found");
        }
        double distance = calculate_distace(this->getPosition(), ship->getPosition());
        weapon->fire(distance, ship);
    }

} // namespace zasada
