#include "game_object.h"
#include <SFML/Graphics/CircleShape.hpp>

GameObject::GameObject(float x, float y, float angle, float speed) {
    position_.x = x;
    position_.y = y;
    angle_ = angle;
}

GameObject::GameObject() {
    // default constructor
}

GameObject::~GameObject() {
    // default destructor
}

void GameObject::update(float deltaTime) {
    // will be overridden in player and enemy objects

}

void GameObject::draw(sf::RenderTarget &target) {
    // will be overridden in player and enemy objects
}

void GameObject::setSpeed(float newSpeed) {
    speed_ = newSpeed;
}