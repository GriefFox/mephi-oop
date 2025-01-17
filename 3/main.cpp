#include "game_headers/Mission.hpp"
#include "game_headers/Table.hpp"
#include "game_headers/Ship.hpp"
#include "LoadoutWindow.h"
#include <cmath>
#include <iostream>

int main(){
    std::shared_ptr<zasada::Cruiser> Def = std::make_shared<zasada::Cruiser>("Def", 1, 5000000, 500);
    std::shared_ptr<zasada::Cruiser> Att = std::make_shared<zasada::Cruiser>("Att", 1, 4000000, 500);

    std::shared_ptr<zasada::Ammo> amm_def = std::make_shared<zasada::Ammo>("def", 0, 1, 10000000, 50);
    std::shared_ptr<zasada::Ammo> amm_att = std::make_shared<zasada::Ammo>("att", 0, 1, 10000000, 50);

    std::vector<std::shared_ptr<zasada::HeavyWeapon>> weapons_def;
    std::vector<std::shared_ptr<zasada::HeavyWeapon>> weapons_att;

    for (int i = 0; i < 5; ++i) {
    weapons_def.push_back(std::make_shared<zasada::HeavyWeapon>(
        5, amm_def, "D_wep" + std::to_string(i), 1, 100, 1000, 2, 1, 0, 300));

    weapons_att.push_back(std::make_shared<zasada::HeavyWeapon>(
        5, amm_att, "A_wep" + std::to_string(i), 1, 100, 1000, 2, 1, 0, 300));
    }
    // std::shared_ptr<zasada::HeavyWeapon> Def_weap = std::make_shared<zasada::HeavyWeapon>(20, amm_def, "D_wep", 1, 100, 1000, 2, 1, 0, 300);
    // std::shared_ptr<zasada::HeavyWeapon> Att_weap = std::make_shared<zasada::HeavyWeapon>(20, amm_att, "A_wep", 1, 100, 1000, 2, 1, 0, 300);
    for (int i=0; i<4;i++){
        Def->setWeapon(weapons_def[i]);
        Att->setWeapon(weapons_att[i]);
    }

    Def->setPosition({0,0});
    Att->setPosition({0,0});
    std::vector<std::thread> threads;
    std::cout << "started" << std::endl;
    auto start = std::chrono::steady_clock::now();
    while (Att->getHealth() > 0 && Def->getHealth() > 0){
        // threads.emplace_back([&Att, &Def](){
        for (const auto [name, weapon]: Att->getWeapons()){
            auto tmp = weapon->getName();
            threads.push_back(Att->attack(tmp, std::dynamic_pointer_cast<zasada::Ship>(Def)));
            // Att->performAttack(weapon, zasada::calculate_distace(Def->getPosition(), Att->getPosition()), Def);
        }
        // });

        for (const auto [name, weapon]: Def->getWeapons()){
            auto tmp = weapon->getName();
            // Def->performAttack(weapon, zasada::calculate_distace(Def->getPosition(), Att->getPosition()), Att);
            threads.push_back(Def->attack(tmp, std::dynamic_pointer_cast<zasada::Ship>(Att)));
        }
        // });


        for (auto& thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }

        threads.clear();
        // std::cout << Att->getHealth() << " " << Def->getHealth() << std::endl;
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Elapsed time: " << elapsed.count() << " ms" << std::endl;
}