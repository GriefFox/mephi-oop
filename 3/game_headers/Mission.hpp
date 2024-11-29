#ifndef MISSION_H
#define MISSION_H
#include "generic.hpp"
#include "Table.hpp"
#include "Ship.hpp"
#include "Plane.hpp"
#include "Weapon.hpp"
namespace zasada{
    class Mission{
        private:
            std::shared_ptr<Table<Ship>> table_attacker;
            std::shared_ptr<Table<Ship>> table_defender; 
            capitan_info commander;
            size_t max_ships;
            size_t spend; // потраченная сумма денег
            size_t max_spend;
            size_t damage_attacker;
            size_t damage_defender;
            size_t win_price; // необходимый ущерб для победы
            size_t enemy_price; // стоимость противника
            size_t saved_money; // стоимость спасшихся едениц
            size_t size; // какой-то размер
            point pointA;
            point pointB;
        public:
            Mission& buyShip(std::shared_ptr<Ship>);
            Mission& sellShip(std::string&);
            Mission& buyPlane(std::shared_ptr<Plane>);
            Mission& sellPlane(std::shared_ptr<Plane>);  
            // Mission& movePlane(std::shared_ptr<Plane>);
            // Mission& buyWeapon(std::shared_ptr<Weapon>);
            // Mission& sellWeapon(std::shared_ptr<Weapon>);
            // Mission& destroyShip(std::shared_ptr<Ship>);
            // Mission& win();

    };
}

#endif