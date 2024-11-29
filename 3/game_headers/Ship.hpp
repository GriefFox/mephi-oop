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
namespace zasada{
    class Plane;
    class Weapon;
    class Ship{
        protected:
            std::string name;
            capitan_info capitan;
            size_t speed;
            size_t health;
            point coordinates;
            point finish;
            size_t price;
        public:
            Ship();
            virtual ~Ship() = 0;
            
            //getters
            std::string getName() const;
            capitan_info getCapitan() const;
            size_t getSpeed() const;
            size_t getHealth() const;
            point getCoordinates() const;
            point getFinish() const;
            size_t getPrice() const;
            
            //setters
            Ship& setCapitan(const capitan_info& newCapitan);
            Ship& setSpeed(size_t newSpeed);
            Ship& setHealth(size_t newHealth);
            Ship& setCoordinates(const point& newCoordinates);
            Ship& setFinish(const point& newFinish);
            Ship& setPrice(size_t newPrice);

            virtual size_t cost();
            virtual void move();
            virtual void takeDamage(size_t);
            
    };

    class Cruiser : protected Ship {
        protected:
            std::unordered_map<std::string, std::shared_ptr<Weapon>> weapons;
            size_t max_weapon;
            size_t storage_space;
            std::unordered_map<std::string, std::shared_ptr<Ammo>> ammo_list;
        public:
            ~Cruiser();
            std::shared_ptr<Weapon> getWeapon(const std::string&) const;
            std::shared_ptr<Ammo> getAmmo(const std::string&) const;
            virtual Cruiser& setWeapon(std::shared_ptr<Weapon>);
            Cruiser& setAmmo(std::shared_ptr<Ammo>);
            virtual size_t getSpace() const;
            void reload(std::string&);
            virtual void attack(std::string&, std::shared_ptr<Plane>);
            virtual void attack(std::string&, std::shared_ptr<Ship>);

            virtual size_t cost() override;
    };

    class Carrier : public Ship{
        protected:
            size_t maxPlanes;
            
            std::unordered_map<std::string, std::shared_ptr<Plane>> planes;
        public:        
            std::shared_ptr<Plane> getPlane(std::string&) const;
            Carrier& setPlane(std::shared_ptr<Plane>);
            
            virtual void flight(std::string&, std::shared_ptr<Ship>);
            virtual void flight(std::string&, std::shared_ptr<Plane>);

            virtual size_t cost() override;

    };

    class AttackCarrier : public Cruiser, Carrier{
        public:
            virtual AttackCarrier& setWeapon(std::shared_ptr<Weapon>) override;
            virtual size_t cost() override;
    };
    


} // namespace zasada


#endif