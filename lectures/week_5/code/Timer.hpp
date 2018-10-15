/**
 *	\file Timer.hpp
 *	\brief Defines the Timer class for timing events.
 *	Taken from Atlas v2.0
 *	Mauricio A. Rovira Galvez - 2018
 */

#pragma once

#include <iostream>
#include <chrono>

namespace atlas
{
    namespace core
    {
        /**
         * \class Timer
         * \brief Defines a simple system for timing events.
         * 
         * This class employs the <tt> \<chrono\> </tt> library to compute
         * the time that passes from the time it is created (or reset), to the
         * time the elapsed function is called.
         * 
         * \tparam The precision of the timer.
         */
        template <typename T>
        class Timer
        {
        public:
            /**
             * Constructs the timer and initializes it to 0.
             */
            Timer()
            { }

            /**
             * Sets the timer to the current time. The elapsed time can be
             * retrieved by calling the ellapsed() function.
             */
            inline void start()
            {
                mBegin = Clock::now();
            }

            /**
             * Resets the timer back to 0.
             */
            inline void reset()
            {
                mBegin = std::chrono::time_point<Clock>();
            }

            /**
             * Returns the amount of time. The time returned is determined
             * by the resolution that was given when the Timer was created.
             */
            T elapsed() const
            {
                return std::chrono::duration_cast<Resolution>(
                        Clock::now() - mBegin);
            }

        private:
            using Clock = std::chrono::high_resolution_clock;
            using Resolution = T;
            std::chrono::time_point<Clock> mBegin;
        };
    }
}
