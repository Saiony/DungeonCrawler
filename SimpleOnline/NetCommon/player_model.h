#pragma once
#include <cstdint>

class player_model
{
private:
    uint16_t id_{};
    char name_[40]{};
    uint16_t health_{};
    
public:
    player_model();
    player_model(uint16_t id, char name[],uint16_t health);
};
