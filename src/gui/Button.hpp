#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button {
public:
    sf::RectangleShape shape;
    sf::Text text;
    std::function<void()> onClick;

    Button(const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& buttonText, std::function<void()> onClick)
        : onClick(onClick) {
        shape.setSize(size);
        shape.setPosition(pos);
        shape.setFillColor(sf::Color::Green);

        sf::Font font;
        text.setFont(font);
        text.setString(buttonText);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(pos.x + 10, pos.y + 10); // Ustawienie tekstu w przycisku
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }

    bool isMouseOver(const sf::Vector2i& mousePos) {
        return shape.getGlobalBounds().contains(sf::Vector2f(mousePos));
    }

    void checkClick(const sf::Vector2i& mousePos, const sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed && isMouseOver(mousePos)) {
            onClick(); // Wywołaj funkcję po kliknięciu
        }
    }
};
