#include "player_factory.h"
#include "Enum/player_class_types.h"

std::vector<dungeon_common::model::action_types> get_player_actions(const dungeon_server::domain::player_class& player_class)
{
    std::vector<dungeon_common::model::action_types> actions;

    switch (player_class.id)
    {
    case dungeon_common::enums::player_class_type::unknown:
        break;
    case dungeon_common::enums::player_class_type::warrior:
        actions.push_back(dungeon_common::model::action_types::sword_slash);
        actions.push_back(dungeon_common::model::action_types::provoke);
        actions.push_back(dungeon_common::model::action_types::shield_bash);
        actions.push_back(dungeon_common::model::action_types::retribution);
        break;
    case dungeon_common::enums::player_class_type::cleric:
        actions.push_back(dungeon_common::model::action_types::heal);
        actions.push_back(dungeon_common::model::action_types::celestial_weakening);
        actions.push_back(dungeon_common::model::action_types::aegis_of_faith);
        break;
    case dungeon_common::enums::player_class_type::archer:
        actions.push_back(dungeon_common::model::action_types::pet_the_eagle);
        actions.push_back(dungeon_common::model::action_types::fire_at_will);
        break;
    case dungeon_common::enums::player_class_type::mage:
        actions.push_back(dungeon_common::model::action_types::concentrate);
        actions.push_back(dungeon_common::model::action_types::arcane_blast);
        actions.push_back(dungeon_common::model::action_types::fireball);
        actions.push_back(dungeon_common::model::action_types::frostbite);
        break;
    }

    return actions;
}

uint8_t get_hp_per_lvl(const dungeon_server::domain::player_class& player_class)
{
    switch (player_class.id)
    {
    case dungeon_common::enums::player_class_type::warrior:
        return 4;
    case dungeon_common::enums::player_class_type::cleric:
        return 2;
    case dungeon_common::enums::player_class_type::archer:
        return 2;
    case dungeon_common::enums::player_class_type::mage:
        return 2;
    default:
        return -1;
    }
}

uint8_t get_ad_per_lvl(const dungeon_server::domain::player_class& player_class)
{
    switch (player_class.id)
    {
    case dungeon_common::enums::player_class_type::warrior:
        return 2;
    case dungeon_common::enums::player_class_type::cleric:
        return 1;
    case dungeon_common::enums::player_class_type::archer:
        return 3;
    case dungeon_common::enums::player_class_type::mage:
        return 1;
    default:
        return -1;
    }
}

uint8_t get_ap_per_lvl(const dungeon_server::domain::player_class& player_class)
{
    switch (player_class.id)
    {
    case dungeon_common::enums::player_class_type::warrior:
        return 1;
    case dungeon_common::enums::player_class_type::cleric:
        return 3;
    case dungeon_common::enums::player_class_type::archer:
        return 2;
    case dungeon_common::enums::player_class_type::mage:
        return 3;
    default:
        return -1;
    }
}

uint16_t get_player_hp(const dungeon_server::domain::player_class& player_class)
{
    switch (player_class.id)
    {
    case dungeon_common::enums::player_class_type::warrior:
        return 15;
    case dungeon_common::enums::player_class_type::cleric:
        return 10;
    case dungeon_common::enums::player_class_type::archer:
        return 12;
    case dungeon_common::enums::player_class_type::mage:
        return 10;
    default:
        return -1;
    }
}

uint16_t get_player_attack_damage(const dungeon_server::domain::player_class& player_class)
{
    switch (player_class.id)
    {
    case dungeon_common::enums::player_class_type::warrior:
        return 3;
    case dungeon_common::enums::player_class_type::cleric:
        return 1;
    case dungeon_common::enums::player_class_type::archer:
        return 2;
    case dungeon_common::enums::player_class_type::mage:
        return 1;
    default:
        return -1;
    }
}

uint16_t get_player_ability_power(const dungeon_server::domain::player_class& player_class)
{
    switch (player_class.id)
    {
    case dungeon_common::enums::player_class_type::warrior:
        return 0;
    case dungeon_common::enums::player_class_type::cleric:
        return 3;
    case dungeon_common::enums::player_class_type::archer:
        return 2;
    case dungeon_common::enums::player_class_type::mage:
        return 5;
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

    const auto ad_per_lvl = get_ad_per_lvl(player_class);
    const auto ap_per_lvl = get_ap_per_lvl(player_class);
    const auto hp_per_lvl = get_hp_per_lvl(player_class);

    player player(player_id, player_name, player_class,
                  hp, ad, ap,
                  ad_per_lvl, ap_per_lvl, hp_per_lvl,
                  get_player_actions(player_class), dungeon_common::enums::elemental_property_type::normal);

    return std::make_shared<class player>(player);
}
