// Button.h
#pragma once
#include <SFML/Graphics.hpp>

class Button {
public:
    Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text, sf::Font& font);

    void draw(sf::RenderWindow& window);
    bool isClicked(const sf::Vector2i& mousePos) const;

private:
    sf::RectangleShape shape;
    sf::Text label;
};
