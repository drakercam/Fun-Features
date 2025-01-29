#include "player_game_object.h"
#include "game.h"
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/CircleShape.hpp>

PlayerGameObject::PlayerGameObject(float x, float y, float angle, float speed) 
    : GameObject(x, y, angle, speed) {
        circle_.setRadius(25.0f);
        circle_.setOrigin(circle_.getRadius(), circle_.getRadius());
        circle_.setPosition(position_.x, position_.y);
        circle_.setFillColor(sf::Color::Magenta);
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

    target.draw(circle_);
}


// PlayerGameObject inherits from GameObject, however the update function will be overridden to change specifics
// about the player

void PlayerGameObject::update(float deltaTime,  sf::RenderTarget &target) {
    // new functionality to be added here

    // for now simply call the parent update function
    GameObject::update(deltaTime);
}