#ifndef PLANE_H
#define PLANE_H

#include "generic.hpp"
#include "Ammo.hpp"
#include "Ship.hpp"
#include <memory>

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
        size_t fuel_cons;
        size_t refill_fuel;
        point position;
        
        size_t price;
        size_t range;
    public:
        Plane();
        virtual ~Plane() = 0;

        //getters
        size_t getDamage() const;
        bool getActivity() const;
        size_t getHealth() const;
        size_t getSpeed() const;

        std::string getName() const;

        std::shared_ptr<Ammo> getAmmo() const;
        size_t getMaxAmmo() const;

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

        Plane& setFuelCapacity(size_t);
        Plane& setFuelCons(size_t);
        Plane& setRefillFuel(size_t);
        Plane& moveTo(point);

        Plane& setPrice(size_t);
        Plane& setRange(size_t);

        //TODO right move
        virtual Plane& takeDamage(size_t);
        virtual size_t attack(const Ship*, std::shared_ptr<Plane>);
        virtual size_t attack(const Ship*, std::shared_ptr<Ship>);

        size_t cost();
    };

    class Fighter : public Plane{
        private:
            const plane_t type = fighter;
        public:
            size_t attack(const Ship*, std::shared_ptr<Plane>) override;
    };

    class StormTrooper : public Plane{
        private:
            const plane_t type = storm_trooper;
        public:
            size_t attack(const Ship*, std::shared_ptr<Ship>) override;
    };
    
} // namespace zasada


#endif