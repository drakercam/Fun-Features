#ifndef ENEMY_GAME_OBJECT_H
#define ENEMY_GAME_OBJECT_H

#include "game_object.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <string>

class EnemyGameObject : public GameObject {
    private:
        sf::Vector2i position_;
        float angle_ ;
        float speed_ ;
        sf::CircleShape circle_;
        std::string name_;
        int color_pos_;
        sf::Texture enemy_texture_;
        sf::Sprite enemy_sprite_;
        sf::Clock animationClock_;
        sf::IntRect frameRect_;
        float frameDuration_ = 0.15f;
        int curFrame = 0;
        int totFrames = 8;

    public:
        void draw(sf::RenderTarget &target);
        EnemyGameObject();
        ~EnemyGameObject();
        EnemyGameObject(float angle, float speed, std::string name, int i);
        void update(float deltaTime);
        void setEnemyPosition(float new_x, float new_y);
        sf::Vector2i getPosition();
        void createNewRandomPosition();
        std::string getName() { return name_; }
        sf::CircleShape getCircle() { return circle_; }
        sf::Texture getTexture() { return enemy_texture_; }
        sf::Sprite getSprite() { return enemy_sprite_; }

};

#endif