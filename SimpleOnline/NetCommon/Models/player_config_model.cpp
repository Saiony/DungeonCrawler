#include "player_config_model.h"
#include <string>

dungeon_common::model::player_config_model::player_config_model() = default;

dungeon_common::model::player_config_model::player_config_model(const std::string& new_id, const std::string& new_name, const uint32_t health, const std::vector<player_action_model>& action_list)
                           : max_health(health)
{
    std::copy(begin(new_id), end(new_id), id);
    std::copy(begin(new_name), end(new_name), name);
    std::ranges::copy(action_list, std::begin(actions));
}