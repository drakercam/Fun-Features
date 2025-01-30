#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

class Menu {
    private:
        float width_;
        float height_;
        sf::Font font_;
        std::vector<sf::Text> buttons_;// resume, quit and settings
        sf::RectangleShape background_;
        int selectedItemIndex_;

    public:
        Menu();
        Menu(float width, float height);
        void draw(sf::RenderTarget &target);
        void moveUpSelection();
        void moveDownSelection();
        int getPressedMenuItem();
        void createButtons();
        void update();
        
};

#endif