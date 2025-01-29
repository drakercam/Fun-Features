#include <SFML/System/Time.hpp>
#include <iostream>

#include "timer.h"
#include <SFML/System/Clock.hpp>

Timer::Timer() {
    sf::Clock clock_;
    float duration_ = 0.0f;
    isRunning_ = false;
}


Timer::~Timer() {
}


void Timer::Start(float duration) {
    duration_ = duration;
    clock_.restart();
    isRunning_ = true;
}


bool Timer::Finished(void) const {
    if (!isRunning_) {
        return false; // since if isRunning_ is false, then the timer hasn't started
    }

    return clock_.getElapsedTime().asSeconds() >= duration_;
}

void Timer::Reset() {
    clock_.restart();
    isRunning_ = false;
}

bool Timer::getIsRunning() const {
    return isRunning_;
}
