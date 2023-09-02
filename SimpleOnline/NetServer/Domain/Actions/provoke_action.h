#pragma once
#include "base_action.h"

namespace dungeon_server::domain::action
{
    class provoke_action final : public base_action
    {
    public:
        provoke_action(const dungeon_common::model::action_types& action_type, const std::string& new_action_owner_id);

        ~provoke_action() override;
        std::string get_name() override;
        std::uint8_t get_targets_count() override;
        std::string use(const std::shared_ptr<encounter>& encounter_ptr) override;
    };
}
