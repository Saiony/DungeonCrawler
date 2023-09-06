#include "arrow_shower_action.h"

dungeon_server::domain::action::arrow_shower_action::arrow_shower_action(const dungeon_common::model::action_types& action_type,
                                                                         const std::string& new_action_owner_id,
                                                                         const dungeon_common::enums::action_target_types target_type)
    : base_action(action_type, new_action_owner_id), target_type_(target_type)
{
    if (target_type_ == dungeon_common::enums::action_target_types::unknown)
        throw std::exception("Invalid target type");
}

dungeon_server::domain::action::arrow_shower_action::~arrow_shower_action() = default;

std::string dungeon_server::domain::action::arrow_shower_action::get_name()
{
    return "arrow shower";
}

std::uint8_t dungeon_server::domain::action::arrow_shower_action::get_targets_count()
{
    return 0;
}

std::string dungeon_server::domain::action::arrow_shower_action::use(const std::shared_ptr<encounter>& encounter_ptr)
{
    const auto action_owner = encounter_ptr->get_creature(action_owner_id);
    std::string log;

    if (target_type_ == dungeon_common::enums::action_target_types::all_players)
    {
        std::ranges::for_each(encounter_ptr->players,
                              [this, &action_owner, &encounter_ptr, &log](auto player)
                              {
                                  log += shoot_arrow(encounter_ptr, action_owner, player);
                              });
    }
    else if (target_type_ == dungeon_common::enums::action_target_types::all_enemies)
    {
        std::ranges::for_each(encounter_ptr->enemies,
                              [this, &action_owner, &encounter_ptr, &log](auto enemy)
                              {
                                  log += shoot_arrow(encounter_ptr, action_owner, enemy);
                              });
    }

    return log;
}

std::string dungeon_server::domain::action::arrow_shower_action::shoot_arrow(const std::shared_ptr<encounter>& encounter,
                                                                             const std::shared_ptr<base_creature>& action_owner,
                                                                             const std::shared_ptr<base_creature>& target)
{
    std::string log = action_owner->name + " used " + get_name() + " on " + target->name;
    const auto damage = static_cast<uint16_t>(randomize_damage(action_owner->attack_damage, variance_));

    target->take_damage(damage, log);
    action_owner->on_attack(encounter, action_owner->public_id, log);

    return log;
}
