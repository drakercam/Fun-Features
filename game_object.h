#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics/RenderTarget.hpp>

class GameObject {
    private:
        float angle_, speed_;
        sf::Vector2f position_;
        // sf::CircleShape circle;

    public:
        GameObject();
        GameObject(float x, float y, float angle, float speed);
        ~GameObject();
        void update(float deltaTime);
        void draw(sf::RenderTarget &target);
        void setSpeed(float newSpeed);
        float getSpeed() { return speed_; }
};

#endif