#ifndef SHIP_H
#define SHIP_H
#include "generic.hpp"
#include "Plane.hpp"
#include "Weapon.hpp"
#include "Ammo.hpp"

#include <complex>
#include <stdexcept>
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>
#include <thread>
#include <mutex>

namespace zasada {

    /**
     * @class Plane
     * Forward declaration of Plane class.
     */
    class Plane;

    /**
     * @class Weapon
     * Forward declaration of Weapon class.
     */
    class Weapon;

    /**
     * @class Ship
     * @brief Represents a generic ship class with basic attributes and behaviors.
     * 
     * This class provides the basic attributes and functionality for ships including 
     * their name, captain, speed, health, position, and price. It includes methods for 
     * modifying and retrieving these attributes and basic ship behaviors like moving 
     * and taking damage.
     */
    class Ship {
        protected:
            std::string name;           ///< Name of the ship.
            capitan_info capitan;       ///< Captain information.
            size_t speed;              ///< Speed of the ship.
            size_t health;             ///< Health points of the ship.
            point coordinates;         ///< Current position of the ship.
            point finish;              ///< Destination of the ship.
            size_t price;              ///< Price of the ship.
        public:
            /**
             * @brief Default constructor for Ship.
             */
            Ship();

            /**
             * @brief Constructor for Ship with name and speed.
             * @param _name Name of the ship.
             * @param _speed Speed of the ship.
             */
            Ship(std::string _name, size_t _speed);  

            /**
             * @brief Constructor for Ship with name, speed, health, and price.
             * @param _name Name of the ship.
             * @param _speed Speed of the ship.
             * @param _health Health of the ship.
             * @param _price Price of the ship.
             */
            Ship(std::string _name, size_t _speed, size_t _health, size_t _price);

            /**
             * @brief Destructor for Ship.
             */
            virtual ~Ship();
            
            // Getters

            /**
             * @brief Gets the name of the ship.
             * @return The name of the ship.
             */
            std::string getName() const;

            /**
             * @brief Gets the captain's information of the ship.
             * @return Captain information of the ship.
             */
            capitan_info getCapitan() const;

            /**
             * @brief Gets the speed of the ship.
             * @return The speed of the ship.
             */
            size_t getSpeed() const;

            /**
             * @brief Gets the health of the ship.
             * @return The health of the ship.
             */
            size_t getHealth() const;

            /**
             * @brief Gets the current position of the ship.
             * @return The coordinates of the ship.
             */
            point getPosition() const;

            /**
             * @brief Gets the finish point of the ship.
             * @return The finish point of the ship.
             */
            point getFinish() const;

            /**
             * @brief Gets the price of the ship.
             * @return The price of the ship.
             */
            size_t getPrice() const;
            
            // Setters

            /**
             * @brief Sets the name of the ship.
             * @param _name The new name of the ship.
             * @return A reference to the ship object.
             */
            Ship& setName(const std::string& _name);

            /**
             * @brief Sets the captain information of the ship.
             * @param newCapitan The new captain information.
             * @return A reference to the ship object.
             */
            Ship& setCapitan(const capitan_info& newCapitan);

            /**
             * @brief Sets the speed of the ship.
             * @param newSpeed The new speed of the ship.
             * @return A reference to the ship object.
             */
            Ship& setSpeed(size_t newSpeed);

            /**
             * @brief Sets the health of the ship.
             * @param newHealth The new health of the ship.
             * @return A reference to the ship object.
             */
            Ship& setHealth(size_t newHealth);

            /**
             * @brief Sets the position of the ship.
             * @param newCoordinates The new coordinates of the ship.
             * @return A reference to the ship object.
             */
            Ship& setPosition(const point& newCoordinates);

            /**
             * @brief Sets the finish point of the ship.
             * @param newFinish The new finish point of the ship.
             * @return A reference to the ship object.
             */
            Ship& setFinish(const point& newFinish);

            /**
             * @brief Sets the price of the ship.
             * @param newPrice The new price of the ship.
             * @return A reference to the ship object.
             */
            Ship& setPrice(size_t newPrice);

            /**
             * @brief Calculates the cost of the ship.
             * @return The cost of the ship.
             */
            virtual size_t cost();

            /**
             * @brief Moves the ship towards its finish point.
             */
            virtual void move(point);

            /**
             * @brief Applies damage to the ship.
             * @param damage The amount of damage to apply.
             */
            virtual void takeDamage(size_t damage);
    };

    /**
     * @class AWeaponShip
     * @brief Represents a ship with weapons and ammo capabilities.
     * 
     * This class provides the ability for ships to have weapons, ammo, and the ability 
     * to attack other ships or planes.
     */
    class AWeaponShip {
        protected:
            size_t max_weapon;                             ///< Maximum weapons the ship can carry.
            std::unordered_map<std::string, std::shared_ptr<Ammo>> ammo_list;  ///< List of ammo types for the ship.
            std::unordered_map<std::string, std::shared_ptr<Weapon>> weapons;  ///< List of weapons on the ship.
            std::mutex attackMutex;

        public:
            /**
             * @brief Gets the weapon by its name.
             * @param weaponName Name of the weapon.
             * @return Shared pointer to the weapon.
             */
            virtual std::shared_ptr<Weapon> getWeapon(const std::string& weaponName) const;
            virtual std::unordered_map<std::string, std::shared_ptr<Weapon>> getWeapons() const;
            /**
             * @brief Sets a weapon on the ship.
             * @param weapon Shared pointer to the weapon.
             * @return A reference to the weapon ship.
             */
            virtual AWeaponShip& setWeapon(std::shared_ptr<Weapon> weapon);

            /**
             * @brief Removes a weapon from the ship.
             * @param weaponName Name of the weapon to remove.
             * @return A reference to the weapon ship.
             */
            virtual AWeaponShip& removeWeapon(const std::string& weaponName);

            /**
             * @brief Attacks a plane with the specified weapon.
             * @param weaponName Name of the weapon to use.
             * @param target The target plane to attack.
             */
            virtual std::thread attack(std::string& weaponName, std::shared_ptr<Plane> target) = 0;

            /**
             * @brief Attacks another ship with the specified weapon.
             * @param weaponName Name of the weapon to use.
             * @param target The target ship to attack.
             */
            virtual std::thread attack(std::string& weaponName, std::shared_ptr<Ship> target) = 0;


            void performAttack(std::shared_ptr<Weapon> weapon, double distance, std::shared_ptr<Ship> ship);
            void performAttack(std::shared_ptr<Weapon> weapon, double distance, std::shared_ptr<Plane> plane);
            /**
             * @brief Sets ammo for the ship.
             * @param ammo Shared pointer to ammo.
             * @return A reference to the weapon ship.
             */
            virtual AWeaponShip& setAmmo(std::shared_ptr<Ammo> ammo);

            /**
             * @brief Gets ammo by its name.
             * @param ammoName Name of the ammo type.
             * @return Shared pointer to the ammo.
             */
            virtual std::shared_ptr<Ammo> getAmmo(const std::string& ammoName) const;
    };

    /**
     * @class Cruiser
     * @brief Represents a cruiser ship with weapon capabilities.
     * 
     * This class is a derived class from Ship and AWeaponShip, providing additional 
     * storage for weapons and the ability to attack.
     */
    class Cruiser : public Ship, public AWeaponShip {
        protected:
            size_t storage_space;  ///< Storage space for weapons and ammo.
        public:
            /**
             * @brief Destructor for Cruiser.
             */
            ~Cruiser();

            /**
             * @brief Default constructor for Cruiser.
             */
            Cruiser() : Ship() {}

            /**
             * @brief Constructor for Cruiser with name and health.
             * @param _name Name of the cruiser.
             * @param _health Health of the cruiser.
             */
            Cruiser(std::string _name, size_t _health) : Ship(_name, _health) {}

            /**
             * @brief Constructor for Cruiser with name, speed, health, and price.
             * @param _name Name of the cruiser.
             * @param _speed Speed of the cruiser.
             * @param _health Health of the cruiser.
             * @param _price Price of the cruiser.
             */
            Cruiser(std::string _name, size_t _speed, size_t _health, size_t _price) : Ship(_name, _speed, _health, _price) {}

            /**
             * @brief Gets the storage space of the cruiser.
             * @return Storage space.
             */
            virtual size_t getSpace() const;

            /**
             * @brief Reloads the cruiser with the specified weapon.
             * @param weaponName Name of the weapon to reload.
             */
            void reload(std::string& weaponName);

            /**
             * @brief Attacks a plane with the cruiser.
             * @param weaponName Name of the weapon to use.
             * @param target Plane to attack.
             */
            std::thread attack(std::string& weaponName, std::shared_ptr<Plane> target) override;

            /**
             * @brief Attacks another ship with the cruiser.
             * @param weaponName Name of the weapon to use.
             * @param target Ship to attack.
             */
            std::thread attack(std::string& weaponName, std::shared_ptr<Ship> target) override;

            /**
             * @brief Calculates the cost of the cruiser.
             * @return Cost of the cruiser.
             */
            virtual size_t cost() override;
    };

    /**
     * @class Carrier
     * @brief Represents a carrier ship capable of carrying planes.
     * 
     * This class represents a carrier ship that can carry multiple planes and 
     * allows for launching planes into combat.
     */
    class Carrier : public Ship {
        protected:
            size_t maxPlanes;  ///< Maximum number of planes the carrier can carry.
            std::unordered_map<std::string, std::shared_ptr<Plane>> planes;  ///< List of planes on the carrier.
            std::mutex flightMutex;
        public:  
            /**
             * @brief Default constructor for Carrier.
             */
            Carrier() : Ship() {}      

            /**
             * @brief Constructor for Carrier with name and health.
             * @param _name Name of the carrier.
             * @param _health Health of the carrier.
             */
            Carrier(std::string _name, size_t _health) : Ship(_name, _health) {}

            /**
             * @brief Constructor for Carrier with name, speed, health, and price.
             * @param _name Name of the carrier.
             * @param _speed Speed of the carrier.
             * @param _health Health of the carrier.
             * @param _price Price of the carrier.
             */
            Carrier(std::string _name, size_t _speed, size_t _health, size_t _price) : Ship(_name, _speed, _health, _price) {}

            /**
             * @brief Gets a plane from the carrier by its name.
             * @param planeName Name of the plane.
             * @return Shared pointer to the plane.
             */
            std::shared_ptr<Plane> getPlane(const std::string& planeName) const;
            std::unordered_map<std::string, std::shared_ptr<Plane>> getPlanes() const;
            /**
             * @brief Adds a plane to the carrier.
             * @param plane Shared pointer to the plane.
             * @return A reference to the carrier.
             */
            Carrier& setPlane(std::shared_ptr<Plane> plane);

            /**
             * @brief Removes a plane from the carrier by its name.
             * @param planeName Name of the plane to remove.
             * @return A reference to the carrier.
             */
            Carrier& erasePlane(const std::string& planeName);
            
            /**
             * @brief Launches a flight mission for a plane to attack a ship.
             * @param planeName Name of the plane.
             * @param target Ship to attack.
             */
            virtual void flight(std::string& planeName, std::shared_ptr<Ship> target);

            /**
             * @brief Launches a flight mission for a plane to attack another plane.
             * @param planeName Name of the plane.
             * @param target Plane to attack.
             */
            virtual void flight(std::string& planeName, std::shared_ptr<Plane> target);
            void performFlight(std::shared_ptr<Plane> plane, double distance, std::shared_ptr<Plane>);
            void performFlight(std::shared_ptr<Plane> plane, double distance, std::shared_ptr<Ship>);

            /**
             * @brief Calculates the cost of the carrier.
             * @return Cost of the carrier.
             */
            virtual size_t cost() override;
    };

    /**
     * @class AttackCarrier
     * @brief Represents an attack carrier capable of carrying planes and using weapons.
     * 
     * This class represents a more specialized type of carrier ship, allowing 
     * for both aircraft launching and weapon attacks on ships and planes.
     */
    class AttackCarrier : public Carrier, public AWeaponShip {
    public:
        /**
         * @brief Default constructor for AttackCarrier.
         */
        AttackCarrier() : Carrier() {}

        /**
         * @brief Constructor for AttackCarrier with name and health.
         * @param _name Name of the attack carrier.
         * @param _health Health of the attack carrier.
         */
        AttackCarrier(std::string _name, size_t _health) : Carrier(_name, _health) {}

        /**
         * @brief Constructor for AttackCarrier with name, speed, health, and price.
         * @param _name Name of the attack carrier.
         * @param _speed Speed of the attack carrier.
         * @param _health Health of the attack carrier.
         * @param _price Price of the attack carrier.
         */
        AttackCarrier(std::string _name, size_t _speed, size_t _health, size_t _price) : Carrier(_name, _speed, _health, _price) {}

        /**
         * @brief Sets a weapon on the attack carrier.
         * @param weapon Shared pointer to the weapon.
         * @return A reference to the attack carrier.
         */
        AttackCarrier& setWeapon(std::shared_ptr<Weapon> weapon) override;

        /**
         * @brief Attacks a plane with the attack carrier.
         * @param weaponName Name of the weapon to use.
         * @param target Plane to attack.
         */
        std::thread attack(std::string& weaponName, std::shared_ptr<Plane> target) override;

        /**
         * @brief Attacks another ship with the attack carrier.
         * @param weaponName Name of the weapon to use.
         * @param target Ship to attack.
         */
        std::thread attack(std::string& weaponName, std::shared_ptr<Ship> target) override;

        /**
         * @brief Calculates the cost of the attack carrier.
         * @return Cost of the attack carrier.
         */
        virtual size_t cost() override;
    };

} // namespace zasada

#endif
