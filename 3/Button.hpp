#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>

class Button {
public:
    Button(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Font& font, const std::string& text) {
        buttonShape.setSize(size);
        buttonShape.setPosition(position);
        buttonShape.setFillColor(sf::Color::Blue);

        buttonText.setFont(font);
        buttonText.setString(text);
        buttonText.setCharacterSize(20);
        buttonText.setFillColor(sf::Color::White);
        buttonText.setPosition(
            position.x + (size.x - buttonText.getLocalBounds().width) / 2, //+ (size.x - buttonText.getLocalBounds().width) / 2,
            position.y //+ (size.y - buttonText.getLocalBounds().height) / 2
        );
    }

    void setCallback(std::function<void()> callback) {
        this->callback = callback;
    }

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (isMouseOver(window)) {
                if (callback) callback();
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(buttonShape);
        window.draw(buttonText);
    }

    void update(const sf::RenderWindow& window) {
        if (isMouseOver(window)) {
            sf::Color color(150, 150, 150);
            buttonShape.setFillColor(color);
        } else {
            sf::Color color(100, 100, 100);
            buttonShape.setFillColor(color);
        }
    }

private:
    bool isMouseOver(const sf::RenderWindow& window) const {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        return buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }

    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    std::function<void()> callback;
};

#endif