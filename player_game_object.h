#ifndef PLAYER_GAME_OBJECT_H
#define PLAYER_GAME_OBJECT_H

#include "game_object.h"
#include "timer.h"
#include "bullet.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <vector>
#include <string>

class PlayerGameObject : public GameObject {
private:
    sf::Vector2f position_;
    float angle_;
    float speed_;
    Timer shootingTimer;
    std::string direction_;
    sf::CircleShape circle_;
    sf::Vector2f circlePosition_;
    sf::Texture player_texture_;
    sf::Sprite player_sprite_;
    sf::Clock animationClock_;
    sf::IntRect frameRect_;
    std::vector<Bullet*> bullets_;
    
    // Animation frame control
    float frameDuration_ = 0.15f;
    int curFrame = 0;
    int totFrames = 4;

public:
    // Constructors and Destructor
    PlayerGameObject();
    PlayerGameObject(float x, float y, float angle, float speed);
    ~PlayerGameObject();

    // Update functions
    void updateAnimation();
    void update(sf::RenderTarget &target, float deltaTime);
    
    // Player setup and input
    void setupPlayer();
    void keyboardInput(float deltaTime);
    void rotatePlayer();

    // Bullet management
    void shoot();
    void removeBullets(float deltaTime, sf::RenderTarget &target);
    
    // Position and accessor methods
    void setPlayerPosition(float x, float y);
    sf::Vector2f getPosition() const;
    const sf::CircleShape& getCirclePosition() const { return circle_; }
    const sf::Texture& getTexture() const { return player_texture_; }
    const sf::Sprite& getSprite() const { return player_sprite_; }
    const std::vector<Bullet*>& getBullets() const { return bullets_; }

    // Drawing method
    void draw(sf::RenderTarget &target);
};

#endif