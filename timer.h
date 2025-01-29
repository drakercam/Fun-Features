#ifndef TIMER_H_
#define TIMER_H_

#include <SFML/System/Clock.hpp>

    // A class implementing a simple timer
    class Timer {

        public:
            // Constructor and destructor
            Timer();
            ~Timer();

            // Start the timer now: end time given in seconds
            void Start(float duration); 

            // Check if timer has finished
            bool Finished(void) const;
            void Reset();
            bool getIsRunning() const;

        private:
            sf::Clock clock_;
            float duration_;
            bool isRunning_;

    }; // class Timer

#endif // TIMER_H_
