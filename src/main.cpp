#include <SFML/Graphics.hpp>
#include "../include/SplayTree.h"
#include "../include/Button.h"
#include "../include/InputBox.h"
#include <map>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;
const int RADIUS = 20;
const int LEVEL_HEIGHT = 80;

sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t) {
    return (1 - t) * start + t * end;
}

void visualizeNodes(TreeNode* root, sf::RenderWindow &window, int x, int y, int offset, std::map<std::string, sf::Vector2f>& positions, float t) {
    if (root) {
        sf::Vector2f targetPos(x, y);
        sf::Vector2f startPos = positions[root->key];
        sf::Vector2f currentPos = lerp(startPos, targetPos, t);
        positions[root->key] = currentPos;  // Update position map

        sf::CircleShape nodeShape(RADIUS);
        nodeShape.setFillColor(sf::Color::Green);
        nodeShape.setPosition(currentPos.x - RADIUS, currentPos.y - RADIUS);

        sf::Text text;
        sf::Font font;
        if (!font.loadFromFile("C:/Windows/Fonts/tahoma.ttf")) {
            std::cerr << "Error loading font\n";
        }
        text.setFont(font);
        text.setString(root->key);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        text.setPosition(currentPos.x - RADIUS / 2, currentPos.y - RADIUS / 2);

        window.draw(nodeShape);
        window.draw(text);

        visualizeNodes(root->left, window, x - offset, y + LEVEL_HEIGHT, offset / 2, positions, t);
        visualizeNodes(root->right, window, x + offset, y + LEVEL_HEIGHT, offset / 2, positions, t);
    }
}

void visualizeEdges(TreeNode* root, sf::RenderWindow &window, int x, int y, int offset, std::map<std::string, sf::Vector2f>& positions, float t) {
    if (root) {
        sf::Vector2f targetPos(x, y);
        sf::Vector2f startPos = positions[root->key];
        sf::Vector2f currentPos = lerp(startPos, targetPos, t);

        if (root->left) {
            sf::Vector2f leftTargetPos(x - offset, y + LEVEL_HEIGHT);
            sf::Vector2f leftStartPos = positions[root->left->key];
            sf::Vector2f leftCurrentPos = lerp(leftStartPos, leftTargetPos, t);
            sf::Vertex line[] = {
                    sf::Vertex(currentPos, sf::Color::Black),
                    sf::Vertex(leftCurrentPos, sf::Color::Black)
            };
            window.draw(line, 2, sf::Lines);
            visualizeEdges(root->left, window, x - offset, y + LEVEL_HEIGHT, offset / 2, positions, t);
        }
        if (root->right) {
            sf::Vector2f rightTargetPos(x + offset, y + LEVEL_HEIGHT);
            sf::Vector2f rightStartPos = positions[root->right->key];
            sf::Vector2f rightCurrentPos = lerp(rightStartPos, rightTargetPos, t);
            sf::Vertex line[] = {
                    sf::Vertex(currentPos, sf::Color::Black),
                    sf::Vertex(rightCurrentPos, sf::Color::Black)
            };
            window.draw(line, 2, sf::Lines);
            visualizeEdges(root->right, window, x + offset, y + LEVEL_HEIGHT, offset / 2, positions, t);
        }
    }
}

void visualize(sf::RenderWindow &window, TreeNode* root, std::map<std::string, sf::Vector2f>& positions, float t) {
    visualizeEdges(root, window, WIDTH / 2, LEVEL_HEIGHT, WIDTH / 4, positions, t);
    visualizeNodes(root, window, WIDTH / 2, LEVEL_HEIGHT, WIDTH / 4, positions, t);
}

int main() {
    SplayTree tree;
    std::map<std::string, sf::Vector2f> positions;  // Store positions of nodes

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Splay Tree Visualization");
    window.setFramerateLimit(60);  // Set a higher frame rate for smoother animations

    Button addButton(10, 10, 100, 40, "Add");
    Button searchButton(120, 10, 100, 40, "Search");
    Button deleteButton(230, 10, 100, 40, "Delete");
    InputBox inputBox(340, 10, 100, 40);

    sf::Clock clock;
    float animationTime = 2.0f;  // Duration of animation in seconds
    float elapsedTime = 0;
    bool animating = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && !animating) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (addButton.isClicked(mousePos)) {
                    try {
                        std::string value = inputBox.getInputValue();
                        tree.insert(value);
                        positions[value] = sf::Vector2f(WIDTH / 2, HEIGHT / 2);  // Start animation from the center
                        inputBox.clear();
                        elapsedTime = 0;
                        animating = true;
                    } catch (...) {
                        std::cerr << "Invalid input\n";
                    }
                } else if (searchButton.isClicked(mousePos)) {
                    try {
                        std::string value = inputBox.getInputValue();
                        bool found = tree.find(value) != nullptr;
                        std::cout << (found ? "Found" : "Not Found") << std::endl;
                        inputBox.clear();
                        elapsedTime = 0;
                        animating = true;
                    } catch (...) {
                        std::cerr << "Invalid input\n";
                    }
                } else if (deleteButton.isClicked(mousePos)) {
                    try {
                        std::string value = inputBox.getInputValue();
                        tree.Delete(value);
                        inputBox.clear();
                        elapsedTime = 0;
                        animating = true;
                    } catch (...) {
                        std::cerr << "Invalid input\n";
                    }
                }
            }

            inputBox.handleEvent(event);
        }

        if (animating) {
            elapsedTime += clock.restart().asSeconds();
            if (elapsedTime > animationTime) {
                elapsedTime = animationTime;
                animating = false;
            }
        } else {
            clock.restart();
        }

        float t = elapsedTime / animationTime;

        window.clear(sf::Color::White);
        visualize(window, tree.getRoot(), positions, t);

        addButton.draw(window);
        searchButton.draw(window);
        deleteButton.draw(window);
        inputBox.draw(window);

        window.display();
    }

    return 0;
}
