#ifndef AMMO_H
#define AMMO_H

#include <string>

namespace zasada {
    class Ammo{
        private:
            std::string name;
            size_t price; 
            size_t storage_size; //reflects how much space one projectile takes up 
            size_t current; 
            size_t in_storage;

        public:
            // structor
            Ammo();
            ~Ammo();
            // Ammo(const Ammo& other); // Copy constructor
            // Ammo& operator=(const Ammo& other); // Copy assignment operator

            // getters
            std::string getName() const;
            size_t getPrice() const;
            size_t getStorageSize() const;
            size_t getCurrent() const;
            size_t getInStorage() const;

            // setters
            Ammo& setName(const std::string&);
            Ammo& setPrice(const size_t);
            Ammo& setStorageSize(const size_t);
            Ammo& setCurrent(const size_t);
            Ammo& setInStorage(const size_t);

            Ammo& reduce(size_t);
            size_t reload(size_t);   
            size_t consume(); //returns how much space freed
            size_t cost();

    };
}

#endif