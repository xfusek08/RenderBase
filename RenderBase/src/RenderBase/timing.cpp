
#include <RenderBase/timing.h>

// #define NO_LOG
#include <RenderBase/logging.h>

using namespace rb::timing;
using namespace rb::timing;

Timer::Timer(Time interval)
{
    setTickInterval(interval);
    beginTime = std::chrono::high_resolution_clock::now();
    nextScheduledTick = getNow();
}

void Timer::setTickInterval(Time interval)
{
    tickInterval = interval;
}

void Timer::setOnTickCallback(TickCallBack callback)
{
    this->callback = callback;
}

void Timer::checkTick()
{
    auto now = getNow();
    if (now >= nextScheduledTick) {
        nextScheduledTick = nextScheduledTick + tickInterval;
        
        // tick timer
        currentTimeStep = {
            currentTimeStep.order + 1,
            now - currentTimeStep.currentTime,
            now // currentTime,
        };
        
        RB_DEBUG("Tick " << currentTimeStep.order << ": " << currentTimeStep.currentTime << "s, delta: " << currentTimeStep.deltaTime << "s, next tick will be in time: " << nextScheduledTick << "s.");
        callback(currentTimeStep);
    }
}

Time Timer::getNow()
{
    auto now  = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> fsec = now - beginTime;
    return fsec.count();
}
