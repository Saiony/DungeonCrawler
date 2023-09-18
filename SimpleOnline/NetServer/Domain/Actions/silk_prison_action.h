#pragma once
#include "base_action.h"

namespace dungeon_server::domain::action
{
    class silk_prison_action final : public base_action
    {
    private:
        std::string target_id_{};
    public:
        ~silk_prison_action() override;
        explicit silk_prison_action(const dungeon_common::model::action_types& action_type,
                                      std::string new_action_owner_id,
                                      std::string target_id = {});

        std::string get_name() override;
        std::uint8_t get_targets_count() override { return 1; }

        void use(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log) override;
    };
}
