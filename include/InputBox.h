#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <SFML/Graphics.hpp>
#include <string>

class InputBox {
public:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;
    std::string input;

    InputBox(float x, float y, float width, float height);

    void draw(sf::RenderWindow& window);
    void handleEvent(sf::Event event);
    std::string getInputValue() const;
    void clear();
};

#endif // INPUTBOX_H
