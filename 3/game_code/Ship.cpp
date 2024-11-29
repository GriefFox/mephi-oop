#include "game_headers/Ship.hpp"

namespace zasada {

    // structors
    Ship::Ship()
        : name(""), speed(0), health(0), coordinates({0, 0}), 
          finish({0, 0}), price(0) {}

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

    point Ship::getCoordinates() const {
        return coordinates;
    }

    point Ship::getFinish() const {
        return finish;
    }

    size_t Ship::getPrice() const {
        return price;
    }

    // setters
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

    Ship& Ship::setCoordinates(const point& newCoordinates) {
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

    void Ship::move() {
    // Calculate the direction vector from current coordinates to the finish point
    int dx = finish.x - coordinates.x;
    int dy = finish.y - coordinates.y;

    // Calculate the distance to the finish point
    double distance = std::sqrt(dx * dx + dy * dy);

    // Normalize the direction vector
    if (distance > 0) {
        double nx = dx / distance;
        double ny = dy / distance;

        // Move the ship by 'speed' units in the direction of the finish point
        coordinates.x += static_cast<int>(nx * speed);
        coordinates.y += static_cast<int>(ny * speed);

        // Ensure the ship does not overshoot the finish point
        if ((nx > 0 && coordinates.x > finish.x) || (nx < 0 && coordinates.x < finish.x)) {
            coordinates.x = finish.x;
        }
        if ((ny > 0 && coordinates.y > finish.y) || (ny < 0 && coordinates.y < finish.y)) {
            coordinates.y = finish.y;
        }
    }
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

    std::shared_ptr<Weapon> Cruiser::getWeapon(const std::string& name) const {
        auto it = weapons.find(name);
        if (it != weapons.end()) {
            return it->second;
        }
        return nullptr; // Return nullptr if not found
    }

    std::shared_ptr<Ammo> Cruiser::getAmmo(const std::string& name) const {
        auto it = ammo_list.find(name);
        if (it != ammo_list.end()){
            return it->second;
        }
        return nullptr; // if not found
    }

    Cruiser& Cruiser::setWeapon(std::shared_ptr<Weapon> weapon) {
        weapons[weapon->getName()] = weapon;
        return *this;
    }

    Cruiser& Cruiser::setAmmo(std::shared_ptr<Ammo> newAmmo) {
        ammo_list[newAmmo->getName()] = newAmmo;
        return *this;
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

    void Cruiser::attack(std::string& weaponName, std::shared_ptr<Plane> plane) {
        std::shared_ptr<Weapon> weapon = this->getWeapon(weaponName);
        if (!weapon) {
            throw std::runtime_error("Weapon not found");
        }

        weapon->fire(this, plane);
    }

    void Cruiser::attack(std::string& weaponName, std::shared_ptr<Ship> ship){
        std::shared_ptr<Weapon> weapon = this->getWeapon(weaponName);
        if (!weapon) {
            throw std::runtime_error("Weapon not found");
        }

        weapon->fire(this, ship);
    }

    size_t Cruiser::cost() {
        size_t totalCost = Ship::cost();
        for (const auto& [_, weapon] : weapons) {
            totalCost += weapon->cost();
        }
        return totalCost;
    }

    // Реализация Carrier
    std::shared_ptr<Plane> Carrier::getPlane(std::string& name) const {
        auto it = planes.find(name);
        if (it != planes.end()){
            return it->second;
        }
        return nullptr;
    }

    Carrier& Carrier::setPlane(std::shared_ptr<Plane> plane) {
        planes[plane->getName()] = plane;
        return *this;
    }

    void Carrier::flight(std::string& plane_name, std::shared_ptr<Ship> ship) {
        std::shared_ptr<Plane> plane = this->getPlane(plane_name);
        if (!plane) {
            throw std::runtime_error("Plane not found");
        }

        plane->attack(this, ship);
    }

    void Carrier::flight(std::string& plane_name, std::shared_ptr<Plane> target_plane) {
        std::shared_ptr<Plane> plane = this->getPlane(plane_name);
        if (!plane) {
            throw std::runtime_error("Plane not found");
        }

        plane->attack(this, target_plane);
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
        size_t totalCost = Cruiser::cost();

        for (const auto& [_, plane] : planes) {
            totalCost += plane->cost();
        }
        return totalCost;
    }

} // namespace zasada
