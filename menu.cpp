#include "menu.h"

Menu::Menu(float width, float height) {
    if (!font_.loadFromFile("textures/ARCADECLASSIC.TTF")) {
        std::cerr << "Unable to load font for menu" << std::endl;
    }

    width_ = width;
    height_ = height;

    background_.setSize(sf::Vector2f(width_, height_));
    background_.setFillColor(sf::Color(0, 0, 0, 150)); // semi-transparent menu

    createButtons();

    selectedItemIndex_ = 0;
}

Menu::Menu() {
    // default constructor
}

void Menu::draw(sf::RenderTarget &target) {
    target.draw(background_);
    for (int i = 0; i < buttons_.size(); ++i) {
        target.draw(buttons_[i]);
    }
}

void Menu::moveUpSelection() {
    if (selectedItemIndex_ > 0) {
        selectedItemIndex_--;
    }
}

void Menu::moveDownSelection() {
    if (selectedItemIndex_ <  buttons_.size() - 1) {
        selectedItemIndex_++;
    }
}

int Menu::getPressedMenuItem() {
    return selectedItemIndex_;
}

void Menu::update() {
    for (int i = 0; i < buttons_.size(); ++i) {
        if (i == selectedItemIndex_) {
            buttons_[i].setFillColor(sf::Color::Red);
        }
        else {
            buttons_[i].setFillColor(sf::Color::White);
        }
    }
}

void Menu::createButtons() {
    sf::Text resumeButton;
    sf::Text settingsButton;
    sf::Text quitButton;

    buttons_.resize(3);

    resumeButton.setFont(font_);
    resumeButton.setString("Resume Game");
    resumeButton.setCharacterSize(30);
    resumeButton.setFillColor(sf::Color::White);
    resumeButton.setPosition(width_ / 2 - 80, height_ / 2 - 60);

    settingsButton.setFont(font_);
    settingsButton.setString("Settings");
    settingsButton.setCharacterSize(30);
    settingsButton.setFillColor(sf::Color::White);
    settingsButton.setPosition(width_ / 2 - 80, height_ / 2 - 30);

    quitButton.setFont(font_);
    quitButton.setString("Quit Game");
    quitButton.setCharacterSize(30);
    quitButton.setFillColor(sf::Color::White);
    quitButton.setPosition(width_ / 2 - 80, height_ / 2);

    buttons_[0] = resumeButton;
    buttons_[1] = settingsButton;
    buttons_[2] = quitButton;
}
