#include "player_config_model.h"
#include <string>

dungeon_common::model::player_config_model::player_config_model() = default;

dungeon_common::model::player_config_model::player_config_model(const std::string& new_id, const std::string& new_name,
                                                                const player_class_model player_class, const uint16_t health, const uint16_t max_health,
                                                                const uint16_t attack_damage, const uint16_t ability_power,
                                                                const std::vector<player_action_model>& action_list)
                                                                : player_class(player_class), health(health), max_health(max_health),
                                                                attack_damage(attack_damage), ability_power(ability_power)
{
    std::ranges::copy(new_id, id);
    std::ranges::copy(new_name, name);
    std::ranges::copy(action_list, std::begin(actions));
}