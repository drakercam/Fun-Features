#include "player_game_object.h"
#include "game.h"
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>

PlayerGameObject::PlayerGameObject(float x, float y, float angle, float speed) 
    : GameObject(x, y, angle, speed) {
        circle_.setRadius(36.0f);
        circle_.setOrigin(circle_.getRadius(), circle_.getRadius());
        circle_.setPosition(position_.x, position_.y);
        circle_.setFillColor(sf::Color::Magenta);

        if (!player_texture_.loadFromFile("textures/mineral_monster_slayer.png")) {
            std::cerr << "Failed to load background image!" << std::endl;
        }
        player_texture_.setSmooth(false);
        player_sprite_.setTexture(player_texture_);
        player_sprite_.setOrigin(circle_.getRadius(), circle_.getRadius());
        player_sprite_.setPosition(position_.x, position_.y);

    } // use the game_object constructor

PlayerGameObject::PlayerGameObject() {
    // default constructor
} 

PlayerGameObject::~PlayerGameObject() {
    // default destructor
}

void PlayerGameObject::setPlayerPosition(float x, float y) {
    position_.x = x;
    position_.y = y;
    circle_.setPosition(position_.x, position_.y);
}

sf::Vector2i PlayerGameObject::getPosition() {
    return position_;
}

void PlayerGameObject::draw(sf::RenderTarget &target) {
    circle_.setOrigin(circle_.getRadius(), circle_.getRadius());
    circle_.setPosition(position_.x, position_.y);
    circle_.setFillColor(sf::Color::Magenta);
    player_sprite_.setOrigin(circle_.getRadius(), circle_.getRadius());
    player_sprite_.setPosition(position_.x, position_.y);

    // target.draw(circle_);
    target.draw(player_sprite_);
}


// PlayerGameObject inherits from GameObject, however the update function will be overridden to change specifics
// about the player

void PlayerGameObject::update(float deltaTime,  sf::RenderTarget &target) {
    // new functionality to be added here

    // for now simply call the parent update function
    GameObject::update(deltaTime);
}