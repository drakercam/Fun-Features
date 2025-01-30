#include "menu.h"

Menu::Menu(float width, float height, int charSize, int offset, std::vector<sf::Text> &buttons, std::vector<std::string> &names) {
    if (!font_.loadFromFile("textures/ARCADECLASSIC.TTF")) {
        std::cerr << "Unable to load font for menu" << std::endl;
    }

    width_ = width;
    height_ = height;
    characterSize_ = charSize;
    buttons_ = buttons;
    names_ = names;
    buttonHeightOffset_ = offset;
    active_ = true;
    state_ = false;

    background_.setSize(sf::Vector2f(width_, height_));
    background_.setFillColor(sf::Color(0, 0, 0, 150)); // semi-transparent menu

    createButtons(buttonHeightOffset_);

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

void Menu::createButtons(int heightOffset) {
    int initHeightOffset = heightOffset;

    for (int i = 0; i < buttons_.size(); ++i) {
        buttons_[i].setFont(font_);
        buttons_[i].setString(names_[i]);
        buttons_[i].setCharacterSize(characterSize_);
        buttons_[i].setFillColor(sf::Color::White);
        buttons_[i].setPosition(width_ / 2 - 80, height_ / 2 - initHeightOffset);
        initHeightOffset -= 30;
    }
}

void Menu::setActive(bool active) {
    active_ = active;
}

bool Menu::getActive() {
    return active_;
}

void Menu::handleMenuInput(sf::Event &event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed) {
        if (getState()) {
            if (event.key.code == sf::Keyboard::Up) {
                moveUpSelection();
            }

            if (event.key.code == sf::Keyboard::Down) {
                moveDownSelection();
            }

            if (event.key.code == sf::Keyboard::Enter) {
                switch (getPressedMenuItem()) {
                    case 0: // Resume
                        setState(false);
                        break;
                    case 1:
                        // to add a new separate menu for settings later on
                        break;
                    
                    case 2: // Quit
                        window.close();
                        break;
                }
            }
        }

        if (event.key.code == sf::Keyboard::Escape) {
            setState(!getState());
            std::cout << "Pause menu toggled. New state: " << getState() << std::endl;
        }
    }
}
