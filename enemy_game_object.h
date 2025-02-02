#ifndef ENEMY_GAME_OBJECT_H
#define ENEMY_GAME_OBJECT_H

#include "game_object.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <string>
#include "timer.h"

class PlayerGameObject;

class EnemyGameObject : public GameObject {
private:
    sf::Vector2f position_;
    float angle_;
    float speed_;
    sf::CircleShape circle_;
    int color_pos_;
    sf::Texture enemy_texture_;
    sf::Sprite enemy_sprite_;
    sf::Clock animationClock_;
    sf::IntRect frameRect_;
    sf::Vector2f velocity_;
    Timer timer_;
    
    // Animation frame control
    float frameDuration_ = 0.15f;
    int curFrame = 0;
    int totFrames = 8;

public:
    // Constructor and Destructor
    EnemyGameObject();
    EnemyGameObject(float angle, float speed);
    ~EnemyGameObject();

    // Public methods for enemy behavior
    void seekPlayer(PlayerGameObject &player);
    void updateAnimation();
    void setUpTextures();
    void draw(sf::RenderTarget &target);
    void update(float deltaTime, PlayerGameObject &player);

    // Position and velocity management
    void setEnemyPosition(float new_x, float new_y);
    sf::Vector2f getPosition() const;
    void createNewRandomPosition();

    // Accessors
    sf::CircleShape getCircle() const { return circle_; }
    const sf::Texture& getTexture() const { return enemy_texture_; }
    const sf::Sprite& getSprite() const { return enemy_sprite_; }
    const sf::Vector2f& getVelocity() const { return velocity_; }
    void setVelocity(const sf::Vector2f& newVelocity) { velocity_ = newVelocity; }
    const sf::Sprite& getEnemySprite() const { return enemy_sprite_; }
};

#endif
