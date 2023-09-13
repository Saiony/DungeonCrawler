#pragma once
#include <string>

namespace dungeon_common::model
{
    enum class action_types
    {
        unknown = 0,
        sword_slash,
        heal,
        bite,
        shield_bash,
        holy_light,
        fire_at_will,
        pet_the_eagle,
        provoke,
        arrow_shower,
        arrow_shot,
        distracting_slash,
        concentrate,
        fireball,
        frostbite,
        arcane_blast,
        retribution,
        aegis_of_faith,
        celestial_weakening,
    };

    struct action_use_model
    {
        action_types id;
        char target_id[39]{};
        char owner_id[39]{};

        action_use_model(action_types id, const std::string& new_owner_id, const std::string& new_target_id);
        action_use_model();
    };
}
