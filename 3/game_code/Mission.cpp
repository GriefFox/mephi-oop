#include "game_headers/Mission.hpp"

namespace zasada{
    Mission::Mission()
        : max_ships(0), spend(0), max_spend(0), damage_attacker(0), damage_defender(0),
          win_price(0), enemy_price(0), saved_money(0), pointA({0,0}), pointB({0,0}) {
        commander.name = "Null";
        commander.rank = "Null";
    }

    Mission::~Mission() {
        // Clean up resources if necessary
        // Since we're using smart pointers, explicit cleanup might not be needed
    }    

    // Getters
    Table<std::string, std::shared_ptr<Ship>>& Mission::getTableAttacker() {
        return table_attacker;
    }

    Table<std::string, std::shared_ptr<Ship>>& Mission::getTableDefender() {
        return table_defender;
    }

    capitan_info Mission::getCommander() const {
        return commander;
    }

    size_t Mission::getMaxShips() const {
        return max_ships;
    }

    size_t Mission::getSpend() const {
        return spend;
    }

    size_t Mission::getMaxSpend() const {
        return max_spend;
    }

    size_t Mission::getDamageAttacker() const {
        return damage_attacker;
    }

    size_t Mission::getDamageDefender() const {
        return damage_defender;
    }

    size_t Mission::getWinPrice() const {
        return win_price;
    }

    size_t Mission::getEnemyPrice() const {
        return enemy_price;
    }

    size_t Mission::getSavedMoney() const {
        return saved_money;
    }

    // size_t Mission::getSize() const {
    //     return size;
    // }

    point Mission::getPointA() const {
        return pointA;
    }

    point Mission::getPointB() const {
        return pointB;
    }

    // Setters
    void Mission::setCommander(const capitan_info& commander) {
        this->commander = commander;
    }

    void Mission::setMaxShips(size_t maxShips) {
        max_ships = maxShips;
    }

    void Mission::setSpend(size_t spend) {
        this->spend = spend;
    }

    void Mission::setMaxSpend(size_t maxSpend) {
        max_spend = maxSpend;
    }

    void Mission::setDamageAttacker(size_t damage) {
        damage_attacker = damage;
    }

    void Mission::setDamageDefender(size_t damage) {
        damage_defender = damage;
    }

    void Mission::setWinPrice(size_t price) {
        win_price = price;
    }

    void Mission::setEnemyPrice(size_t price) {
        enemy_price = price;
    }

    void Mission::setSavedMoney(size_t money) {
        saved_money = money;
    }

    // void Mission::setSize(size_t size) {
    //     this->size = size;
    // }

    void Mission::setPointA(const point& pointA) {
        this->pointA = pointA;
    }

    void Mission::setPointB(const point& pointB) {
        this->pointB = pointB;
    }

    Mission& Mission::buyShip(std::shared_ptr<Ship> ship) {
        if (!ship) {
            throw std::invalid_argument("Cannot buy a null ship.");
        }

        size_t shipPrice = ship->getPrice();

        if (spend + shipPrice > max_spend || table_defender.size() >= max_ships){
            throw std::runtime_error("Insufficient funds or maximum ships reached.");
        }

        try {
            table_defender.insert(ship->getName(), ship);
        } catch(std::runtime_error e) {
            throw e;
        }
        spend += shipPrice;
        
        saved_money = spend;
        win_price = 80 * spend / 100;
        return *this;
    }

    Mission& Mission::sellShip(const std::string& ship_name) {
        auto ship = table_defender.find(ship_name);
        if (!ship) {
            throw std::runtime_error("Ship not found");
        }
        bool deleted = table_defender.erase(ship_name);
        if (!deleted) {
            throw std::runtime_error("Failed to delete the ship");
        }
        size_t cost = (*ship)->cost();

        spend -= cost;
        saved_money = spend;
        win_price = 80 * spend / 100;
        return *this;
    }

    Mission& Mission::buyPlane(std::shared_ptr<Plane> plane, std::string& ship_name) {
        if (!plane) {
            throw std::invalid_argument("Cannot buy a null plane.");
        }

        auto ship = table_defender.find(ship_name);
        if (!ship) {
            throw std::runtime_error("Ship not found in table_defender.");
        }

        auto carrier = std::dynamic_pointer_cast<Carrier>(*ship);
        if (!carrier) {
            throw std::runtime_error("The specified ship is not a Carrier.");
        }

        size_t planePrice = plane->getPrice();
        if (spend + planePrice > max_spend) {
            throw std::runtime_error("Insufficient funds to buy the plane.");
        }

        carrier->setPlane(plane);
        spend += planePrice;
        saved_money = spend;
        win_price = 80 * spend / 100;
        return *this;
    }

    Mission& Mission::sellPlane(const std::string& plane_name, const std::string& ship_name) {
    auto ship = table_defender.find(ship_name);
    if (!ship) {
        throw std::runtime_error("Ship not found in table_defender.");
    }

    auto carrier = std::dynamic_pointer_cast<Carrier>(*ship);
    if (!carrier) {
        throw std::runtime_error("The specified ship is not a Carrier.");
    }

    auto existingPlane = carrier->getPlane(plane_name);
    if (!existingPlane) {
        throw std::runtime_error("Plane not found on the specified Carrier.");
    }

    size_t planePrice = existingPlane->getPrice();
    carrier->erasePlane(plane_name);
    spend -= planePrice;
    saved_money = spend;
    win_price = 80 * spend / 100;
    return *this;
}

     Mission& Mission::buyWeapon(std::shared_ptr<Weapon> weapon, std::string& ship_name) {
        if (!weapon) {
            throw std::invalid_argument("Cannot buy a null weapon.");
        }

        auto ship = table_defender.find(ship_name);
        if (!ship) {
            throw std::runtime_error("Ship not found in table_defender.");
        }

        auto weaponShip = std::dynamic_pointer_cast<AWeaponShip>(*ship);
        if (!weaponShip) {
            throw std::runtime_error("The specified ship is not a WeaponShip.");
        }

        size_t weaponPrice = weapon->getPrice();
        if (spend + weaponPrice > max_spend) {
            throw std::runtime_error("Insufficient funds to buy the weapon.");
        }
        
        try {
            weaponShip->setWeapon(weapon);
        } catch (std::runtime_error e){
            throw e;
        }
        spend += weaponPrice;
        saved_money = spend;
        win_price = 80 * spend / 100;
        return *this;
    }

    Mission& Mission::sellWeapon(const std::string& ship_name, const std::string& weapon_name) {
        auto ship = table_defender.find(ship_name);
        if (!ship) {
            throw std::runtime_error("Ship not found in table_defender.");
        }

        auto weaponShip = std::dynamic_pointer_cast<AWeaponShip>(*ship);
        if (!weaponShip) {
            throw std::runtime_error("The specified ship is not a WeaponShip.");
        }

        auto existingWeapon = weaponShip->getWeapon(weapon_name);
        if (!existingWeapon) {
            throw std::runtime_error("Weapon not found on the specified WeaponShip.");
        }

        size_t weaponPrice = existingWeapon->getPrice();
        weaponShip->removeWeapon(weapon_name); // Assuming this removes the weapon
        spend -= weaponPrice;
        saved_money = spend;
        win_price = 80 * spend / 100;
        return *this;
    }

    Mission& Mission::movePlane(const std::string& sourceShipName, const std::string& planeName, const std::string& destinationShipName) {
        // Find the source ship
        auto sourceShip = table_defender.find(sourceShipName);
        if (!sourceShip) {
            throw std::runtime_error("Source ship not found in table_defender.");
        }

        // Check if the source ship is a Carrier
        auto sourceCarrier = std::dynamic_pointer_cast<Carrier>(*sourceShip);
        if (!sourceCarrier) {
            throw std::runtime_error("The source ship is not a Carrier.");
        }

        // Find the plane on the source ship
        auto plane = sourceCarrier->getPlane(planeName);
        if (!plane) {
            throw std::runtime_error("Plane not found on the source Carrier.");
        }

        // Find the destination ship
        auto destinationShip = table_defender.find(destinationShipName);
        if (!destinationShip) {
            throw std::runtime_error("Destination ship not found in table_defender.");
        }

        // Check if the destination ship is a Carrier
        auto destinationCarrier = std::dynamic_pointer_cast<Carrier>(*destinationShip);
        if (!destinationCarrier) {
            throw std::runtime_error("The destination ship is not a Carrier.");
        }

        // Remove the plane from the source ship
        sourceCarrier->erasePlane(planeName);

        // Add the plane to the destination ship
        destinationCarrier->setPlane(plane);

        return *this;
    }

}