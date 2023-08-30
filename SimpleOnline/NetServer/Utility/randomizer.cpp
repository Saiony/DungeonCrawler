#include "randomizer.h"

#include <random>

int dungeon_server::utility::randomizer::randomize(const int min, const int max)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution random_number(min, max);

    return random_number(rng);
}
