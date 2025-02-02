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
    struct Vector2fHash {
        std::size_t operator()(const sf::Vector2f& v) const {
            return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
        }
    };

    // Custom equality operator for sf::Vector2i
    struct Vector2fEqual {
        bool operator()(const sf::Vector2f& lhs, const sf::Vector2f& rhs) const {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }
    };

    bool toSpawn = enemySpawnTimer_->Finished();

    if (toSpawn) {

        // create as many enemies as needed
        enemies_.push_back(new EnemyGameObject(0.0, 100.0, i));

        // O(n) Time complexity solition to recalculate different enemy positions
        std::unordered_map<sf::Vector2f, int, Vector2fHash, Vector2fEqual> positionMap;
        for (int i = 0; i < enemies_.size(); ++i) {
            sf::Vector2f pos = enemies_[i]->getPosition();
            if (positionMap.find(pos) != positionMap.end()) {
                // position already exists, calc new position
                enemies_[i]->createNewRandomPosition();
                pos = enemies_[i]->getPosition();
            }

            positionMap[pos] = i;
        }

        enemySpawnTimer_->Reset();
        enemySpawnTimer_->Start(2.0f); // spawn a new enemy every 8 seconds
        ++i;
    }
}

void Game::mainLoop() {                // draw the game window and detect events
    setIsGameStart(true);
    
    while (window_.isOpen()) {
        startGameClock();
 
        sf::Event event;
        while (window_.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { window_.close(); }

            if (getIsGameStart()) {
                startMenu_->handleMenuInput(event, window_);
            } else {
                pauseMenu_->handleMenuInput(event, window_);
            }
        }

        update();

        window_.clear();

        window_.draw(background_sprite_);

        if (startMenu_->getState()) {

            if (startMenu_ && startMenu_->getActive()) {
                startMenu_->update();
                startMenu_->draw(window_);
            }

        }  else {

            setIsGameStart(false);
            startMenu_->setActive(false); // should prevent the startMenu from being opened after game starts

            if (pauseMenu_->getState()) {
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
                debugDrawBounds(window_); // show collision bounds for debugging purposes
            }
        }

        window_.display();
    }

    setIsRunning(false);
}

sf::Vector2u Game::getScreenResolution() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    return sf::Vector2u(desktop.width, desktop.height);
}

void Game::debugDrawBounds(sf::RenderTarget& target) {
    // Draw bounding boxes for bullets
    for (Bullet* bullet : player->getBullets()) {
        sf::FloatRect bulletBounds = bullet->getBulletSprite().getGlobalBounds();
        sf::RectangleShape bulletBox(sf::Vector2f(bulletBounds.width, bulletBounds.height));
        bulletBox.setPosition(bulletBounds.left, bulletBounds.top);
        bulletBox.setFillColor(sf::Color::Transparent);
        bulletBox.setOutlineColor(sf::Color::Red);  // Red for bullets
        bulletBox.setOutlineThickness(1.5f);
        target.draw(bulletBox);
    }

    // Draw bounding boxes for enemies
    for (EnemyGameObject* enemy : enemies_) {
        sf::FloatRect enemyBounds;
        enemyBounds.width = enemy->getSprite().getGlobalBounds().width - 36.0f;
        enemyBounds.height = enemy->getSprite().getGlobalBounds().height - 36.0f;
        sf::RectangleShape enemyBox(sf::Vector2f(enemyBounds.width, enemyBounds.height));
        enemyBox.setPosition(enemy->getPosition().x, enemy->getPosition().y);
        enemyBox.setOrigin(enemy->getCircle().getRadius(), enemy->getCircle().getRadius());
        enemyBox.setFillColor(sf::Color::Transparent);
        enemyBox.setOutlineColor(sf::Color::Green);  // Green for enemies
        enemyBox.setOutlineThickness(2.0f);
        target.draw(enemyBox);
    }
}

void Game::update() {
    player->update(window_, deltaTime_);

    for (int i = 0; i < enemies_.size(); ++i) {
        enemies_[i]->update(deltaTime_, *player);
    }

    toSpawnEnemy();

    collisionHandling();
}

void Game::setIsGameStart(bool isStart) {
    isStart_ = isStart;
}

bool Game::getIsGameStart() {
    return isStart_;
}

void Game::setIsRunning(bool change) {
    isRunning_ = change;
}

bool Game::getIsRunning() {
    return isRunning_;
}

void Game::collisionHandling() {
    for (int i = 0; i < enemies_.size(); ++i) {
        EnemyGameObject* current_enemy = enemies_[i];
        sf::Vector2f differencePE = current_enemy->getPosition() - player->getPosition();

        float distancePE = std::sqrt(differencePE.x * differencePE.x + differencePE.y * differencePE.y);

        if (distancePE < 52.0f) {
            std::cout << "Colliding with enemy object " << i << std::endl;
        }

        for (int j = 0; j < player->getBullets().size(); ++j) {

            Bullet* bullet = player->getBullets()[j];

            bulletBounds = bullet->getBulletSprite().getGlobalBounds();
            enemyBounds = current_enemy->getSprite().getGlobalBounds();
            // Set enemyBounds to match enemyBox exactly
            enemyBounds.left = current_enemy->getPosition().x;
            enemyBounds.top = current_enemy->getPosition().y;
            enemyBounds.width -= 36.0f;
            enemyBounds.height -= 36.0f;

            // // some sort of memory bug here
            if (bulletBounds.intersects(enemyBounds)) {
                std::cout << "Bullet " << j << " hit enemy " << j << std::endl;

                std::cout << "Deleted bullet " << j << ". Will free bullets_ vector later" << std::endl;

                enemies_.erase(enemies_.begin() + i);
                delete current_enemy;
            }
        }
    }
}

// Set up the game world (scene, game objects, etc.)
void Game::SetupGameWorld(void) {
    if (!background_.loadFromFile("textures/space_background.png")) {
        std::cerr << "Failed to load background image!" << std::endl;
    }

    // if (!laserSound_.openFromFile("textures/mixkit-laser-cannon-shot-1678.wav")) {
    //     std::cerr << "Unable to load laser shot sounds" << std::endl;
    // }

    background_sprite_.setTexture(background_);

    // scale the background to the window size
    sf::Vector2u textureSize = background_.getSize();
    sf::Vector2u windowSize = window_.getSize();
    float scaleX = windowSize.x / textureSize.x;
    float scaleY = windowSize.y / textureSize.y;

    background_sprite_.setScale(scaleX, scaleY);

    // if (!gameMusic_.openFromFile("textures/meet-the-princess.wav")) {
    //     std::cerr << "Error loading game music file!" << std::endl;
    // }

    // if (!levelStart_.openFromFile("textures/start-level.wav")) {
    //     std::cerr << "Error loading level start sound" << std::endl;
    // }

    player = new PlayerGameObject(500.0f, 0.0f, 0.0, 500.0);

    enemySpawnTimer_ = new Timer();

    enemySpawnTimer_->Start(2.0f);

    sf::Text quitButton;
    sf::Text startButton;
    std::vector<sf::Text> startMenuButtons = {startButton, quitButton};
    std::vector<std::string> startMenuNames = {"Start", "Quit"};

    startMenu_ = new Menu(window_.getSize().x, window_.getSize().y, 30, 60, startMenuButtons, startMenuNames);
    startMenu_->setState(true);
    
    sf::Text quitButton2;
    sf::Text pauseButton;
    sf::Text settingsButton;

    std::vector<sf::Text> pauseMenuButtons = {pauseButton, settingsButton, quitButton2};
    std::vector<std::string> pauseMenuNames = {"Resume", "Settings", "Quit"};

    // set up the pause menu
    pauseMenu_ = new Menu(window_.getSize().x, window_.getSize().y, 30, 60, pauseMenuButtons, pauseMenuNames);
    pauseMenu_->setState(false);

    // gameMusic_.setLoop(true);
    // gameMusic_.setVolume(10.0f);
    // gameMusic_.play();
}

// Destroy the game world
void Game::DestroyGameWorld(void) {
    delete player;
    delete enemySpawnTimer_;
    delete startMenu_;
    delete pauseMenu_;
}