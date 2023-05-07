#pragma once
#include <cstdint>

enum class action_types
{
    unknown = 0,
    fireball = 1,
    bite = 2,
};

struct action_model
{
    action_types id;
    int target_id{};

    action_model(action_types id, int target_id);
    action_model();
};
