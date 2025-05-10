#include <iostream>
#include "Company.h"
#include "User.h"
#include "TransactionManager.h"
#include "Portfolio.h"
#include <SFML/Graphics.hpp>
#include <vector>

int main(){
    sf::RenderWindow window(sf::VideoMode({800, 600}), "ImVestor");

    User user("Robert", 1000);

    Company companyA("Apple Inc.", "AAPL", "Technology", 150.0, 6543);
    Company companyB("Tesla Inc.", "TSLA", "Automotive", 700.0, 9935);
    Company companyC("Orlen", "ORL", "Energy", 300, 2222);

    std::vector<Company> companies = { companyA, companyB, companyC };

    sf::Font font;
    if (!font.openFromFile("assets/ARIAL.ttf")) {
        std::cout << "Nie udało się załadować czcionki!" << std::endl;
        return -1;
    }

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::White);

        // draw avaliable companies
        for (size_t i = 0; i < companies.size(); ++i) {
            // create caption
            sf::String companiesString = companies[i].getName() + ": " + std::to_string(companies[i].getStockPrice()) + " PLN";
            sf::Text companiesText(font, companiesString, 20);

            // Ustawienie pozycji tekstu, aby nie były nałożone
            companiesText.setPosition(sf::Vector2f(50.0f, 50.0f + i * 40.0f));
            window.draw(companiesText);  // Rysowanie tekstu
        }

        // draw user info

        /*
        sf::String userString = user.printPortfolio()
        sf::Text userText(font, userString , 20);
        userText.setPosition(50, 350);
        window.draw(userText);

        window.display();
        */
    }

    /*
    
    Company test("Test", "TST", "test category", 127.25, 15000);

    test.printInfo();

    Company apple("Apple Inc.", "AAPL", "Technology", 150.0, 6543);
    Company tesla("Tesla Inc.", "TSLA", "Automotive", 700.0, 9935);

    User user("Jan Kowalski", 10000.0);

    user.printPortfolio();

    TransactionManager::buyStock(user, &apple, 50);
    TransactionManager::buyStock(user, &tesla, 10);

    user.printPortfolio();

    TransactionManager::sellStock(user, &apple, 20);

    user.printPortfolio();
    */
    return 0;
}

