#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <SFML/Window/Event.hpp>

class Menu {
    private:
        float width_;
        float height_;
        sf::Font font_;
        sf::RectangleShape background_;
        int selectedItemIndex_;
        int characterSize_;
        int numButtons_;
        int buttonHeightOffset_;
        std::vector<sf::Text> buttons_;
        std::vector<std::string> names_;
        bool state_;
        bool active_;

    public:
        Menu();
        Menu(float width, float height, int charSize, int offset, std::vector<sf::Text> &buttons, std::vector<std::string> &names);
        void draw(sf::RenderTarget &target);
        void moveUpSelection();
        void moveDownSelection();
        int getPressedMenuItem();
        void createButtons(int heightOffset);
        void update();
        void handleMenuInput(sf::Event &event, sf::RenderWindow &window);
        void setState(bool newState) { state_ = newState; }
        bool getState() { return state_; }
        void setActive(bool active);
        bool getActive();
        
};

#endif