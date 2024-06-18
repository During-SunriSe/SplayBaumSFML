#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;

    Button(float x, float y, float width, float height, const std::string& label);

    void draw(sf::RenderWindow& window);
    bool isClicked(sf::Vector2i mousePos);
};

#endif // BUTTON_H
