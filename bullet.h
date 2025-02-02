#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include "enemy_game_object.h"
#include <iostream>
#include  "timer.h"


class Bullet {
    private:
        sf::Clock animationClock_;
        sf::CircleShape shape_;
        std::string direction_;
        sf::Vector2f position_;
        sf::Texture bulletTexture_;
        sf::Sprite bulletSprite_;
        sf::IntRect frameRect_;
        sf::FloatRect bulletBounds;
        sf::FloatRect enemyBounds;
        Timer soundTimer_;
        float frameDuration_ = 0.15f;
        float soundDuration_ = 0.5f;
        int curFrame = 0;
        int totFrames = 4;

    public:

        Bullet(float x, float y, std::string direction) 
        : frameRect_(0, 0, 48, 32) {

            if (!bulletTexture_.loadFromFile("textures/spritesheet.png")) {
                std::cerr << "Error loading bullet texture" << std::endl;
            }

            position_.x = x;
            position_.y = y;

            bulletSprite_.setTexture(bulletTexture_);
            bulletSprite_.setTextureRect(frameRect_);

            shape_.setRadius(5.0f);
            shape_.setOrigin(shape_.getRadius(), shape_.getRadius());
            shape_.setPosition(x, y);
            shape_.setFillColor(sf::Color::Yellow);

            bulletSprite_.setOrigin(shape_.getRadius(), shape_.getRadius());
            direction_ = direction;

            if (direction_ == "left") {
                bulletSprite_.setPosition(x - 154.0f, y);
                bulletSprite_.setScale(-1.0f, 1.0f);
                shape_.setPosition(x - 170.0f, y + 12.0f);
            } 
            else if (direction_ == "right") {
                bulletSprite_.setPosition(x + 48.0f, y);
                bulletSprite_.setScale(1.0f, 1.0f);
                shape_.setPosition(x + 64.0f, y + 12.0f);
            }

        }

        void move(float deltaTime) {
            if (direction_ == "right") {
                bulletSprite_.move(400.0f * deltaTime, 0.0f);
                shape_.move(400.0f * deltaTime, 0.0f);
            }
            else if (direction_ == "left") {
                bulletSprite_.move(-400.0f * deltaTime, 0.0f);
                shape_.move(-400.0f * deltaTime, 0.0f);
            }
        }

        void animation() {
            if (animationClock_.getElapsedTime().asSeconds() >= frameDuration_) {
                curFrame = (curFrame + 1) % totFrames;

                frameRect_.left = curFrame * 48;
                bulletSprite_.setTextureRect(frameRect_);
                animationClock_.restart();
            }
        }

        sf::Sprite getBulletSprite() { return bulletSprite_; }
        sf::Vector2f getPosition() { return position_; }
        sf::Sprite getSprite() { return bulletSprite_; }
        sf::CircleShape getCircle() { return shape_; }

};

#endif