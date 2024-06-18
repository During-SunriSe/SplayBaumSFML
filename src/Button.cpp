#include "../include/Button.h"
#include <iostream>

Button::Button(float x, float y, float width, float height, const std::string& label) {
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color::Blue);

    if (!font.loadFromFile("C:/Windows/Fonts/tahoma.ttf")) {
        std::cerr << "Error loading font\n";
    }

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(x + 10, y + 10);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

bool Button::isClicked(sf::Vector2i mousePos) {
    return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}
