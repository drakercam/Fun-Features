#include "player_game_object.h"
#include "game.h"
#include "bullet.h"
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <SFML/Graphics/RenderTexture.hpp>

PlayerGameObject::PlayerGameObject(float x, float y, float angle, float speed)  
    : GameObject(x, y, angle, speed),
      frameRect_(0, 0, 106, 77) {

        speed_ = speed;

        setupPlayer();

        shootingTimer.Start(0.5f);

    } // use the game_object constructor

PlayerGameObject::PlayerGameObject() {
    // default constructor
} 

PlayerGameObject::~PlayerGameObject() {
    // default destructor
    // for (auto &bullet : bullets_) {
    //     delete bullet;
    // }
}

void PlayerGameObject::draw(sf::RenderTarget &target) {
    circle_.setOrigin(circle_.getRadius(), circle_.getRadius());
    circle_.setPosition(position_.x, position_.y);
    circle_.setFillColor(sf::Color::Magenta);
    player_sprite_.setOrigin(circle_.getRadius(), circle_.getRadius());
    player_sprite_.setPosition(position_.x - 24.0f, position_.y - 10.0f);

    // target.draw(circle_);    // for debug purposes
    target.draw(player_sprite_);

    // Draw bullets
    for (auto& bullet : bullets_) {
        target.draw(bullet->getBulletSprite());
        // target.draw(bullet->getCircle());
    }
}

void PlayerGameObject::update(sf::RenderTarget &target, float deltaTime) {
    // update player based on keyboard input
    keyboardInput(deltaTime);

    shoot();

    removeBullets(deltaTime, target);

    updateAnimation();

    // for now simply call the parent update function
    GameObject::update(deltaTime);
}

void PlayerGameObject::setPlayerPosition(float x, float y) {
    position_.x = x;
    position_.y = y;
    circle_.setPosition(position_.x, position_.y);
}

sf::Vector2f PlayerGameObject::getPosition() const {
    return position_;
}

void PlayerGameObject::removeBullets(float deltaTime, sf::RenderTarget &target) {
    for (int i = 0;i < bullets_.size(); ++i) {
        Bullet* bullet = bullets_[i];
        bullet->animation();
        bullet->move(deltaTime);

        // // Check if bullet is out of bounds
        if ((bullet->getBulletSprite().getPosition().x < 0 || 
            bullet->getBulletSprite().getPosition().x > target.getSize().x)) {
            
            bullets_.erase(bullets_.begin() + i); // Remove from vector
            // std::cout << "Removed bullet " << i << std::endl;
        }
    }
}

void PlayerGameObject::setupPlayer() {

    circle_.setRadius(30.0f);
    circle_.setOrigin(circle_.getRadius(), circle_.getRadius());
    circle_.setPosition(position_.x, position_.y);
    circle_.setFillColor(sf::Color::Magenta);

    if (!player_texture_.loadFromFile("textures/spaceship-unit.png")) {
        std::cerr << "Failed to load background image!" << std::endl;
    }

    player_texture_.setSmooth(false);
    player_sprite_.setTexture(player_texture_);
    player_sprite_.setTextureRect(frameRect_);

    player_sprite_.setOrigin(circle_.getRadius(), circle_.getRadius());
    player_sprite_.setPosition(position_.x - 24.0f, position_.y - 10.0f);
}

void PlayerGameObject::keyboardInput(float deltaTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        angle_ = 0.0f;
        position_.y -= speed_ * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        angle_ = 0.0f;
        position_.y += speed_ * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        angle_ = 0.0f;
        direction_ = "left";
        position_.x -= speed_ * deltaTime;
        player_sprite_.setScale(-1.0f, 1.0f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        angle_ = 0.0f;
        direction_ = "right";
        position_.x += speed_ * deltaTime;
        player_sprite_.setScale(1.0f, 1.0f);
    }
    rotatePlayer();
}

void PlayerGameObject::rotatePlayer() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if (direction_ == "left") {
            angle_ = 15.0f;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if (direction_ == "right") {
            angle_ = -15.0f;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if (direction_ == "left") {
            angle_ = 345.0f;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if (direction_ == "right") {
            angle_ = -345.0f;
        }
    }
    player_sprite_.setRotation(angle_);
}

void PlayerGameObject::shoot() {
    // Only shoot when the 'E' key is pressed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && shootingTimer.Finished()) {
        std::string bulletDirection = direction_;
        Bullet* bullet = new Bullet(position_.x, position_.y, bulletDirection);
        bullets_.push_back(bullet); // Add the bullet to the bullets container
        shootingTimer.Reset();
        shootingTimer.Start(0.5f);
    }
}

void PlayerGameObject::updateAnimation() {
    if (animationClock_.getElapsedTime().asSeconds() >= frameDuration_) {
        curFrame = (curFrame + 1) % totFrames;

        frameRect_.left = curFrame * 106;
        player_sprite_.setTextureRect(frameRect_);
        animationClock_.restart();
    }
}