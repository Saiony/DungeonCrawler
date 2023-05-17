#pragma once
#include <cstdint>

enum class action_types
{
    unknown = 0,
    sword_slash,
    heal,
    bite,
};

struct action_model
{
    action_types id;
    int target_id{};

    action_model(action_types id, int target_id);
    action_model();
};
