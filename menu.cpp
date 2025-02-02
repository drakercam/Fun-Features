#include "menu.h"

Menu::Menu(float width, float height, int charSize, int offset, std::vector<sf::Text>& buttons, std::vector<std::string>& names)
    : width_(width), height_(height), characterSize_(charSize), buttons_(buttons), names_(names),
      buttonHeightOffset_(offset), selectedItemIndex_(0), state_(false), active_(true) {

    if (!font_.loadFromFile("textures/ARCADECLASSIC.TTF")) {
        std::cerr << "Unable to load font for menu" << std::endl;
    }

    // Create the background shape
    background_.setSize(sf::Vector2f(width_, height_));
    background_.setFillColor(sf::Color(0, 0, 0, 150)); // semi-transparent menu

    // Create buttons
    createButtons(buttonHeightOffset_);
}

Menu::Menu() 
    : width_(0), height_(0), characterSize_(0), buttonHeightOffset_(0), selectedItemIndex_(0), state_(false), active_(false) {
    // Default constructor can initialize with default values if necessary
}

void Menu::draw(sf::RenderTarget& target) {
    target.draw(background_);
    for (const auto& button : buttons_) {
        target.draw(button);
    }
}

void Menu::moveUpSelection() {
    if (selectedItemIndex_ > 0) {
        --selectedItemIndex_;
    }
}

void Menu::moveDownSelection() {
    if (selectedItemIndex_ < buttons_.size() - 1) {
        ++selectedItemIndex_;
    }
}

int Menu::getPressedMenuItem() const {
    return selectedItemIndex_;
}

void Menu::update() {
    for (size_t i = 0; i < buttons_.size(); ++i) {
        if (i == selectedItemIndex_) {
            buttons_[i].setFillColor(sf::Color::Red);
        } else {
            buttons_[i].setFillColor(sf::Color::White);
        }
    }
}

void Menu::createButtons(int heightOffset) {
    int initHeightOffset = heightOffset;

    for (size_t i = 0; i < buttons_.size(); ++i) {
        buttons_[i].setFont(font_);
        buttons_[i].setString(names_[i]);
        buttons_[i].setCharacterSize(characterSize_);
        buttons_[i].setFillColor(sf::Color::White);
        buttons_[i].setPosition(width_ / 2 - 80, height_ / 2 - initHeightOffset);
        initHeightOffset -= 30;
    }
}

void Menu::handleMenuInput(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (getState()) {
            switch (event.key.code) {
                case sf::Keyboard::Up:
                    moveUpSelection();
                    break;
                case sf::Keyboard::Down:
                    moveDownSelection();
                    break;
                case sf::Keyboard::Enter:
                    switch (getPressedMenuItem()) {
                        case 0: // Resume
                            setState(false);
                            break;
                        case 1:
                            // Placeholder for settings menu logic in future
                            break;
                        case 2: // Quit
                            window.close();
                            break;
                        default:
                            break;
                    }
                    break;
            }
        }

        if (event.key.code == sf::Keyboard::Escape) {
            setState(!getState());
        }
    }
}
