#include <cmath>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "LoadoutWindow.h"
#include "game_headers/Ship.hpp"
#include "game_headers/Mission.hpp" // Include your Mission class header


using json = nlohmann::json;

void parseMissionConfig(const std::string& filePath, zasada::Mission& mission) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << filePath << std::endl;
        return;
    }

    json config;
    file >> config;

    if (config.contains("max_ships")) {
        mission.setMaxShips(config["max_ships"]);
    }
    if (config.contains("max_money")) {
        mission.setMaxSpend(config["max_money"]);
    }
    if (config.contains("win_price")) {
        mission.setWinPrice(config["win_price"]);
    }
    if (config.contains("point_a")) {
        mission.setPointA({config["point_a"][0], config["point_a"][1]});
    }
    if (config.contains("point_b")) {
        mission.setPointB({config["point_b"][0], config["point_b"][1]});
    }
    if (config.contains("attack_ships")){
        auto cfg = config["attack_ships"]["cruiser"];
        auto carShip = std::make_shared<zasada::Cruiser>(cfg["name"], cfg["speed"], cfg["health"], cfg["price"]);
        mission.getTableAttacker().insert(carShip->getName(), carShip);
        std::cout << mission.getTableAttacker().size() << std::endl;
    }
}

void runLoadoutSetup(sf::RenderWindow& loadoutWindow, zasada::Mission& mission) {
    parseMissionConfig("mission_config.json", mission);

    sf::Color loadoutColor(200, 200, 200); // Gray color for the loadout window
    bool switchToMain = false;

    sf::Font font;
    if(!font.loadFromFile("/usr/share/fonts/gnu-free/FreeMonoBold.otf")){
        std::cerr << "Error loading font" << std::endl;
        return;
    }
    std::vector<std::unique_ptr<TextField>> textFields;
    sf::Text text;
    text.setFont(font);
    text.setString("Loadout Setup");
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(LOADOUT_WIDTH/2-text.getGlobalBounds().width/2,10);

    std::vector<sf::Text> texts;
    texts.emplace_back("", font, 20);
    texts.emplace_back("For each ship enter its name(names can't repeat) Everything costs 500", font, 16);
    texts.emplace_back("Buy cruiser", font, 20);
    texts.emplace_back("Buy carrier", font, 20);
    texts.emplace_back("Buy Carrier with weapon", font, 20);
    texts.emplace_back("Buy Light weapon(ship, weapon)", font, 20);
    texts.emplace_back("Buy Heavy weapon(ship, weapon)", font, 20);
    texts.emplace_back("Buy Plane Fighter(ship, plane)", font, 20);
    texts.emplace_back("Buy Plane StormTrooper(ship, plane)", font, 20);
    texts.emplace_back("Move plane(ship, plane, ship)", font, 20);
    texts.emplace_back("Sell ship", font, 20);
    texts.emplace_back("Sell plane", font, 20);
    texts.emplace_back("Sell weapon", font, 20);
    
    for (size_t i=0; i<texts.size();i++){
        texts[i].setPosition(sf::Vector2f(10, 50+i*50));
        texts[i].setFillColor(sf::Color::Black);
    }

    std::vector<Button> buttons;
    for (int i=0; i<7; i++){
        buttons.emplace_back(sf::Vector2f(50, 30), sf::Vector2f(700, 150 + i*50), font, "Buy");
    }
    buttons.emplace_back(sf::Vector2f(50, 30), sf::Vector2f(700, 500), font, "Move");
    for (int i=0; i<3;i++){
        buttons.emplace_back(sf::Vector2f(50, 30), sf::Vector2f(700, 550+i*50), font, "Sell");
    }
    buttons.emplace_back(sf::Vector2f(100, 25), sf::Vector2f(680, 750), font, "Continue");

    textFields.push_back(std::make_unique<TextField>(font, sf::Vector2f(450, 150), sf::Vector2f(200, 30)));
    textFields.push_back(std::make_unique<TextField>(font, sf::Vector2f(450, 200), sf::Vector2f(200, 30)));
    textFields.push_back(std::make_unique<TextField>(font, sf::Vector2f(450, 250), sf::Vector2f(200, 30)));
    for (int i=0; i<4;i++){
        textFields.push_back(std::make_unique<TextField>(font, sf::Vector2f(450, 300+i*50), sf::Vector2f(95, 30)));
        textFields.push_back(std::make_unique<TextField>(font, sf::Vector2f(555, 300+i*50), sf::Vector2f(95, 30)));
    }
    textFields.push_back(std::make_unique<TextField>(font, sf::Vector2f(450, 500), sf::Vector2f(60, 30)));
    textFields.push_back(std::make_unique<TextField>(font, sf::Vector2f(450+70, 500), sf::Vector2f(60, 30)));
    textFields.push_back(std::make_unique<TextField>(font, sf::Vector2f(450+140, 500), sf::Vector2f(60, 30)));

    textFields.push_back(std::make_unique<TextField>(font, sf::Vector2f(450, 550), sf::Vector2f(200, 30)));
    textFields.push_back(std::make_unique<TextField>(font, sf::Vector2f(450, 600), sf::Vector2f(95, 30)));
    textFields.push_back(std::make_unique<TextField>(font, sf::Vector2f(555, 600), sf::Vector2f(95, 30)));
    textFields.push_back(std::make_unique<TextField>(font, sf::Vector2f(450, 650), sf::Vector2f(95, 30)));
    textFields.push_back(std::make_unique<TextField>(font, sf::Vector2f(555, 650), sf::Vector2f(95, 30)));


    buttons[0].setCallback([&mission, &textFields]() {
        std::string ShipName = textFields[0]->getString();
        if (ShipName.empty()) {
            std::cout << "Ship name cannot be empty" << std::endl;
            return;
        }
        auto ammo = std::make_shared<zasada::Ammo>("ammo", 0, 1, 100, 0);
        auto carShip = std::make_shared<zasada::Cruiser>(ShipName, 1, 400, 500);
        carShip->setAmmo(ammo);
        try{
            mission.buyShip(carShip);
        } catch (std::runtime_error e){
            std::cout << "Can't buy this ship" << std::endl;
        }
    });

    buttons[1].setCallback([&mission, &textFields]() {
        std::string ShipName = textFields[1]->getString();
        if (ShipName.empty()) {
            std::cout << "Ship name cannot be empty" << std::endl;
            return;
        }
        auto carShip = std::make_shared<zasada::Carrier>(ShipName, 1, 250, 500);
        try{
            mission.buyShip(carShip);
        } catch (std::runtime_error e){
            std::cout << "Can't buy this ship" << std::endl;
        }
    });

    buttons[2].setCallback([&mission, &textFields]() {
        std::string ShipName = textFields[2]->getString();
        if (ShipName.empty()) {
            std::cout << "Ship name cannot be empty" << std::endl;
            return;
        }
        auto ammo = std::make_shared<zasada::Ammo>("ammo", 0, 1, 100, 0);
        auto carShip = std::make_shared<zasada::AttackCarrier>(ShipName, 1, 250, 500);
        carShip->setAmmo(ammo);

        try{
            mission.buyShip(carShip);
        } catch (std::runtime_error e){
            std::cout << "Can't buy this ship" << std::endl;
        }
    });
    buttons[3].setCallback([&mission, &textFields](){
        std::string ShipName = textFields[3]->getString();
        std::string weaponName = textFields[4]->getString();

        if (ShipName.empty() || weaponName.empty()) {
            std::cout << "name cannot be empty" << std::endl;
            return;
        }
        auto weapon = std::make_shared<zasada::LightWeapon>(100, nullptr, weaponName, 1, 10, 50, 50, 500, 0, 500);
        try{
            mission.buyWeapon(weapon, ShipName);
        } catch (std::runtime_error e){
            std::cout << "Can't buy this weapon" << std::endl;
        }
    });

    buttons[4].setCallback([&mission, &textFields](){
        std::string ShipName = textFields[5]->getString();
        std::string weaponName = textFields[6]->getString();

        if (ShipName.empty() || weaponName.empty()) {
            std::cout << "name cannot be empty" << std::endl;
            return;
        }
        auto weapon = std::make_shared<zasada::HeavyWeapon>(100, nullptr, weaponName, 1, 10, 50, 50, 500, 0, 500);
        try{
            mission.buyWeapon(weapon, ShipName);
        } catch (std::runtime_error e){
            std::cout << "Can't buy this weapon" << std::endl;
        }
    });

    buttons[5].setCallback([&mission, &textFields](){
        std::string ShipName = textFields[7]->getString();
        std::string planeName = textFields[8]->getString();

        if (ShipName.empty() || planeName.empty()) {
            std::cout << "name cannot be empty" << std::endl;
            return;
        }
        auto plane = std::make_shared<zasada::Fighter>(100, true, 50, 300, planeName, nullptr, 10, 50, 10, 10, 10, zasada::point{0,0}, 500, 50); // Example parameters
        try {
            mission.buyPlane(plane, ShipName);
        } catch (std::runtime_error e) {
            std::cout << "Can't buy this plane" << std::endl;
        }
    });

    buttons[6].setCallback([&mission, &textFields](){
        std::string ShipName = textFields[9]->getString();
        std::string planeName = textFields[10]->getString();

        if (ShipName.empty() || planeName.empty()) {
            std::cout << "name cannot be empty" << std::endl;
            return;
        }
        auto plane = std::make_shared<zasada::StormTrooper>(100, true, 50, 300, planeName, nullptr, 10, 50, 10, 10, 10, zasada::point{0,0}, 500, 50); // Example parameters
        try {
            mission.buyPlane(plane, ShipName);
        } catch (std::runtime_error e) {
            std::cout << "Can't buy this plane" << std::endl;
        }
    });

    buttons[7].setCallback([&mission, &textFields]() {
        std::string sourceShipName = textFields[11]->getString();
        std::string planeName = textFields[12]->getString();
        std::string destinationShipName = textFields[13]->getString();

        if (sourceShipName.empty() || planeName.empty() || destinationShipName.empty()) {
            std::cout << "Source ship, plane, and destination ship names cannot be empty" << std::endl;
            return;
        }

        try {
            mission.movePlane(sourceShipName, planeName, destinationShipName);
            std::cout << "Plane moved successfully" << std::endl;
        } catch (std::runtime_error& e) {
            std::cout << "Can't move this plane: " << e.what() << std::endl;
        }
    });

    buttons[8].setCallback([&mission, &textFields]() {
        std::string ShipName = textFields[14]->getString();
        if (ShipName.empty()) {
            std::cout << "Ship name cannot be empty" << std::endl;
            return;
        }
        try {
            mission.sellShip(ShipName);
            std::cout << "Ship sold successfully" << std::endl;
        } catch (std::runtime_error& e) {
            std::cout << "Can't sell this ship: " << e.what() << std::endl;
        }
    });

    buttons[9].setCallback([&mission, &textFields]() {
        std::string ShipName = textFields[15]->getString();
        std::string planeName = textFields[16]->getString();
        if (ShipName.empty() || planeName.empty()) {
            std::cout << "Ship and plane names cannot be empty" << std::endl;
            return;
        }
        try {
            mission.sellPlane(ShipName, planeName);
            std::cout << "Plane sold successfully" << std::endl;
        } catch (std::runtime_error& e) {
            std::cout << "Can't sell this plane: " << e.what() << std::endl;
        }
    });

    buttons[10].setCallback([&mission, &textFields]() {
        std::string ShipName = textFields[17]->getString();
        std::string weaponName = textFields[18]->getString();
        if (ShipName.empty() || weaponName.empty()) {
            std::cout << "Ship and weapon names cannot be empty" << std::endl;
            return;
        }
        try {
            mission.sellWeapon(ShipName, weaponName);
            std::cout << "Weapon sold successfully" << std::endl;
        } catch (std::runtime_error& e) {
            std::cout << "Can't sell this weapon: " << e.what() << std::endl;
        }
    });

    buttons[11].setCallback([&loadoutWindow](){
        loadoutWindow.close();
    });

    while (loadoutWindow.isOpen() && !switchToMain) {
        sf::Event event;
        while (loadoutWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                loadoutWindow.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                switchToMain = true; 
                // loadoutWindow.close();
            }

            for (auto& textField : textFields) {
                textField->handleEvent(event);
            }

            for (auto& button: buttons){
                button.handleEvent(event, loadoutWindow);
            }
        }
     
        for (auto & button: buttons){
            button.update(loadoutWindow);
        }

        loadoutWindow.clear(loadoutColor);
     
        loadoutWindow.draw(text);

        for (auto& textField : textFields) {
            textField->draw(loadoutWindow);
        }
        for(auto & button: buttons){
            button.draw(loadoutWindow);
        }

        for(auto& textt: texts){
            loadoutWindow.draw(textt);
        }
        texts[0].setString("Max Ships in groups: " + std::to_string( mission.getMaxShips()) + " Spend: " + std::to_string(mission.getSpend())+ " Max can be spend: "+std::to_string(mission.getMaxSpend()));

        loadoutWindow.display();
    }


}