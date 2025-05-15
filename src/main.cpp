#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include "Company.h"
#include "User.h"
#include "TransactionManager.h"
#include "Portfolio.h"
#include "Button.hpp"
#include <SFML/Graphics.hpp>
#include <variant>
#include <random>

std::string formatTo2DecimalString(double value) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << value;
    return oss.str();
}

int main(){
    sf::RenderWindow window(sf::VideoMode({800, 600}), "ImVestor");

    User user("Filip", 10000);

    Portfolio portfolio;

    Company companyA("Apple Inc.", "AAPL", "Technology", 150, 8000);
    Company companyB("Tesla Inc.", "TSLA", "Automotive", 350, 900);
    Company companyC("Orlen", "ORL", "Energy", 280, 10000);
    Company companyD("Allegro SA", "ALG", "E-commerce", 70, 15000);
    Company companyE("PKO BP", "PKO", "Finances", 90, 20000);
    Company companyF("Ubisoft", "UBI", "Gaming", 120, 12000);

    std::vector<Company> companies = { companyA, companyB, companyC, companyD, companyE, companyF};
    for (auto& company : companies) {
        company.initTrend();
    }

    std::vector<Button> buyButtons;
    std::vector<Button> sellButtons;
    sf::Clock priceUpdateClock;

    sf::Font font;
    if (!font.openFromFile("assets/ARIAL.ttf")) {
        std::cout << "Nie udało się załadować czcionki!" << std::endl;
        return -1;
    }

    // draw buttons
        for (size_t i = 0; i < companies.size(); ++i) {
            buyButtons.emplace_back(sf::Vector2f(60, 30), sf::Vector2f(400, 50 + i * 40), "Buy", font);
            sellButtons.emplace_back(sf::Vector2f(60, 30), sf::Vector2f(470, 50 + i * 40), "Sell", font);
        }

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window.close();
                }
            }
            else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                    std::cout << "Left mouse button pressed at: "
                              << mouseButtonPressed->position.x << ", "
                              << mouseButtonPressed->position.y << std::endl;

                    // mouse button click support (e.g. buy, sell)
                    sf::Vector2i mousePos = mouseButtonPressed->position;

                    for (size_t i = 0; i < companies.size(); ++i) {
                        if (buyButtons[i].isClicked(mousePos)) {
                            TransactionManager::buyStock(user, &companies[i], 1);
                        }
                        if (sellButtons[i].isClicked(mousePos)) {
                            TransactionManager::sellStock(user, &companies[i], 1);
                        }
                    }
                }
            }
        }

        if (priceUpdateClock.getElapsedTime().asSeconds() > 2.0f) {
            for (auto& company : companies) {
                company.updatePrice();
                company.updateTrend();
            }
        priceUpdateClock.restart();
        }

        window.clear(sf::Color::Black);

        // draw avaliable companies
        for (size_t i = 0; i < companies.size(); ++i) {
            const Company& comp = companies[i];

            // the direction of change
            std::string arrow = "(=)"; // default without change
            sf::Color color = sf::Color::White;

               if (comp.didPriceIncrease()) {
                    arrow = "(+)";
                    color = sf::Color::Green;
                } else if (comp.didPriceDecrease()) {
                    arrow = "(-)";
                    color = sf::Color::Red;
                }

            // create caption
            sf::String companiesString = comp.getName() + " " + formatTo2DecimalString(comp.getStockPrice()) + " PLN" + " " + arrow;
            sf::Text companiesText(font, companiesString, 20);
            
            companiesText.setFillColor(color);

            // set position
            companiesText.setPosition(sf::Vector2f(50.0f, 50.0f + i * 40.0f));
            window.draw(companiesText); 
        }

        for (auto& btn : buyButtons) btn.draw(window);
        for (auto& btn : sellButtons) btn.draw(window);

        // draw user info

        sf::String userString = "Hi " + user.getName() + "\n" + "Balance: " + formatTo2DecimalString(user.getBalance());
        sf::Text userText(font, userString , 20);
        userText.setPosition(sf::Vector2f(550.0f, 40.0f));
        window.draw(userText);

        //draw portfolio
        sf::String portfolioString = "Your shares: \n" + user.getPortfolio().getPortfolio();
        sf::Text portfolioText(font, portfolioString , 20);
        portfolioText.setPosition(sf::Vector2f(550.0f, 100.0f));
        window.draw(portfolioText);
        window.display();
        
        
    }
        return 0;
}

