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
        virtual void update(float deltaTime);
        virtual void draw(sf::RenderTarget &target);
        void setSpeed(float newSpeed);
        float getSpeed() { return speed_; }
        const sf::Vector2f& getPosition() const { return position_; }
        void setPosition(const sf::Vector2f& pos) { position_ = pos; }
};

#endif