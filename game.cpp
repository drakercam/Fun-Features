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

void Game::toSpawnEnemy() {
    static int i = 0;
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

    bool toSpawn = enemySpawnTimer_->Finished();

    if (toSpawn) {
        std::vector<std::string> enemyNames = {"Anakin", "Obi-Wan", "Yoda", "Mace", "Yaddle", "Rex", "Ezra", "Maul", "Vader", "Starkiller"};

        // create as many enemies as needed
        enemies_.push_back(new EnemyGameObject(0.0, 100.0, enemyNames[i], i));

        // O(n) Time complexity solition to recalculate different enemy positions
        std::unordered_map<sf::Vector2i, int, Vector2iHash, Vector2iEqual> positionMap;
        for (int i = 0; i < enemies_.size(); ++i) {
            sf::Vector2i pos = enemies_[i]->getPosition();
            if (positionMap.find(pos) != positionMap.end()) {
                // position already exists, calc new position
                enemies_[i]->createNewRandomPosition();
            }
        }

        enemySpawnTimer_->Reset();
        enemySpawnTimer_->Start(8.0f); // spawn a new enemy every 8 seconds
        ++i;
    }
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
                window_.setMouseCursorVisible(false);
            }

            handleMenuInput(event); // moved into a helper function for better code readabilty
        }

        update();

        window_.clear();

        window_.draw(background_sprite_);

        if (getIsPaused()) {
            if (pauseMenu_) {
                pauseMenu_->update();
                pauseMenu_->draw(window_);
            }
        }

        else {
            for (int i = 0; i < enemies_.size(); ++i) {
                enemies_[i]->draw(window_);
            }

            player->draw(window_);
        }

        window_.display();
    }

    setIsRunning(false);
}

sf::Vector2u Game::getScreenResolution() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    return sf::Vector2u(desktop.width, desktop.height);
}

void Game::update() {
    if (!(enemies_.size() >= 10)) { // only allow 10 enemies for now
        toSpawnEnemy();
    }

    for (int i = 0; i < enemies_.size(); ++i) {
        EnemyGameObject* current_enemy = enemies_[i];
        sf::Vector2i difference = current_enemy->getPosition() - player->getPosition();

        float distance = std::sqrt(difference.x * difference.x + difference.y * difference.y);

        if (distance < 94.0f) {
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

void Game::handleMenuInput(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (getIsPaused()) {
            if (event.key.code == sf::Keyboard::Up) {
                pauseMenu_->moveUpSelection();
            }

            if (event.key.code == sf::Keyboard::Down) {
                pauseMenu_->moveDownSelection();
            }

            if (event.key.code == sf::Keyboard::Enter) {
                switch (pauseMenu_->getPressedMenuItem()) {
                    case 0: // Resume
                        setIsPaused(false);
                        break;
                    case 1:
                        // to add a new separate menu for settings later on
                        break;
                    
                    case 2: // Quit
                        window_.close();
                        break;
                }
            }
        }

        if (event.key.code == sf::Keyboard::Escape) {
            setIsPaused(!getIsPaused());
        }
    }
}

// Set up the game world (scene, game objects, etc.)
void Game::SetupGameWorld(void) {
    if (!background_.loadFromFile("textures/new_background.png")) {
        std::cerr << "Failed to load background image!" << std::endl;
    }

    background_sprite_.setTexture(background_);

    player = new PlayerGameObject(100.0, 200.0, 0.0, 100.0);

    enemySpawnTimer_ = new Timer();

    enemySpawnTimer_->Start(8.0f);

    // set up the pause menu
    pauseMenu_ = new Menu(window_.getSize().x, window_.getSize().y);
    setIsPaused(false);
}

// Destroy the game world
void Game::DestroyGameWorld(void) {
    for (int i = 0; i < enemies_.size(); ++i) {
        delete enemies_[i];
    }

    delete player;
    delete enemySpawnTimer_;
    delete pauseMenu_;
}