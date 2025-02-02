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

class Game {   
    private:
        sf::Vector2u screenSize_;
        sf::Vector2u windowSize_;
        sf::Vector2i windowPosition_;
        float deltaTime_;
        bool isRunning_;
        PlayerGameObject* player;
        std::vector<EnemyGameObject*> enemies_;
        sf::Texture background_;
        sf::Sprite background_sprite_;
        // sf::Music gameMusic_;
        // sf::Music levelStart_;
        // sf::Music laserSound_;
        Timer* enemySpawnTimer_;
        Menu* pauseMenu_;
        Menu* startMenu_;
        bool isPaused_;
        bool isStart_;
        sf::FloatRect bulletBounds;
        sf::FloatRect enemyBounds;

    public:
        Game();
        ~Game();
        Game(float window_x, float window_y);
        void update();
        void setScreenSize();
        void setWindowSize(float x, float y);
        void setWindowPosition();
        void startGameClock();
        void setIsRunning(bool change);
        bool getIsRunning();
        void toSpawnEnemy();
        void setIsPaused(bool pause) { isPaused_ = pause; }
        bool getIsPaused() { return isPaused_; }
        void handleMenuInput(sf::Event &event);
        void setIsGameStart(bool isStart);
        bool getIsGameStart();
        void collisionHandling();
        void debugDrawBounds(sf::RenderTarget& target);

        void mainLoop();
        sf::Vector2u getScreenResolution();
        sf::RenderWindow window_;
        sf::Clock gameClock_;

        // Set up the game world (scene, game objects, etc.)
        void SetupGameWorld(void);

        // Destroy the game world
        void DestroyGameWorld(void);
};

#endif