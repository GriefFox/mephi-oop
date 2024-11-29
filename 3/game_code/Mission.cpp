#include "game_headers/Mission.hpp"

namespace zasada{
    Mission& Mission::buyShip(std::shared_ptr<Ship> ship) {
        if (!ship) {
            throw std::invalid_argument("Cannot buy a null ship.");
        }

        size_t shipPrice = ship->getPrice();

        if (spend + shipPrice > max_spend || table_defender->getSize() > max_ships){
            throw std::runtime_error("Insufficient funds or maximum ships reached.");
        }

        table_defender->append(ship);
        spend += shipPrice;
        
        saved_money = spend;
        win_price = 80 * spend / 100;
        return *this;
    }

    Mission& Mission::sellShip(std::string& ship_name){
        auto ship = table_defender->pop(ship_name);

        size_t cost = ship->cost();

        spend -= cost;
        saved_money = spend;
        win_price = 80 * spend / 100;
        return *this;
    }
}