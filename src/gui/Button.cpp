// Button.cpp
#include "Button.hpp"

Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text, sf::Font& font)
    : label(font, sf::String(text), 16) {
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Blue);

    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(16);
    label.setFillColor(sf::Color::White);
    label.setPosition(sf::Vector2f(position.x + 10, position.y + 5));
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(label);
}

bool Button::isClicked(const sf::Vector2i& mousePos) const {
    return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}
