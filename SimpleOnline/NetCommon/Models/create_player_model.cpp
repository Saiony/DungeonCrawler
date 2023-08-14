#include "create_player_model.h"

dungeon_common::model::create_player_model::create_player_model(const std::string& name_string, const enums::player_class_type player_class_type)
                                                                     : player_class_type(player_class_type)
{
    std::ranges::copy(name_string, name);
}
