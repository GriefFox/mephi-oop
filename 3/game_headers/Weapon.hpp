#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <memory>
#include <stdexcept>

#include "Ship.hpp"
#include "Plane.hpp"
#include "Ammo.hpp"

namespace zasada {
    class Ship;
    class Plane;
    class Weapon{
        
        protected:
            const weapon_t type = weapon_t::def_weap;
            size_t damage;
            std::shared_ptr<Ammo> ammo;
            std::string name; // a uniq ID
            bool activity;
            const size_t max_ammo = 0;
            size_t range;
            size_t fire_rate;
            const size_t reload_time; // how many ticks it will reload
            size_t reload_left; // how many ticks left to reload
            size_t price;
            
        public:
            Weapon();
            virtual ~Weapon();

            //getter
            weapon_t getType() const;
            virtual size_t getDamage() const;
            std::shared_ptr<Ammo> getAmmo() const;
            std::string getName() const;
            bool getActivity() const;
            size_t getRange() const;
            size_t getMaxAmmo() const;
            size_t getFireRate() const;
            size_t getReloadTime() const;
            size_t getReloadLeft() const;

            size_t getPrice() const;

            //setter
            Weapon& setDamage(size_t);
            Weapon& setAmmo(std::shared_ptr<Ammo>);
            Weapon& setName(const std::string&);
            Weapon& setActivity(bool);
            Weapon& setRange(size_t);
            Weapon& setFireRate(size_t);
            Weapon& setReloadLeft(size_t);
            Weapon& setPrice(size_t);

            virtual size_t reload();
            void tick(); // reduce time left to reload
            virtual size_t fire(const Ship*, std::shared_ptr<Plane>);
            virtual size_t fire(const Ship*, std::shared_ptr<Ship>);

            size_t cost();
    };

    class HeavyWeapon : public Weapon{
        private:
            weapon_t type = heavy;
        public:
            size_t fire(const Ship*, std::shared_ptr<Ship>) override;
    };

    class LightWeapon : public Weapon{
        private:
            weapon_t type = light;
        public:
            size_t fire(const Ship*, std::shared_ptr<Plane>) override;
    };
}

#endif