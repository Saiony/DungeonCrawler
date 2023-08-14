﻿#include "player_factory.h"
#include "Enum/player_class_types.h"

std::vector<dungeon_common::model::action_types> get_player_actions(const dungeon_server::domain::player_class& player_class)
{
    std::vector<dungeon_common::model::action_types> actions;

    switch (player_class.id)
    {
    case dungeon_common::enums::warrior:
        actions.push_back(dungeon_common::model::action_types::sword_slash);
        break;
    case dungeon_common::enums::cleric:
        actions.push_back(dungeon_common::model::action_types::heal);
        break;
    case dungeon_common::enums::unknown:
        break;
    }

    return actions;
}

uint16_t get_player_hp(const dungeon_server::domain::player_class& player_class)
{
    switch (player_class.id)
    {
    case dungeon_common::enums::warrior:
        return 15;
    case dungeon_common::enums::cleric:
        return 10;
    default:
        return -1;
    }
}

uint16_t get_player_attack_damage(const dungeon_server::domain::player_class& player_class)
{
    switch (player_class.id)
    {
    case dungeon_common::enums::warrior:
        return 3;
    case dungeon_common::enums::cleric:
        return 1;
    default:
        return -1;
    }
}

uint16_t get_player_ability_power(const dungeon_server::domain::player_class& player_class)
{
    switch (player_class.id)
    {
    case dungeon_common::enums::warrior:
        return 0;
    case dungeon_common::enums::cleric:
        return 3;
    default:
        return -1;
    }
}

std::shared_ptr<dungeon_server::domain::player> dungeon_server::domain::factory::player_factory::create_player
(const std::string& player_id, const std::string& player_name, const dungeon_common::enums::player_class_type player_class_id)
{
    player_classes player_classes;
    const auto player_class = player_classes.get_class(player_class_id);

    const auto hp = get_player_hp(player_class);
    const auto ad = get_player_attack_damage(player_class);
    const auto ap = get_player_ability_power(player_class);
    
    player player(player_id, player_name, player_class, hp,ad,ap, get_player_actions(player_class));
    return std::make_shared<class player>(player);
}
