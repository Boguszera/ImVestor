// Button.hpp
enum class ButtonType { Buy, Sell };
#include <SFML/Graphics.hpp>

class Button {
public:
    Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text, sf::Font& font, ButtonType type);

    void draw(sf::RenderWindow& window);
    bool isClicked(const sf::Vector2i& mousePos) const;
    void updateHover(const sf::Vector2i& mousePos);

private:
    sf::RectangleShape shape;
    sf::Text label;
    sf::Color normalColor;
    sf::Color hoverColor;
    ButtonType type;
};
