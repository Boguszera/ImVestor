// Button.cpp
#include "Button.hpp"

Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text, sf::Font& font, ButtonType type)
    : label(font, sf::String(text), 16) {
    shape.setSize(size);
    shape.setPosition(position);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color(230, 230, 230));
    shape.setFillColor(sf::Color::Blue);

    if (type == ButtonType::Buy) {
        normalColor = sf::Color(0, 180, 120);          // morski zielony
        hoverColor  = sf::Color(0, 210, 150);
    } else {
        normalColor = sf::Color(200, 60, 80);          // ciepła czerwień
        hoverColor  = sf::Color(230, 80, 100);
    }

    shape.setFillColor(normalColor);
    label.setFillColor(sf::Color(230, 230, 230));

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

void Button::updateHover(const sf::Vector2i& mousePos) {
    if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        shape.setFillColor(hoverColor);
    } else {
        shape.setFillColor(normalColor);
    }
}



