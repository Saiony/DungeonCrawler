#include "player.h"
#include <utility>
#include "Utility/guid_generator.h"

dungeon_server::domain::player::player(std::string client_id, const std::string& new_name, domain::player_class player_class,
                                       const uint16_t new_health, const uint16_t new_damage, const uint16_t new_ability_power,
                                       const uint8_t ad_per_level, const uint8_t ap_per_level, const uint8_t hp_per_level,
                                       std::vector<dungeon_common::model::action_types> actions,
                                       const dungeon_common::enums::elemental_property_type elemental_property)
    : base_creature(new_name, new_health, new_damage, new_ability_power, elemental_property),
      private_id(std::move(client_id)), aggro(1),
      player_class(std::move(player_class)), actions(std::move(actions)),
      ad_per_level(ad_per_level), ap_per_level(ap_per_level), hp_per_level(hp_per_level)
{
    public_id = dungeon_common::utility::guid_generator::create_guid();
}

void dungeon_server::domain::player::level_up(const dungeon_common::enums::creature_stat_types stat_id, action_log& log)
{
    switch (stat_id)
    {
    case dungeon_common::enums::creature_stat_types::attack_damage:
        {
            log.add_log(name + " [AD] " + std::to_string(base_ad_) + " -> " + std::to_string(base_ad_ + ad_per_level));
            base_ad_ += ad_per_level;
            break;
        }
    case dungeon_common::enums::creature_stat_types::ability_power:
        {
            log.add_log(name + " [AP] " + std::to_string(base_ap_) + " -> " + std::to_string(base_ap_ + ap_per_level));
            base_ap_ += ap_per_level;
            break;
        }
    case dungeon_common::enums::creature_stat_types::max_health:
        {
            log.add_log(name + " [HP] " + std::to_string(health) + " -> " + std::to_string(health + hp_per_level));
            health += hp_per_level;
            break;
        }
    default:
        {
            throw std::exception("Invalid stat id");
        }
    }
}
