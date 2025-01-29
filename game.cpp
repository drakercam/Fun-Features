#include "game.h"
#include <unordered_map>
#include <memory>
#include <cmath>
#include <iostream>

Game::Game() 
 : window_(sf::VideoMode(1280.0, 720.0), "Game Dev Project")
{
    setScreenSize();
    setWindowSize(1280.0, 720.0);
    setWindowPosition();
    window_.setPosition(windowPosition_);
    isRunning_ = true;
}

Game::Game(float window_x, float window_y) 
 : window_(sf::VideoMode(window_x, window_y), "Game Dev Project") 
{
    setScreenSize();
    setWindowSize(window_x, window_y);
    setWindowPosition();
    window_.setPosition(windowPosition_);
    isRunning_ = true;
}

Game::~Game() {
    DestroyGameWorld();
}

void Game::setScreenSize() {
    screenSize_ = getScreenResolution();
}

void Game::setWindowSize(float x, float y) {
    windowSize_ = sf::Vector2u(x, y);
}

void Game::setWindowPosition() {
    windowPosition_ = sf::Vector2i(
        static_cast<int>((screenSize_.x - windowSize_.x) / 2),
        static_cast<int>((screenSize_.y - windowSize_.y) / 2)
    );
}

void Game::startGameClock() {
    deltaTime_ = gameClock_.restart().asSeconds();
}

void Game::mainLoop() {                // draw the game window and detect events
    while (window_.isOpen()) {
        startGameClock();

        sf::Event event;
        while (window_.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { window_.close(); }

            if (event.type == sf::Event::MouseMoved) {
                // Get the mouse position relative to the window
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window_);

                // Set the position of the circle shape
                player->setPlayerPosition(
                    static_cast<float>(mousePosition.x), 
                    static_cast<float>(mousePosition.y)
                );
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window_.close();
        }

        update();

        window_.clear();

        window_.draw(background_sprite_);
        
        // enemies_[0]->draw(window_);

        for (int i = 0; i < enemies_.size(); ++i) {
            enemies_[i]->draw(window_); 
        }

        player->draw(window_);

        window_.display();
    }

    setIsRunning(false);
}

sf::Vector2u Game::getScreenResolution() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    return sf::Vector2u(desktop.width, desktop.height);
}

void Game::update() {
    for (int i = 0; i < enemies_.size(); ++i) {
        EnemyGameObject* current_enemy = enemies_[i];
        sf::Vector2i difference = current_enemy->getPosition() - player->getPosition();

        float distance = std::sqrt(difference.x * difference.x + difference.y * difference.y);

        if (distance < 20.0f) {
            std::cout << "Colliding with enemy object " << enemies_[i]->getName() << std::endl;
        }
    }
}

void Game::setIsRunning(bool change) {
    isRunning_ = change;
}

bool Game::getIsRunning() {
    return isRunning_;
}

// Set up the game world (scene, game objects, etc.)
void Game::SetupGameWorld(void) {
    // Custom hash function for sf::Vector2i
    struct Vector2iHash {
        std::size_t operator()(const sf::Vector2i& v) const {
            return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
        }
    };

    // Custom equality operator for sf::Vector2i
    struct Vector2iEqual {
        bool operator()(const sf::Vector2i& lhs, const sf::Vector2i& rhs) const {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }
    };

    if (!background_.loadFromFile("textures/new_background.png")) {
        std::cerr << "Failed to load background image!" << std::endl;
    }

    background_sprite_.setTexture(background_);

    player = new PlayerGameObject(100.0, 200.0, 0.0, 100.0);

    std::vector<std::string> enemyNames = {"Anakin", "Obi-Wan", "Yoda", "Mace", "Yaddle", "Rex", "Ezra", "Maul", "Vader", "Starkiller"};

    // create as many enemies as needed
    for (int i = 0; i < 10; ++i) {
        enemies_.push_back(new EnemyGameObject(0.0, 100.0, enemyNames[i], i));
    }

    // O(n) Time complexity solition to recalculate different enemy positions
    std::unordered_map<sf::Vector2i, int, Vector2iHash, Vector2iEqual> positionMap;
    for (int i = 0; i < enemies_.size(); ++i) {
        sf::Vector2i pos = enemies_[i]->getPosition();
        if (positionMap.find(pos) != positionMap.end()) {
            // position already exists, calc new position
            enemies_[i]->createNewRandomPosition();
        }
    }
}

// Destroy the game world
void Game::DestroyGameWorld(void) {
    for (int i = 0; i < enemies_.size(); ++i) {
        delete enemies_[i];
    }
    delete player;
}