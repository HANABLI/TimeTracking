#ifndef TIME_TRACKING_HPP
#define TIME_TRACKING_HPP
#pragma once
#include <memory>
#include <functional>

/**
 * @file TimeTracking.hpp
 *
 * @brief This is the definition of the TimeTracking class.
 *
 * copyright © 2025 by Hatem Nabli
 */
namespace TimeTracking
{
    /**
     * This represents an
     */
    class Clock
    {
        // Methods
    public:
        /**
         * This module returns the current time, in seconds, since the clock's
         * reference point (typically UNIX epoch, or Midnight UTC
         * January 1, 1970).
         */
        virtual double GetCurrentTime() = 0;
    };

    class Scheduler
    {
        // Types
    public:
        /**
         * This is the type of function which can be scheduled to be called
         * by the scheduler.
         */
        using Callback = std::function<void()>;

        // Lifecycle Managment
    public:
        ~Scheduler();
        Scheduler(const Scheduler&) = delete;
        Scheduler(Scheduler&&) noexcept;
        Scheduler& operator=(const Scheduler&) = delete;
        Scheduler& operator=(Scheduler&&) noexcept;
        // Methods
    public:
        /**
         * This is the constructor of the class
         */
        Scheduler(/* args */);

        /**
         * Return the clock object used to know when to call scheduled
         * callback
         */
        std::shared_ptr<Clock> GetClock() const;

        /**
         * This is the seter needed to set the clock.
         */
        void SetClock(std::shared_ptr<Clock> clock);

        /**
         * Schedule the given callback function to be called when the
         * time returned by the clock associated with the scheduler reached
         * the expected time.
         *
         * @param callback
         *      This is the callback function scheduled by the Schedual.
         *
         * @param expectedTime
         *      This is the value that will be returned by the associated
         *      clock at the moment when the callback function should be called.
         */
        int Schedule(Callback callback, double expectedTime);

        /**
         * Terminate the scheduled callback function corresponding to the given token.
         *
         * @note
         *      The callback may be called anyway, if canceled close to due time.
         * @param[in] token
         *      This is the token of the scheduled callback to be canceled.
         */
        void Cancel(int token);

        //------------------------------------------------------------------------
        // Methods of this section are for testing only and should not be used
        // outside of the test framework.
        // |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

        /**
         * This method force the scheduler to sample its clock and reevaluate
         * scheduled callbacks, even if the scheduler was asleep awaiting the
         * next scheduled time.
         */
        void WakeUp();

        //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
        //------------------------------------------------------------------------

        // Private properties
    private:
        /* data */

        /**
         * This is the tipe of structure that contains the private properties
         * of the instance. It is defined in the implementation and declared
         * here to ensure that it is scoped inside the class.
         */
        struct Impl;

        /**
         * This contains the private properties of the instance.
         */
        std::unique_ptr<Impl> impl_;
    };

}  // namespace TimeTracking
#endif /* TIME_TRAKING_HPP */