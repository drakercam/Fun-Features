#ifndef GAME_H
#define GAME_H

#include "player_game_object.h"
#include "enemy_game_object.h"
#include "game_object.h"
#include "timer.h"
#include "menu.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <unordered_map>

class Game {
private:
    // Screen and window size information
    sf::Vector2u screenSize_;
    sf::Vector2u windowSize_;
    sf::Vector2i windowPosition_;

    // Game state and clock management
    float deltaTime_;
    bool isRunning_;
    bool isStart_;
    bool isPaused_;
    sf::Clock gameClock_;

    // Game objects
    std::unique_ptr<PlayerGameObject> player;
    std::vector<std::unique_ptr<EnemyGameObject>> enemies_;
    sf::Texture background_;
    sf::Sprite background_sprite_;

    // Menu system
    std::unique_ptr<Menu> startMenu_;
    std::unique_ptr<Menu> pauseMenu_;

    // Spawn timer
    std::unique_ptr<Timer> enemySpawnTimer_;

    // Collision bounds
    sf::FloatRect bulletBounds;
    sf::FloatRect enemyBounds;

    // UI related
    int score_;              // Player's score
    int playerHealth_;       // Player's health

    sf::Font font_;          // Font for rendering text
    sf::Text scoreText_;     // Text for displaying score
    sf::Text healthText_;    // Text for displaying player's health
    std::vector<sf::Text> enemyHealthText_; // Text for displaying enemy health

    // Helper methods
    void setScreenSize();
    void setWindowSize(float x, float y);
    void setWindowPosition();
    void startGameClock();
    void toSpawnEnemy();
    void collisionHandling();
    void debugDrawBounds(sf::RenderTarget& target);
    void setIsGameStart(bool isStart);
    bool getIsGameStart();

public:
    // Constructors and Destructor
    Game();
    ~Game();
    Game(float window_x, float window_y);

    // Game loop and update methods
    void update();
    void mainLoop();

    // UI elements
    void updateUI();
    void drawUI(sf::RenderWindow& window);
    void updateScore();
    void updatePlayerHealth();
    void updateEnemyHealth(int enemyIndex, int amount);
    void setupUI();

    // Game state and control methods
    void setIsRunning(bool change);
    bool getIsRunning();
    void setIsPaused(bool pause) { isPaused_ = pause; }
    bool getIsPaused() { return isPaused_; }

    // Screen resolution and window size methods
    sf::Vector2u getScreenResolution();

    // Set up and destroy the game world
    void SetupGameWorld(void);
    void DestroyGameWorld(void);

    // SFML window object
    sf::RenderWindow window_;
};

#endif
