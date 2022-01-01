
#include <RenderBase/tools/random.h>
#include <RenderBase/defines.h>
#include <random>

float32 rb::random::randomFloat(float32 min, float32 max)
{
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<> distr(min, max);
    return distr(eng);
}
