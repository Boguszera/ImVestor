#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include "Company.h"
#include "User.h"
#include "TransactionManager.h"
#include "Portfolio.h"
#include "ReportGenerator.h"
#include "gui/Button.hpp"
#include "SystemMessage.h"
#include <SFML/Graphics.hpp>
#include <variant>
#include <random>
#include <algorithm>
#include <cstdint>

std::string formatTo2DecimalString(double value) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << value;
    return oss.str();
}

int main(){
    sf::RenderWindow window(sf::VideoMode({800, 600}), "ImVestor");

    User user("Boguszera", 10000);

    Portfolio portfolio;

    Company companyA("Apple Inc.", "AAPL", "Technology", 150, 8000);
    Company companyB("Tesla Inc.", "TSLA", "Automotive", 350, 900);
    Company companyC("Orlen", "ORL", "Energy", 280, 10000);
    Company companyD("Allegro SA", "ALG", "E-commerce", 70, 15000);
    Company companyE("PKO BP", "PKO", "Finances", 90, 20000);
    Company companyF("Ubisoft", "UBI", "Gaming", 120, 12000);

    int selectedCompanyIndex = -1; // selected company index

    std::vector<Company> companies = { companyA, companyB, companyC, companyD, companyE, companyF};
    for (auto& company : companies) {
        company.initTrend();
    }

    std::vector<Button> buyButtons;
    std::vector<Button> sellButtons;
    sf::Clock priceUpdateClock;

    sf::Font font;
    if (!font.openFromFile("assets/LiberationSans-Regular.ttf")) {
        std::cout << "Failed to load the font!" << std::endl;
        return -1;
    }

    // draw buttons
    Button generateReportButton(sf::Vector2f(70, 27), sf::Vector2f(550, 320), "Report", font, ButtonType::Report);
        for (size_t i = 0; i < companies.size(); ++i) {
            float yPos = 50.0f + i * 40.0f;
            float buyX  = 280.0f;
            float sellX = 360.0f;
            buyButtons.emplace_back(sf::Vector2f(60, 30), sf::Vector2f(buyX, yPos), "Buy", font, ButtonType::Buy);
            sellButtons.emplace_back(sf::Vector2f(60, 30), sf::Vector2f(sellX, yPos), "Sell", font, ButtonType::Sell);
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

                    // mouse button click support
                    sf::Vector2i mousePos = mouseButtonPressed->position;
                    
                    // buy/sell
                    for (size_t i = 0; i < companies.size(); ++i) {
                        if (buyButtons[i].isClicked(mousePos)) {
                            TransactionManager::buyStock(user, &companies[i], 1);
                        }
                        if (sellButtons[i].isClicked(mousePos)) {
                            TransactionManager::sellStock(user, &companies[i], 1);
                        }
                    }

                    // company name
                    for (size_t i = 0; i < companies.size(); ++i) {
                        sf::FloatRect companyArea(sf::Vector2f(10.f, 50.f + i * 40.f), sf::Vector2f(240.f, 35.f));
                        if (companyArea.contains((sf::Vector2f)mousePos)) {
                            selectedCompanyIndex = static_cast<int>(i);
                        }
                    }

                    // report 
                    if (generateReportButton.isClicked(mousePos)) {
                        ReportGenerator::generateReport("transaction_report.csv");
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

        window.clear(sf::Color(18, 18, 30));

        // draw avaliable companies
        for (size_t i = 0; i < companies.size(); ++i) {
            // draw left section
                sf::RectangleShape background(sf::Vector2f(245.f, 35.f));
                background.setPosition(sf::Vector2f(10.f, 50.f + i * 40.f));
                background.setFillColor(sf::Color(25, 25, 40, 180)); 
                background.setOutlineColor(sf::Color(70, 70, 100));
                background.setOutlineThickness(1.f);
                window.draw(background);
            
            const Company& comp = companies[i];

            // the direction of change
            std::string arrow = "(=)"; // default without change
            sf::Color color = sf::Color(230, 230, 230);

               if (comp.didPriceIncrease()) {
                    arrow = "(+)";
                    color = sf::Color(0, 255, 160);
                } else if (comp.didPriceDecrease()) {
                    arrow = "(-)";
                    color = sf::Color(255, 80, 80);
                }

            // create caption
            sf::String companiesString = comp.getName() + " " + formatTo2DecimalString(comp.getStockPrice()) + " PLN" + " " + arrow;
            sf::Text companiesText(font, companiesString, 20);
            
            companiesText.setFillColor(color);

            // set position
            companiesText.setPosition(sf::Vector2f(20.0f, 50.0f + i * 40.0f));
            window.draw(companiesText); 
        }

        // hover on buttons
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        for (auto& btn : buyButtons) {
            btn.updateHover(mousePos);
        }
        for (auto& btn : sellButtons) {
            btn.updateHover(mousePos);
        }
        generateReportButton.updateHover(mousePos);

        for (auto& btn : buyButtons) btn.draw(window);
        for (auto& btn : sellButtons) btn.draw(window);
        generateReportButton.draw(window);

        // draw right section (userInfo and portfolio)
        sf::RectangleShape userInfoPanel(sf::Vector2f(240.f, 60.f));
        userInfoPanel.setPosition(sf::Vector2f(550.f, 30.f));
        userInfoPanel.setFillColor(sf::Color(30, 30, 50));
        userInfoPanel.setOutlineColor(sf::Color(80, 80, 110));
        userInfoPanel.setOutlineThickness(1.f);
        window.draw(userInfoPanel);
        sf::RectangleShape portfolioPanel(sf::Vector2f(240.f, 200.f));
        portfolioPanel.setPosition(sf::Vector2f(550.f, 110.f));
        portfolioPanel.setFillColor(sf::Color(30, 30, 50));
        portfolioPanel.setOutlineColor(sf::Color(80, 80, 110));
        portfolioPanel.setOutlineThickness(1.f);
        window.draw(portfolioPanel);

        // draw user info
        sf::String userString = "Hi " + user.getName() + "\n" + "Balance: " + formatTo2DecimalString(user.getBalance());
        sf::Text userText(font, userString , 20);
        userText.setPosition(sf::Vector2f(550.0f, 40.0f));
        window.draw(userText);

        // draw portfolio
        sf::String portfolioString = "Your shares: \n" + user.getPortfolio().getPortfolio();
        sf::Text portfolioText(font, portfolioString , 20);
        portfolioText.setPosition(sf::Vector2f(550.0f, 120.0f));
        window.draw(portfolioText);

        // draw chart
        if (selectedCompanyIndex >= 0) {
            const auto& history = companies[selectedCompanyIndex].getPriceHistory();
            if (history.size() < 2) continue;

            float maxPrice = *std::max_element(history.begin(), history.end());
            float minPrice = *std::min_element(history.begin(), history.end());

            float chartWidth = 500.f;
            float chartHeight = 150.f;
            float chartX = 50.f;
            float chartY = 400.f;

            // chart background 
            sf::RectangleShape chartBackground(sf::Vector2f(chartWidth, chartHeight));
            chartBackground.setPosition(sf::Vector2f(chartX, chartY));
            chartBackground.setFillColor(sf::Color(30, 30, 50));
            chartBackground.setOutlineThickness(1.f);
            chartBackground.setOutlineColor(sf::Color(70, 70, 100));
            window.draw(chartBackground);

            // horizontal grid
            for (int i = 1; i < 5; ++i) {
                float y = chartY + (i * chartHeight / 5.f);

                sf::Vertex line[2];
                line[0].position = sf::Vector2f(chartX, y);
                line[0].color = sf::Color(60, 60, 80);

                line[1].position = sf::Vector2f(chartX + chartWidth, y);
                line[1].color = sf::Color(60, 60, 80);

                window.draw(line, 2, sf::PrimitiveType::Lines);
            }

            // Y axis designations
            for (int i = 1; i < 5; ++i) {
                float y = chartY + (i * chartHeight / 5.f);
                float t = float(i) / 5.f;
                float value = maxPrice - t * (maxPrice - minPrice);  

                std::ostringstream ss;
                ss.precision(2);
                ss << std::fixed << value;

                sf::Text label(font, ss.str(), 14);
                label.setFillColor(sf::Color(200, 200, 200));
                label.setPosition(sf::Vector2f(chartX - 50.f, y - 10.f)); 
                window.draw(label);
            }

            // vertical grid
            for (int i = 1; i < 10; ++i) {
                float x = chartX + (i * chartWidth / 10.f);

                sf::Vertex line[2];
                line[0].position = sf::Vector2f(x, chartY);
                line[0].color = sf::Color(40, 40, 60);

                line[1].position = sf::Vector2f(x, chartY + chartHeight);
                line[1].color = sf::Color(40, 40, 60);

                window.draw(line, 2, sf::PrimitiveType::Lines);
            }

            // shadow under the line
            sf::VertexArray shadowLine(sf::PrimitiveType::LineStrip, history.size());
            for (size_t i = 0; i < history.size(); ++i) {
                float x = chartX + (float(i) / (history.size() - 1)) * chartWidth;
                float normalizedY = (history[i] - minPrice) / (maxPrice - minPrice + 0.001f);
                float y = chartY + chartHeight - normalizedY * chartHeight;

                shadowLine[i].position = sf::Vector2f(x, y + 2.f);
                shadowLine[i].color = sf::Color(0, 0, 0, 100);     
            }
            window.draw(shadowLine);

            // main line of the graph
            sf::VertexArray priceLine(sf::PrimitiveType::LineStrip, history.size());
            for (size_t i = 0; i < history.size(); ++i) {
                float x = chartX + (float(i) / (history.size() - 1)) * chartWidth;
                float normalizedY = (history[i] - minPrice) / (maxPrice - minPrice + 0.001f);
                float y = chartY + chartHeight - normalizedY * chartHeight;

                priceLine[i].position = sf::Vector2f(x, y);

                // Gradient: the farther away - green, closer - blue
                float t = float(i) / (history.size() - 1);
                uint8_t r = 0;
                uint8_t g = static_cast<uint8_t>(180 + 75 * t);
                uint8_t b = static_cast<uint8_t>(255 - 180 * t);

                priceLine[i].color = sf::Color(r, g, b, 220);
            }
            window.draw(priceLine);

            // dots on data points
            for (size_t i = 0; i < history.size(); ++i) {
                float x = chartX + (float(i) / (history.size() - 1)) * chartWidth;
                float normalizedY = (history[i] - minPrice) / (maxPrice - minPrice + 0.001f);
                float y = chartY + chartHeight - normalizedY * chartHeight;

                sf::CircleShape dot(2.f);
                dot.setFillColor(sf::Color(0, 255, 180));
                dot.setOutlineColor(sf::Color::White);
                dot.setOutlineThickness(1.f);
                dot.setOrigin(sf::Vector2f(2.f, 2.f)); // geometric center
                dot.setPosition(sf::Vector2f(x, y));
                window.draw(dot);
            }

            // dot at the end of the graph line
            float lastX = chartX + chartWidth;
            float lastY = chartY + chartHeight - ((history.back() - minPrice) / (maxPrice - minPrice + 0.001f)) * chartHeight;
            sf::CircleShape dot(4.f);
            dot.setFillColor(sf::Color(255, 220, 50));
            dot.setOrigin(sf::Vector2f(4.f, 4.f));
            dot.setPosition(sf::Vector2f(lastX, lastY));
            window.draw(dot);

            // final price label
            sf::Text label(font, "", 14);
            label.setFont(font);
            label.setCharacterSize(14);
            label.setFillColor(sf::Color(255, 220, 50));
            label.setString(formatTo2DecimalString(history.back()) + " PLN");
            label.setPosition(sf::Vector2f(lastX - 60.f, lastY - 20.f));
            window.draw(label);

            // chart title
            sf::Text title(font, "", 14);
            title.setFont(font);
            title.setCharacterSize(18);
            title.setFillColor(sf::Color::White);
            title.setString(companies[selectedCompanyIndex].getName() + " - Price Chart");
            title.setPosition(sf::Vector2f(chartX, chartY - 30.f));
            window.draw(title);
        }
        
        sf::Text messageText(font, "", 14);
        messageText.setFont(font);
        messageText.setCharacterSize(16);
        messageText.setFillColor(sf::Color::Yellow);
        messageText.setString(SystemMessage::get());
        messageText.setPosition(sf::Vector2f(20.f, 570.f)); // np. na dole ekranu

        if (!SystemMessage::get().empty()) {
            window.draw(messageText);
        }

        window.display();
    }
        return 0;
}

