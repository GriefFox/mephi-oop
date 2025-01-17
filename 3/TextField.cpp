#include "TextField.hpp"
#include <cctype> // For std::isdigit

TextField::TextField(sf::Font& font, sf::Vector2f position, sf::Vector2f size)
    : isFocused(false), box(size), text("", font, 24) {
    box.setPosition(position);
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(1);

    text.setPosition(position.x + 5, position.y + 5);
    text.setFillColor(sf::Color::Black);
}

void TextField::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        setFocus(contains(mousePos));
    }
    if (isFocused && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b' && !input.empty()) { // Handle backspace
            input.pop_back();
        } else if (event.text.unicode < 128 && event.text.unicode != '\b') {
            input += static_cast<char>(event.text.unicode);
        }
        text.setString(input);
    }
}

void TextField::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(text);
}

void TextField::setFocus(bool focus) {
    isFocused = focus;
    box.setOutlineColor(isFocused ? sf::Color::Blue : sf::Color::Black);
}

bool TextField::contains(sf::Vector2f point) const {
    return box.getGlobalBounds().contains(point);
}
void TextField::setString(const std::string& String){
    input = String;
    text.setString(input);
}

std::string& TextField::getString(){
    return this->input;
}

NumField::NumField(sf::Font& font, sf::Vector2f position, sf::Vector2f size)
    : TextField(font, position, size) {}

void NumField::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            setFocus(contains(mousePos));
        }
    if (isFocused && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b' && !input.empty()) { // Handle backspace
            input.pop_back();
        } else if (event.text.unicode < 128 && std::isdigit(static_cast<char>(event.text.unicode))) {
            input += static_cast<char>(event.text.unicode);
        }
        text.setString(input);
    }
}