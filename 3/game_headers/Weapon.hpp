#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <memory>
#include <stdexcept>
#include <thread>
#include <mutex>

#include "Ship.hpp"
#include "Plane.hpp"
#include "Ammo.hpp"

namespace zasada {
    class Ship;
    class Plane;
    
    /**
     * @class Weapon
     * @brief A base class for all weapon types, encapsulating common functionality.
     * 
     * This class defines the common properties and methods for different types of weapons, including 
     * their damage, ammo, range, fire rate, reload time, and price.
     */
    class Weapon {
    protected:
        weapon_t type = weapon_t::def_weap; ///< Type of the weapon (e.g., default weapon type).
        size_t damage; ///< The damage dealt by the weapon.
        std::shared_ptr<Ammo> ammo; ///< The ammo used by the weapon.
        std::string name; ///< A unique identifier for the weapon.
        bool activity; ///< Whether the weapon is active or not.
        const size_t max_ammo = 0; ///< The maximum amount of ammo the weapon can hold.
        size_t range; ///< The range of the weapon.
        size_t fire_rate; ///< The rate at which the weapon fires.
        const size_t reload_time; ///< How many ticks it takes to reload the weapon.
        size_t reload_left; ///< How many ticks are left until the weapon is fully reloaded.
        size_t price; ///< The price of the weapon.
        std::mutex mtx;

    public:
        /**
         * @brief Default constructor for Weapon.
         */
        Weapon();

        /**
         * @brief Destructor for Weapon.
         */
        virtual ~Weapon();

        /**
         * @brief Constructs a Weapon with the specified parameters.
         * 
         * @param damage The damage dealt by the weapon.
         * @param ammo The ammo used by the weapon.
         * @param name The unique name of the weapon.
         * @param activity The activity status of the weapon.
         * @param max_ammo The maximum ammo capacity of the weapon.
         * @param range The range of the weapon.
         * @param fire_rate The fire rate of the weapon.
         * @param reload_time The reload time in ticks.
         * @param reload_left The number of ticks left for reload.
         * @param price The price of the weapon.
         */
        Weapon(size_t damage, std::shared_ptr<Ammo> ammo, std::string name, bool activity, const size_t max_ammo,
               size_t range, size_t fire_rate, const size_t reload_time, size_t reload_left, size_t price);
        
        // Getter methods

        /**
         * @brief Gets the type of the weapon.
         * @return The weapon's type.
         */
        weapon_t getType() const;

        /**
         * @brief Gets the damage dealt by the weapon.
         * @return The damage value.
         */
        virtual size_t getDamage() const;

        /**
         * @brief Gets the ammo used by the weapon.
         * @return A shared pointer to the ammo object.
         */
        std::shared_ptr<Ammo> getAmmo() const;

        /**
         * @brief Gets the name of the weapon.
         * @return The name of the weapon.
         */
        std::string getName() const;

        /**
         * @brief Gets the activity status of the weapon.
         * @return True if the weapon is active, false otherwise.
         */
        bool getActivity() const;

        /**
         * @brief Gets the range of the weapon.
         * @return The range of the weapon.
         */
        size_t getRange() const;

        /**
         * @brief Gets the maximum ammo capacity of the weapon.
         * @return The maximum ammo capacity.
         */
        size_t getMaxAmmo() const;

        /**
         * @brief Gets the fire rate of the weapon.
         * @return The fire rate in ticks.
         */
        size_t getFireRate() const;

        /**
         * @brief Gets the reload time of the weapon.
         * @return The reload time in ticks.
         */
        size_t getReloadTime() const;

        /**
         * @brief Gets the number of ticks left to reload the weapon.
         * @return The number of ticks left to reload.
         */
        size_t getReloadLeft() const;

        /**
         * @brief Gets the price of the weapon.
         * @return The price of the weapon.
         */
        size_t getPrice() const;

        // Setter methods

        /**
         * @brief Sets the damage of the weapon.
         * @param damage The new damage value.
         * @return The current weapon object.
         */
        Weapon& setDamage(size_t damage);

        /**
         * @brief Sets the ammo for the weapon.
         * @param ammo A shared pointer to the new ammo.
         * @return The current weapon object.
         */
        Weapon& setAmmo(std::shared_ptr<Ammo> ammo);

        /**
         * @brief Sets the name of the weapon.
         * @param name The new name of the weapon.
         * @return The current weapon object.
         */
        Weapon& setName(const std::string& name);

        /**
         * @brief Sets the activity status of the weapon.
         * @param activity True to activate the weapon, false to deactivate.
         * @return The current weapon object.
         */
        Weapon& setActivity(bool activity);

        /**
         * @brief Sets the range of the weapon.
         * @param range The new range value.
         * @return The current weapon object.
         */
        Weapon& setRange(size_t range);

        /**
         * @brief Sets the fire rate of the weapon.
         * @param fire_rate The new fire rate.
         * @return The current weapon object.
         */
        Weapon& setFireRate(size_t fire_rate);

        /**
         * @brief Sets the number of ticks left for reload.
         * @param reload_left The new number of ticks left to reload.
         * @return The current weapon object.
         */
        Weapon& setReloadLeft(size_t reload_left);

        /**
         * @brief Sets the price of the weapon.
         * @param price The new price.
         * @return The current weapon object.
         */
        Weapon& setPrice(size_t price);

        /**
         * @brief Reloads the weapon and resets reload time.
         * @return The number of successful reload ticks.
         */
        virtual size_t reload();

        /**
         * @brief Decreases the reload time by one tick.
         */
        void tick();

        /**
         * @brief Fires the weapon at a target plane.
         * 
         * @param distance The distance to the target.
         * @param plane A shared pointer to the plane being fired upon.
         * @return The damage dealt by the weapon.
         */
        virtual size_t fire(double distance, std::shared_ptr<Plane> plane) = 0;

        /**
         * @brief Fires the weapon at a target ship.
         * 
         * @param distance The distance to the target.
         * @param ship A shared pointer to the ship being fired upon.
         * @return The damage dealt by the weapon.
         */
        virtual size_t fire(double distance, std::shared_ptr<Ship> ship) = 0;

        void fireAsync(double distance, std::shared_ptr<Ship> to);
        void fireAsync(double distance, std::shared_ptr<Plane> to);

        /**
         * @brief Calculates the cost of the weapon.
         * @return The cost of the weapon.
         */
        size_t cost();
    };

    /**
     * @class HeavyWeapon
     * @brief A derived class representing a heavy weapon.
     * 
     * This class overrides the fire methods for heavy weapon-specific behavior.
     */
    class HeavyWeapon : public Weapon {
    public:
        /**
         * @brief Constructs a HeavyWeapon with the specified parameters.
         * 
         * @param damage The damage dealt by the weapon.
         * @param ammo The ammo used by the weapon.
         * @param name The unique name of the weapon.
         * @param activity The activity status of the weapon.
         * @param max_ammo The maximum ammo capacity of the weapon.
         * @param range The range of the weapon.
         * @param fire_rate The fire rate of the weapon.
         * @param reload_time The reload time in ticks.
         * @param reload_left The number of ticks left for reload.
         * @param price The price of the weapon.
         */
        HeavyWeapon(size_t damage, std::shared_ptr<Ammo> ammo, std::string name, bool activity, const size_t max_ammo,
                    size_t range, size_t fire_rate, const size_t reload_time, size_t reload_left, size_t price);

        /**
         * @brief Fires the heavy weapon at a target ship.
         * @param distance The distance to the target.
         * @param ship A shared pointer to the ship being fired upon.
         * @return The damage dealt by the weapon.
         */
        size_t fire(double distance, std::shared_ptr<Ship> ship) override;

        /**
         * @brief Fires the heavy weapon at a target plane.
         * @param distance The distance to the target.
         * @param plane A shared pointer to the plane being fired upon.
         * @return The damage dealt by the weapon.
         */
        size_t fire(double distance, std::shared_ptr<Plane> plane) override;
    };

    /**
     * @class LightWeapon
     * @brief A derived class representing a light weapon.
     * 
     * This class overrides the fire methods for light weapon-specific behavior.
     */
    class LightWeapon : public Weapon {
    public:
        /**
         * @brief Constructs a LightWeapon with the specified parameters.
         * 
         * @param damage The damage dealt by the weapon.
         * @param ammo The ammo used by the weapon.
         * @param name The unique name of the weapon.
         * @param activity The activity status of the weapon.
         * @param max_ammo The maximum ammo capacity of the weapon.
         * @param range The range of the weapon.
         * @param fire_rate The fire rate of the weapon.
         * @param reload_time The reload time in ticks.
         * @param reload_left The number of ticks left for reload.
         * @param price The price of the weapon.
         */
        LightWeapon(size_t damage, std::shared_ptr<Ammo> ammo, std::string name, bool activity, const size_t max_ammo,
                    size_t range, size_t fire_rate, const size_t reload_time, size_t reload_left, size_t price);

        /**
         * @brief Fires the light weapon at a target plane.
         * @param distance The distance to the target.
         * @param plane A shared pointer to the plane being fired upon.
         * @return The damage dealt by the weapon.
         */
        size_t fire(double distance, std::shared_ptr<Plane> plane) override;

        /**
         * @brief Fires the light weapon at a target ship.
         * @param distance The distance to the target.
         * @param ship A shared pointer to the ship being fired upon.
         * @return The damage dealt by the weapon.
         */
        size_t fire(double distance, std::shared_ptr<Ship> ship) override;
    };
}

#endif // WEAPON_H
