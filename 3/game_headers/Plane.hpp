#ifndef PLANE_H
#define PLANE_H

#include "generic.hpp"
#include "Ammo.hpp"
#include "Ship.hpp"
#include <memory>
#include <thread>
#include <mutex>

namespace zasada{
    class Ship;
    class Plane
    {
    protected:
        size_t damage;
        bool activity = false;
        size_t health;
        size_t speed;

        std::string name;
        
        std::shared_ptr<Ammo> ammo;
        size_t max_ammo;
        const plane_t type = def_plane;

        size_t fuel_capacity;
        size_t fuel_current;
        size_t fuel_cons;
        size_t refill_fuel;
        point position;
        
        size_t price;
        size_t range;
        std::mutex mtx;
    public:
        Plane();
        Plane(size_t _damage, bool _activity, size_t _health, size_t _speed,
          const std::string& _name, std::shared_ptr<Ammo> _ammo, size_t _max_ammo,
          size_t _fuel_capacity, size_t _fuel_current, size_t _fuel_cons,
          size_t _refill_fuel, point _position, size_t _price, size_t _range);
        virtual ~Plane() = 0;

        //getters
        size_t getDamage() const;
        bool getActivity() const;
        size_t getHealth() const;
        size_t getSpeed() const;

        std::string getName() const;

        std::shared_ptr<Ammo> getAmmo() const;
        size_t getMaxAmmo() const;

        size_t getFuelCurrent() const;
        size_t getFuelCapacity() const;
        size_t getFuelCons() const;
        size_t getRefillFuel() const;
        point getPosition() const;

        size_t getPrice() const;
        size_t getRange() const;

        // Setters
        Plane& setDamage(size_t);
        Plane& setActivity(bool);
        Plane& setHealth(size_t);
        Plane& setSpeed(size_t);

        Plane& setName(const std::string&);

        Plane& setAmmo(std::shared_ptr<Ammo>);
        Plane& setMaxAmmo(size_t);

        Plane& setFuelCurrent(size_t);
        Plane& setFuelCapacity(size_t);
        Plane& setFuelCons(size_t);
        Plane& setRefillFuel(size_t);
        Plane& moveTo(point);
        void moveToAsync(point);
        Plane& setPosition(point);

        Plane& setPrice(size_t);
        Plane& setRange(size_t);


        virtual Plane& takeDamage(size_t);
        virtual size_t attack(double distance, std::shared_ptr<Plane>);
        virtual size_t attack(double distance, std::shared_ptr<Ship>);
        void attackAsync(double distance, std::shared_ptr<Plane> target);
        void attackAsync(double distance, std::shared_ptr<Ship> target);
        size_t cost();
    };

    class Fighter : public Plane{
        private:
            const plane_t type = fighter;
        public:
        Fighter(size_t _damage, bool _activity, size_t _health, size_t _speed,
          const std::string& _name, std::shared_ptr<Ammo> _ammo, size_t _max_ammo,
          size_t _fuel_capacity, size_t _fuel_current, size_t _fuel_cons,
          size_t _refill_fuel, point _position, size_t _price, size_t _range);
            size_t attack(double distance, std::shared_ptr<Plane>) override;
    };

    class StormTrooper : public Plane{
        private:
            const plane_t type = storm_trooper;
        public:
        StormTrooper(size_t _damage, bool _activity, size_t _health, size_t _speed,
          const std::string& _name, std::shared_ptr<Ammo> _ammo, size_t _max_ammo,
          size_t _fuel_capacity, size_t _fuel_current, size_t _fuel_cons,
          size_t _refill_fuel, point _position, size_t _price, size_t _range);
            size_t attack(double distance, std::shared_ptr<Ship>) override;
    };
    
} // namespace zasada


#endif