#pragma once
#include "base_action.h"

namespace dungeon_server::domain::action
{
    class frostbite_action final : public base_action
    {
    private:
        const float_t variance_ = 0;
        const float_t dmg_multiplier_ = 1;
    public:
        std::string target_id{};
        
        ~frostbite_action() override;
        std::string get_name() override;
        std::uint8_t get_targets_count() override;
        void use(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log) override;
    };
}
