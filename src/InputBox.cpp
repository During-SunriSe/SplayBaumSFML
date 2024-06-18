#include "../include/InputBox.h"
#include <iostream>

InputBox::InputBox(float x, float y, float width, float height) {
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color::White);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1);

    if (!font.loadFromFile("C:/Windows/Fonts/tahoma.ttf")) {
        std::cerr << "Error loading font\n";
    }

    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x + 10, y + 10);
}

void InputBox::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

void InputBox::handleEvent(sf::Event event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b') {
            if (!input.empty()) {
                input.pop_back();
            }
        } else if (event.text.unicode < 128 && event.text.unicode != '\r') {
            input += static_cast<char>(event.text.unicode);
        }
        text.setString(input);
    }
}

std::string InputBox::getInputValue() const {
    return input;
}

void InputBox::clear() {
    input.clear();
    text.setString(input);
}
