#ifndef ENEMY_GAME_OBJECT_H
#define ENEMY_GAME_OBJECT_H

#include "game_object.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include "timer.h"

class PlayerGameObject;

class EnemyGameObject : public GameObject {
    private:
        sf::Vector2f position_;
        float angle_ ;
        float speed_ ;
        sf::CircleShape circle_;
        int color_pos_;
        sf::Texture enemy_texture_;
        sf::Sprite enemy_sprite_;
        sf::Clock animationClock_;
        sf::IntRect frameRect_;
        sf::Vector2f velocity_;
        Timer timer_;
        float frameDuration_ = 0.15f;
        int curFrame = 0;
        int totFrames = 8;

    public:
        void draw(sf::RenderTarget &target);
        EnemyGameObject();
        ~EnemyGameObject();
        EnemyGameObject(float angle, float speed, int i);
        void update(float deltaTime, PlayerGameObject &player);
        void setEnemyPosition(float new_x, float new_y);
        sf::Vector2f getPosition();
        void createNewRandomPosition();
        sf::CircleShape getCircle() { return circle_; }
        sf::Texture getTexture() { return enemy_texture_; }
        sf::Sprite getSprite() { return enemy_sprite_; }
        sf::Vector2f getVelocity() { return velocity_; }
        void setVelocity(sf::Vector2f newVelocity) { velocity_ = newVelocity; }
        sf::Sprite getEnemySprite() { return enemy_sprite_; }

};

#endif