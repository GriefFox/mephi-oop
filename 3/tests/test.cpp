#define CATCH_CONFIG_MAIN

#include "Table.hpp"
#include "game_headers/Weapon.hpp"
#include "game_headers/Ammo.hpp"
#include "game_headers/Ship.hpp"
#include "game_headers/Plane.hpp"
#include <sstream>
#include <catch2/catch_all.hpp>

namespace zasada {
TEST_CASE("Table can be constructed and destroyed", "[Table]") {
    zasada::Table<int, int> table;  // Default capacity
    REQUIRE(table.size() == 0);    // Table is empty
}

TEST_CASE("Insert adds elements to the table", "[Table]") {
    zasada::Table<std::string, int> table;

    table.insert("key1", 10);
    table.insert("key2", 20);

    REQUIRE(table.size() == 2);         // Size should be 2
    REQUIRE(*table.find("key1") == 10); // Value for "key1" should be 10
    REQUIRE(*table.find("key2") == 20); // Value for "key2" should be 20
}

TEST_CASE("Erase removes elements from the table", "[Table]") {
    zasada::Table<std::string, int> table;

    table.insert("key1", 10);
    table.insert("key2", 20);

    REQUIRE(table.erase("key1") == true);  // Erase key1
    REQUIRE(table.size() == 1);           // Size should now be 1
    REQUIRE(table.find("key1") == nullptr); // key1 should not exist

    REQUIRE(table.erase("key3") == false); // key3 doesn't exist
}

TEST_CASE("Inserting duplicate keys throws an exception", "[Table]") {
    zasada::Table<std::string, int> table;

    table.insert("key1", 10);

    REQUIRE_THROWS_AS(table.insert("key1", 20), std::runtime_error);
}

TEST_CASE("Table can be iterated over", "[Table]") {
    zasada::Table<std::string, int> table;

    table.insert("key1", 10);
    table.insert("key2", 20);

    std::vector<std::string> keys;
    std::vector<int> values;

    for (const auto& pair : table) {
        keys.push_back(pair.first);
        values.push_back(pair.second);
    }

    REQUIRE(keys.size() == 2);         // Two keys
    REQUIRE(values.size() == 2);      // Two values
    REQUIRE(std::find(keys.begin(), keys.end(), "key1") != keys.end());
    REQUIRE(std::find(values.begin(), values.end(), 10) != values.end());
}

TEST_CASE("Ammo Default Constructor", "[Ammo]") {
    Ammo ammo;

    REQUIRE(ammo.getName() == "");
    REQUIRE(ammo.getPrice() == 0);
    REQUIRE(ammo.getStorageSize() == 0);
    REQUIRE(ammo.getCurrent() == 0);
    REQUIRE(ammo.getInStorage() == 0);
}

TEST_CASE("Ammo Parameterized Constructor", "[Ammo]") {
    Ammo ammo("Bullets", 10, 50, 5, 100);

    REQUIRE(ammo.getName() == "Bullets");
    REQUIRE(ammo.getPrice() == 10);
    REQUIRE(ammo.getStorageSize() == 50);
    REQUIRE(ammo.getCurrent() == 5);
    REQUIRE(ammo.getInStorage() == 100);
}

TEST_CASE("Ammo Copy Constructor and Assignment Operator", "[Ammo]") {
    Ammo original("Shells", 20, 100, 10, 200);
    Ammo copy = original;

    REQUIRE(copy.getName() == "Shells");
    REQUIRE(copy.getPrice() == 20);
    REQUIRE(copy.getStorageSize() == 100);
    REQUIRE(copy.getCurrent() == 10);
    REQUIRE(copy.getInStorage() == 200);

    Ammo assigned;
    assigned = original;

    REQUIRE(assigned.getName() == "Shells");
    REQUIRE(assigned.getPrice() == 20);
    REQUIRE(assigned.getStorageSize() == 100);
    REQUIRE(assigned.getCurrent() == 10);
    REQUIRE(assigned.getInStorage() == 200);
}

TEST_CASE("Ammo Setters", "[Ammo]") {
    Ammo ammo;

    ammo.setName("Rockets")
        .setPrice(50)
        .setStorageSize(200)
        .setCurrent(20)
        .setInStorage(300);

    REQUIRE(ammo.getName() == "Rockets");
    REQUIRE(ammo.getPrice() == 50);
    REQUIRE(ammo.getStorageSize() == 200);
    REQUIRE(ammo.getCurrent() == 20);
    REQUIRE(ammo.getInStorage() == 300);
}

TEST_CASE("Ammo Reduce", "[Ammo]") {
    Ammo ammo("Bullets", 10, 50, 10, 100);

    REQUIRE_NOTHROW(ammo.reduce(5));
    REQUIRE(ammo.getCurrent() == 5);

    REQUIRE_THROWS_AS(ammo.reduce(10), std::out_of_range);
}

TEST_CASE("Ammo Reload", "[Ammo]") {
    Ammo ammo("Bullets", 10, 50, 5, 100);

    size_t reloaded = ammo.reload(20);
    REQUIRE(reloaded == 15);
    REQUIRE(ammo.getCurrent() == 20);
    REQUIRE(ammo.getInStorage() == 85);

    reloaded = ammo.reload(30);
    REQUIRE(reloaded == 10);
    REQUIRE(ammo.getCurrent() == 30);
    REQUIRE(ammo.getInStorage() == 75);
}

TEST_CASE("Ammo Consume", "[Ammo]") {
    Ammo ammo("Bullets", 10, 50, 1, 100);

    REQUIRE(ammo.consume() == 50);
    REQUIRE(ammo.getCurrent() == 0);

    REQUIRE_THROWS_AS(ammo.consume(), std::out_of_range);
}

TEST_CASE("Ammo Cost Calculation", "[Ammo]") {
    Ammo ammo("Bullets", 10, 50, 5, 100);

    size_t cost = ammo.cost();
    REQUIRE(cost == (5 * 10 + 100 * 5)); // current * price + in_storage * current
}


} // namespace zasada