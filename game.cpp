#include "game.h"
#include <unordered_map>
#include <memory>
#include <cmath>
#include <iostream>

Game::Game() 
 : window_(sf::VideoMode(1280.0f, 720.0f), "Game Dev Project"),
   isRunning_(true), 
   isStart_(false), 
   isPaused_(false),
   player(std::make_unique<PlayerGameObject>(500.0f, 0.0f, 0.0, 500.0)),
   enemySpawnTimer_(std::make_unique<Timer>())
{
    setScreenSize();
    setWindowSize(1280.0f, 720.0f);
    setWindowPosition();
    window_.setPosition(windowPosition_);
    enemySpawnTimer_->Start(2.0f);  // Start the timer for enemy spawn.
    SetupGameWorld();
}

Game::Game(float window_x, float window_y) 
 : window_(sf::VideoMode(window_x, window_y), "Game Dev Project"),
   isRunning_(true), 
   isStart_(false), 
   isPaused_(false),
   player(std::make_unique<PlayerGameObject>(500.0f, 0.0f, 0.0, 500.0)),
   enemySpawnTimer_(std::make_unique<Timer>())
{
    setScreenSize();
    setWindowSize(window_x, window_y);
    setWindowPosition();
    window_.setPosition(windowPosition_);
    enemySpawnTimer_->Start(2.0f);
    SetupGameWorld();
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

// Game::getIsRunning
bool Game::getIsRunning() {
    return isRunning_;
}

// Game::getScreenResolution
sf::Vector2u Game::getScreenResolution() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    return sf::Vector2u(desktop.width, desktop.height);
}

// Game::setIsGameStart
void Game::setIsGameStart(bool isStart) {
    isStart_ = isStart;
}

// Game::getIsGameStart
bool Game::getIsGameStart() {
    return isStart_;
}

// Game::setIsRunning
void Game::setIsRunning(bool change) {
    isRunning_ = change;
}


void Game::startGameClock() {
    deltaTime_ = gameClock_.restart().asSeconds();
}

void Game::toSpawnEnemy() {
    // Custom hash function for sf::Vector2f
    struct Vector2fHash {
        std::size_t operator()(const sf::Vector2f& v) const {
            // Combining x and y values to generate a unique hash for sf::Vector2f
            return std::hash<float>()(v.x) ^ (std::hash<float>()(v.y) << 1); 
        }
    };

    // Custom equality operator for sf::Vector2f (this is often unnecessary if you use the default one)
    struct Vector2fEqual {
        bool operator()(const sf::Vector2f& lhs, const sf::Vector2f& rhs) const {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }
    };

    bool toSpawn = enemySpawnTimer_->Finished();

    if (toSpawn) {
        enemies_.push_back(std::make_unique<EnemyGameObject>(0.0, 100.0));

        // O(n) Time complexity solution to recalculate different enemy positions
         std::unordered_map<sf::Vector2f, int, Vector2fHash, Vector2fEqual> positionMap;
        for (int i = 0; i < enemies_.size(); ++i) {
            sf::Vector2f pos = enemies_[i]->getPosition();
            if (positionMap.find(pos) != positionMap.end()) {
                enemies_[i]->createNewRandomPosition();
                pos = enemies_[i]->getPosition();
            }
            positionMap[pos] = i;
        }

        enemySpawnTimer_->Reset();
        enemySpawnTimer_->Start(2.0f); // spawn a new enemy every 2 seconds
    }
}

void Game::mainLoop() {
    setIsGameStart(true);

    while (window_.isOpen()) {
        startGameClock();

        sf::Event event;
        while (window_.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window_.close();
            }

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
            startMenu_->update();
            startMenu_->draw(window_);
        } else {

            drawUI(window_);

            setIsGameStart(false);
            startMenu_->setActive(false);

            if (pauseMenu_->getState()) {
                pauseMenu_->update();
                pauseMenu_->draw(window_);
            } else {
                for (auto& enemy : enemies_) {
                    enemy->draw(window_);
                }

                player->draw(window_);
                // debugDrawBounds(window_);  // Debugging collision bounds
            }
        }
        
        window_.display();
    }

    setIsRunning(false);
}

void Game::debugDrawBounds(sf::RenderTarget& target) {
    for (auto& bullet : player->getBullets()) {
        sf::FloatRect bulletBounds = bullet->getBulletSprite().getGlobalBounds();
        sf::RectangleShape bulletBox(sf::Vector2f(bulletBounds.width, bulletBounds.height));
        bulletBox.setPosition(bulletBounds.left, bulletBounds.top);
        bulletBox.setFillColor(sf::Color::Transparent);
        bulletBox.setOutlineColor(sf::Color::Red);  // Red for bullets
        bulletBox.setOutlineThickness(1.5f);
        target.draw(bulletBox);
    }

    for (auto& enemy : enemies_) {
        // Get the bounds for the enemy sprite
        sf::FloatRect enemyBounds = enemy->getSprite().getGlobalBounds();

        // Shrink the bounding box by a certain factor (e.g., 20% smaller)
        float shrinkFactor = 0.4f;  // Shrink to 80% of the original size
        float newWidth = enemyBounds.width * shrinkFactor;
        float newHeight = enemyBounds.height * shrinkFactor;

        // Create the new smaller bounding box
        sf::RectangleShape enemyBox(sf::Vector2f(newWidth, newHeight));

        // Center the bounding box on the enemy's position
        enemyBox.setPosition(
            enemy->getPosition().x - newWidth / 2, 
            enemy->getPosition().y - newHeight / 2
        );
        enemyBox.setFillColor(sf::Color::Transparent);
        enemyBox.setOutlineColor(sf::Color::Green);  // Green for enemies
        enemyBox.setOutlineThickness(2.0f);

        target.draw(enemyBox);
    }
}

void Game::setupUI() {
    // Load the font (replace with the path to your font file)
    if (!font_.loadFromFile("textures/ARCADECLASSIC.TTF")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    // Setup the score text
    scoreText_.setFont(font_);
    scoreText_.setCharacterSize(24);  // Font size
    scoreText_.setFillColor(sf::Color::White);  // Font color
    scoreText_.setPosition(10.0f, 10.0f);  // Position of the score text

    // Setup the player health text
    healthText_.setFont(font_);
    healthText_.setCharacterSize(24);  // Font size
    healthText_.setFillColor(sf::Color::Red);  // Font color
    healthText_.setPosition(10.0f, 40.0f);  // Position of the health text

    updateScore();
    updatePlayerHealth();
}

void Game::updateScore() {
    scoreText_.setString("Score      " + std::to_string(score_));
}

void Game::updatePlayerHealth() {
    healthText_.setString("Health    " + std::to_string(playerHealth_));
}

void Game::drawUI(sf::RenderWindow& window) {

    window.draw(scoreText_);
    window.draw(healthText_);
}

void Game::update() {
    player->update(window_, deltaTime_);

    for (auto& enemy : enemies_) {
        enemy->update(deltaTime_, *player);
    }

    toSpawnEnemy();
    collisionHandling();
}

void Game::collisionHandling() {
    for (int i = 0; i < enemies_.size(); ++i) {
        EnemyGameObject* current_enemy = enemies_[i].get();
        // Check if a bullet hit the enemy
        for (int j = 0; j < player->getBullets().size(); ++j) {
            Bullet* bullet = player->getBullets()[j];

            sf::FloatRect bulletBounds = bullet->getBulletSprite().getGlobalBounds();
            sf::FloatRect enemyBounds = current_enemy->getSprite().getGlobalBounds();

            if (bulletBounds.intersects(enemyBounds)) {
                // If the enemy is dead, increase score
                enemies_.erase(enemies_.begin() + i);
                score_ += 100;
                updateScore();  // Increase score by 100
                break;  // Exit the loop to avoid invalidating the iterator
            }

            // Check if the player collides with the enemy
            sf::FloatRect playerBounds = player->getSprite().getGlobalBounds();
            if (playerBounds.intersects(current_enemy->getSprite().getGlobalBounds())) {
                // Handle player health decrease due to collision with enemy
                playerHealth_ -= 10;
                updatePlayerHealth();  // Update the health UI (adjust according to your health system)
                break;                
                // You can add additional logic for when the player collides with an enemy.
            }
        }
    }
}


void Game::SetupGameWorld() {
    if (!background_.loadFromFile("textures/space_background.png")) {
        std::cerr << "Failed to load background image!" << std::endl;
    }

    background_sprite_.setTexture(background_);

    // scale the background to the window size
    sf::Vector2u textureSize = background_.getSize();
    sf::Vector2u windowSize = window_.getSize();
    float scaleX = windowSize.x / textureSize.x;
    float scaleY = windowSize.y / textureSize.y;

    background_sprite_.setScale(scaleX, scaleY);

    sf::Text quitButton;
    sf::Text startButton;
    std::vector<sf::Text> startMenuButtons = {startButton, quitButton};
    std::vector<std::string> startMenuNames = {"Start", "Quit"};
    startMenu_ = std::make_unique<Menu>(window_.getSize().x, window_.getSize().y, 30, 60, startMenuButtons, startMenuNames);
    startMenu_->setState(true);
    
    sf::Text quitButton2;
    sf::Text pauseButton;
    sf::Text settingsButton;

    std::vector<sf::Text> pauseMenuButtons = {pauseButton, settingsButton, quitButton2};
    std::vector<std::string> pauseMenuNames = {"Resume", "Settings", "Quit"};
    pauseMenu_ = std::make_unique<Menu>(window_.getSize().x, window_.getSize().y, 30, 60, pauseMenuButtons, pauseMenuNames);
    pauseMenu_->setState(false);

    playerHealth_ = 100;
    score_ = 0;

    setupUI();
}

void Game::DestroyGameWorld() {
    // Memory will be freed automatically when smart pointers go out of scope.
}
