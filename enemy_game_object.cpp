#include "enemy_game_object.h"
#include "player_game_object.h"
#include "game.h"
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <random>
#include <iostream>

EnemyGameObject::EnemyGameObject(float angle, float speed, int i)
    : frameRect_(0, 0, 48, 48),
      velocity_(0.0f, 0.0f) {
    // Create a random device and seed the random number generator
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());

    // Define distributions for the desired ranges
    std::uniform_real_distribution<float> dist1(50.0f, 1310.0f);
    std::uniform_real_distribution<float> dist2(50.0f, 750.0f);

    // Generate random numbers
    float randomFloat1 = dist1(gen);
    float randomFloat2 = dist2(gen);

    setEnemyPosition(randomFloat1, randomFloat2);

    // vector to store colours to be used by enemies and any other future objects.
    std::vector<sf::Color> colors = {
        sf::Color::Red,      // Red
        sf::Color::Blue,     // Blue
        sf::Color::Green,    // Green
        sf::Color(128, 0, 128),  // Purple
        sf::Color(255, 192, 203), // Pink
        sf::Color::Yellow,   // Yellow
        sf::Color(255, 165, 0),  // Orange
        sf::Color(139, 69, 19),  // Brown
        sf::Color::Cyan,    // Black
        sf::Color::White     // White 
    };
    
    circle_.setRadius(23.0f);
    circle_.setOrigin(circle_.getRadius(), circle_.getRadius());
    circle_.setFillColor(sf::Color::Blue);

    color_pos_ = i;

    circle_.setFillColor(colors[color_pos_]);

    if (!enemy_texture_.loadFromFile("textures/Spritesheet.png")) {
        std::cerr << "Failed to load background image!" << std::endl;
    }

    enemy_texture_.setSmooth(false);
    enemy_sprite_.setTexture(enemy_texture_);
    enemy_sprite_.setTextureRect(frameRect_);
    enemy_sprite_.setOrigin(circle_.getRadius(), circle_.getRadius());
    enemy_sprite_.setPosition(position_.x, position_.y);

} // use the game_object constructor

EnemyGameObject::EnemyGameObject() {
    // default constructor
} 

EnemyGameObject::~EnemyGameObject() {
    // default destructor
}

void EnemyGameObject::setEnemyPosition(float new_x, float new_y) {
    position_.x = new_x;
    position_.y = new_y;
    circle_.setPosition(position_.x, position_.y);
}

sf::Vector2f EnemyGameObject::getPosition() {
    return position_;
}

void EnemyGameObject::createNewRandomPosition() {
    // Create a random device and seed the random number generator
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());

    // Define distributions for the desired ranges
    std::uniform_real_distribution<float> dist1(50.0f, 1230.0f);
    std::uniform_real_distribution<float> dist2(50.0f, 550.0f);

    // Generate random numbers
    float randomFloat1 = dist1(gen);
    float randomFloat2 = dist2(gen);

    setEnemyPosition(randomFloat1, randomFloat2);
}

void EnemyGameObject::draw(sf::RenderTarget &target) {

    circle_.setOrigin(circle_.getRadius(), circle_.getRadius());
    circle_.setPosition(position_.x, position_.y);
    enemy_sprite_.setOrigin(circle_.getRadius(), circle_.getRadius());
    enemy_sprite_.setPosition(position_.x, position_.y);
    enemy_sprite_.setScale(1.604f, 1.604f);

    target.draw(enemy_sprite_);
    // target.draw(circle_);   // for debug purposes
}

// PlayerGameObject inherits from GameObject, however the update function will be overridden to change specifics
// about the player

void EnemyGameObject::update(float deltaTime, PlayerGameObject &player) {
    position_ += velocity_ * deltaTime;

    // new functionality to be added here
    if (animationClock_.getElapsedTime().asSeconds() >= frameDuration_) {
        curFrame = (curFrame + 1) % totFrames;

        frameRect_.left = curFrame * 48;
        enemy_sprite_.setTextureRect(frameRect_);
        animationClock_.restart();
    }

    // wandering towards player functionality
    sf::Vector2f playerPos = player.getPosition();

    sf::Vector2f desired = playerPos - getPosition();
    sf::Vector2f steering = desired - getVelocity();

    float length = std::sqrt(steering.x * steering.x + steering.y * steering.y);
    if (length != 0) {
        steering /= length; // normalize
    }

    steering *= 1.0f;
    velocity_ += steering;

    // const float maxSpeed = 150.0f;  // Limit max speed
    // if (std::sqrt(velocity_.x * velocity_.x + velocity_.y * velocity_.y) > maxSpeed) {
    //     velocity_ = velocity_ / std::sqrt(velocity_.x * velocity_.x + velocity_.y * velocity_.y) * maxSpeed;
    // }

    // // Add randomness to wandering
    // float randNum = ((float)rand()) / ((float)RAND_MAX);
    // float randAngle = randNum * 2.0f * 3.14159265f;  // Random angle for wandering
    // float radius = 100.0f;  // Adjust the wandering radius

    // // Add random offset to the desired direction (towards the player)
    // sf::Vector2f randomWanderingOffset(radius * cos(randAngle), radius * sin(randAngle));
    // desired += randomWanderingOffset;  // Add the wandering offset to the direction

    // timer_.Reset();

    // for now simply call the parent update function
    GameObject::update(deltaTime);
}