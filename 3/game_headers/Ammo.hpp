#ifndef AMMO_H
#define AMMO_H

#include <string>
#include <thread>
#include <mutex>

namespace zasada {

    /**
     * @class Ammo
     * @brief Represents ammunition used in weapons.
     * 
     * The `Ammo` class defines the properties of ammunition, including its name, price, 
     * storage size, current count, and total count in storage. It provides methods for 
     * managing the amount of ammo, including reducing, reloading, and calculating costs.
     */
    class Ammo {
        private:
            std::string name;          ///< Name of the ammunition.
            size_t price;              ///< Price of the ammunition.
            size_t storage_size;       ///< Amount of storage space taken by one unit of ammo.
            size_t current;            ///< Current amount of ammo being used.
            size_t in_storage;         ///< Total amount of ammo in storage.
            std::mutex mtx;            ///< Mutex var

        public:
            /**
             * @brief Default constructor for Ammo.
             */
            Ammo();

            /**
             * @brief Destructor for Ammo.
             */
            ~Ammo();

            /**
             * @brief Parameterized constructor for Ammo.
             * @param _name Name of the ammunition.
             * @param _price Price of the ammunition.
             * @param _storage_size Storage space taken by one unit of ammo.
             * @param _current Current amount of ammo being used.
             * @param _in_storage Total amount of ammo in storage.
             */
            Ammo(std::string _name, size_t _price, size_t _storage_size, size_t _current, size_t _in_storage);

            /**
             * @brief Copy constructor for Ammo.
             * @param other The Ammo object to copy.
             */
            Ammo(const Ammo& other);

            /**
             * @brief Copy assignment operator for Ammo.
             * @param other The Ammo object to assign from.
             * @return A reference to the current Ammo object.
             */
            Ammo& operator=(const Ammo& other);

            // Getters

            /**
             * @brief Gets the name of the ammunition.
             * @return The name of the ammunition.
             */
            std::string getName() const;

            /**
             * @brief Gets the price of the ammunition.
             * @return The price of the ammunition.
             */
            size_t getPrice() const;

            /**
             * @brief Gets the storage size of the ammunition.
             * @return The storage size (space taken by one projectile).
             */
            size_t getStorageSize() const;

            /**
             * @brief Gets the current amount of ammunition being used.
             * @return The current amount of ammo.
             */
            size_t getCurrent() const;

            /**
             * @brief Gets the total amount of ammunition in storage.
             * @return The total amount of ammo in storage.
             */
            size_t getInStorage() const;

            // Setters

            /**
             * @brief Sets the name of the ammunition.
             * @param _name The new name of the ammunition.
             * @return A reference to the Ammo object.
             */
            Ammo& setName(const std::string& _name);

            /**
             * @brief Sets the price of the ammunition.
             * @param _price The new price of the ammunition.
             * @return A reference to the Ammo object.
             */
            Ammo& setPrice(const size_t _price);

            /**
             * @brief Sets the storage size of the ammunition.
             * @param _storage_size The new storage size of the ammunition.
             * @return A reference to the Ammo object.
             */
            Ammo& setStorageSize(const size_t _storage_size);

            /**
             * @brief Sets the current amount of ammunition being used.
             * @param _current The new current amount of ammo being used.
             * @return A reference to the Ammo object.
             */
            Ammo& setCurrent(const size_t _current);

            /**
             * @brief Sets the total amount of ammunition in storage.
             * @param _in_storage The new total amount of ammo in storage.
             * @return A reference to the Ammo object.
             */
            Ammo& setInStorage(const size_t _in_storage);

            /**
             * @brief Reduces the amount of ammo being used.
             * @param amount The amount of ammo to reduce.
             * @return A reference to the Ammo object.
             */
            Ammo& reduce(size_t amount);

            /**
             * @brief Reloads the ammunition.
             * @param amount The amount of ammo to reload.
             * @return The new total amount of ammo in storage after reload.
             */
            size_t reload(size_t amount);

            /**
             * @brief Consumes some ammo, freeing up storage space.
             * @return The amount of space freed by consuming ammo.
             */
            size_t consume();

            /**
             * @brief Calculates the cost of the ammunition.
             * @return The cost of the ammunition.
             */
            size_t cost();
    };

}

#endif
