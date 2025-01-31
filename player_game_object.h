#ifndef PLAYER_GAME_OBJECT_H
#define PLAYER_GAME_OBJECT_H

#include "game_object.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

class PlayerGameObject : public GameObject {
    private:
        sf::Vector2i position_;
        float angle_ ;
        float speed_ ;
        sf::CircleShape circle_;
        sf::Vector2i circlePosition_;
        sf::Texture player_texture_;
        sf::Sprite player_sprite_;
        sf::Clock animationClock_;
        sf::IntRect frameRect_;
        float frameDuration_ = 0.15f;
        int curFrame = 0;
        int totFrames = 4;

    public:
        void draw(sf::RenderTarget &target);
        PlayerGameObject();
        ~PlayerGameObject();
        PlayerGameObject(float x, float y, float angle, float speed);
        void update(float deltaTime);
        void setPlayerPosition(float x, float y);
        sf::Vector2i getPosition();
        sf::CircleShape getCirclePosition() { return circle_; }
        sf::Texture getTexture() { return player_texture_; }
        sf::Sprite getSprite() { return player_sprite_; }

};

#endif