#pragma once
#include "base_action.h"

namespace dungeon_server::domain::action
{
    class retribution_action final : public base_action
    {
    public:
        retribution_action(const dungeon_common::model::action_types& action_type, const std::string& new_action_owner_id);

        ~retribution_action() override;
        std::string get_name() override;
        std::uint8_t get_targets_count() override;
        void use(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log) override;
    };
}
