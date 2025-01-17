#ifndef TEXTFIELD_HPP
#define TEXTFIELD_HPP

#include <SFML/Graphics.hpp>
#include <string>

class TextField {
public:
    TextField(sf::Font& font, sf::Vector2f position, sf::Vector2f size);

    virtual void handleEvent(const sf::Event& event);
    void draw(sf::RenderWindow& window);
    void setFocus(bool focus);
    bool contains(sf::Vector2f point) const;
    void setString(const std::string&);
    std::string& getString();
    
protected:
    bool isFocused;
    sf::RectangleShape box;
    sf::Text text;
    std::string input;
};

class NumField : public TextField {
public:
    NumField(sf::Font& font, sf::Vector2f position, sf::Vector2f size);

    void handleEvent(const sf::Event& event) override;
};

#endif // TEXTFIELD_HPP