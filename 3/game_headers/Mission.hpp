#ifndef MISSION_H
#define MISSION_H

#include "generic.hpp"
#include "Table.hpp"
#include "Ship.hpp"
#include "Plane.hpp"
#include "Weapon.hpp"

namespace zasada{

    /**
     * @class Mission
     * @brief Represents a mission with attackers, defenders, and various mission-related parameters.
     */
    class Mission{
        private:
            Table<std::string, std::shared_ptr<Ship>> table_attacker; ///< Table of attacker ships.
            Table<std::string, std::shared_ptr<Ship>> table_defender; ///< Table of defender ships.
            capitan_info commander; ///< Information about the mission commander.
            size_t max_ships; ///< Maximum number of ships allowed in the mission.
            size_t spend; ///< Amount of money spent.
            size_t max_spend; ///< Maximum amount of money allowed to spend.
            size_t damage_attacker; ///< Total damage dealt by attackers.
            size_t damage_defender; ///< Total damage dealt by defenders.
            size_t win_price; ///< Damage required for victory.
            size_t enemy_price; ///< Cost of the enemy fleet.
            size_t saved_money; ///< Value of units saved during the mission.
            point pointA; ///< Starting point of the mission.
            point pointB; ///< Ending point of the mission.

        public:
            /**
             * @brief Default constructor for Mission.
             */
            Mission();

            /**
             * @brief Destructor for Mission.
             */
            ~Mission();

            // Getters

            /**
             * @brief Retrieves the table of attacker ships.
             * @return Reference to the table of attacker ships.
             */
            Table<std::string, std::shared_ptr<Ship>>& getTableAttacker();

            /**
             * @brief Retrieves the table of defender ships.
             * @return Reference to the table of defender ships.
             */
            Table<std::string, std::shared_ptr<Ship>>& getTableDefender();

            /**
             * @brief Retrieves the mission commander's information.
             * @return The mission commander information.
             */
            capitan_info getCommander() const;

            /**
             * @brief Retrieves the maximum number of ships allowed.
             * @return Maximum number of ships.
             */
            size_t getMaxShips() const;

            /**
             * @brief Retrieves the amount of money spent.
             * @return Amount of money spent.
             */
            size_t getSpend() const;

            /**
             * @brief Retrieves the maximum amount of money allowed to spend.
             * @return Maximum allowed spending.
             */
            size_t getMaxSpend() const;

            /**
             * @brief Retrieves the total damage dealt by attackers.
             * @return Total attacker damage.
             */
            size_t getDamageAttacker() const;

            /**
             * @brief Retrieves the total damage dealt by defenders.
             * @return Total defender damage.
             */
            size_t getDamageDefender() const;

            /**
             * @brief Retrieves the required damage for victory.
             * @return Damage required for victory.
             */
            size_t getWinPrice() const;

            /**
             * @brief Retrieves the cost of the enemy fleet.
             * @return Enemy fleet cost.
             */
            size_t getEnemyPrice() const;

            /**
             * @brief Retrieves the value of saved units.
             * @return Saved units' value.
             */
            size_t getSavedMoney() const;

            /**
             * @brief Retrieves the starting point of the mission.
             * @return Starting point.
             */
            point getPointA() const;

            /**
             * @brief Retrieves the ending point of the mission.
             * @return Ending point.
             */
            point getPointB() const;

            // Setters

            /**
             * @brief Sets the mission commander.
             * @param commander Information about the new commander.
             */
            void setCommander(const capitan_info& commander);

            /**
             * @brief Sets the maximum number of ships.
             * @param maxShips The new maximum number of ships.
             */
            void setMaxShips(size_t maxShips);

            /**
             * @brief Sets the amount of money spent.
             * @param spend The new amount of money spent.
             */
            void setSpend(size_t spend);

            /**
             * @brief Sets the maximum allowed spending.
             * @param maxSpend The new maximum spending amount.
             */
            void setMaxSpend(size_t maxSpend);

            /**
             * @brief Sets the damage dealt by attackers.
             * @param damage The new total attacker damage.
             */
            void setDamageAttacker(size_t damage);

            /**
             * @brief Sets the damage dealt by defenders.
             * @param damage The new total defender damage.
             */
            void setDamageDefender(size_t damage);

            /**
             * @brief Sets the required damage for victory.
             * @param price The new victory damage requirement.
             */
            void setWinPrice(size_t price);

            /**
             * @brief Sets the cost of the enemy fleet.
             * @param price The new enemy fleet cost.
             */
            void setEnemyPrice(size_t price);

            /**
             * @brief Sets the value of saved units.
             * @param money The new saved money value.
             */
            void setSavedMoney(size_t money);

            /**
             * @brief Sets the starting point of the mission.
             * @param pointA The new starting point.
             */
            void setPointA(const point& pointA);

            /**
             * @brief Sets the ending point of the mission.
             * @param pointB The new ending point.
             */
            void setPointB(const point& pointB);

            // Mission-related actions

            /**
             * @brief Buys a ship for the mission.
             * @param ship The ship to add to the mission.
             * @return Reference to the current Mission object.
             */
            Mission& buyShip(std::shared_ptr<Ship> ship);

            /**
             * @brief Sells a ship from the mission.
             * @param name The name of the ship to sell.
             * @return Reference to the current Mission object.
             */
            Mission& sellShip(const std::string& name);

            /**
             * @brief Buys a plane and assigns it to a ship.
             * @param plane The plane to add.
             * @param shipName The name of the ship to assign the plane to.
             * @return Reference to the current Mission object.
             */
            Mission& buyPlane(std::shared_ptr<Plane> plane, std::string& shipName);

            /**
             * @brief Sells a plane from a ship.
             * @param plane_name The name of the plane to sell.
             * @param ship_name The name of the ship the plane is assigned to.
             * @return Reference to the current Mission object.
             */
            Mission& sellPlane(const std::string& plane_name, const std::string& ship_name);

            /**
             * @brief Moves a plane from one ship to another.
             * @param sourceShipName The source ship's name.
             * @param planeName The name of the plane to move.
             * @param destinationShipName The destination ship's name.
             * @return Reference to the current Mission object.
             */
            Mission& movePlane(const std::string& sourceShipName, const std::string& planeName, const std::string& destinationShipName);

            /**
             * @brief Buys a weapon and assigns it to a ship.
             * @param weapon The weapon to buy.
             * @param shipName The name of the ship to assign the weapon to.
             * @return Reference to the current Mission object.
             */
            Mission& buyWeapon(std::shared_ptr<Weapon> weapon, std::string& shipName);

            /**
             * @brief Sells a weapon from a ship.
             * @param weapon_name The name of the weapon to sell.
             * @param ship_name The name of the ship the weapon is assigned to.
             * @return Reference to the current Mission object.
             */
            Mission& sellWeapon(const std::string& weapon_name, const std::string& ship_name);

            // Future functions:
            // Mission& destroyShip(std::shared_ptr<Ship>);
            // Mission& win();
    };

} // namespace zasada

#endif