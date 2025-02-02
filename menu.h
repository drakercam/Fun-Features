#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include <string>
#include <iostream>

class Menu {
private:
    float width_;
    float height_;
    sf::Font font_;
    sf::RectangleShape background_;
    int selectedItemIndex_;
    int characterSize_;
    int buttonHeightOffset_;
    std::vector<sf::Text> buttons_;
    std::vector<std::string> names_;
    bool state_;
    bool active_;

public:
    // Constructors and Destructor
    Menu();
    Menu(float width, float height, int charSize, int offset, std::vector<sf::Text>& buttons, std::vector<std::string>& names);
    ~Menu() = default;

    // Menu interaction
    void moveUpSelection();
    void moveDownSelection();
    int getPressedMenuItem() const;

    // Button handling
    void createButtons(int heightOffset);
    void update();

    // Drawing
    void draw(sf::RenderTarget& target);

    // Input handling
    void handleMenuInput(sf::Event& event, sf::RenderWindow& window);

    // State control
    void setState(bool newState) { state_ = newState; }
    bool getState() const { return state_; }

    // Active state control
    void setActive(bool active) { active_ = active; }
    bool getActive() const { return active_; }
};

#endif
