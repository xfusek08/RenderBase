
#pragma once

#include <RenderBase/defines.h>
#include <RenderBase/defaults.h>

#include <functional>
#include <chrono>

namespace rb::timing {
    // current time implementation is just float value of seconds
    // representing time interval in second usually time interval starting from application start.
    using Time = float32;
    
    struct TimeStep {
        uint32 order;       // time step ordering counted from 0
        Time   deltaTime;   // time elapsed from last time step
        Time   currentTime; // time of this step
    };
    
    using TickCallBack = std::function<bool(const TimeStep&)>;
    
    class Timer
    {
        public:
            Timer(Time interval = DEFAULT_TICK_INTERVAL);
            void setTickInterval(Time interval);
            void setOnTickCallback(TickCallBack callback);
            
            // Timer runtime control
            Time getNow();
            void checkTick();
            
            inline const TimeStep& getCurrentTimeStep() const { return currentTimeStep; }
            
        private:
            TimeStep     currentTimeStep;
            Time         tickInterval;
            Time         nextScheduledTick;
            TickCallBack callback;
            
            // completely local implementation detail but it needs to be store in class constext
            // an pimpl idiom would introduce unnecessary spart pointer.
            std::chrono::time_point<std::chrono::high_resolution_clock> beginTime;
    };
}
