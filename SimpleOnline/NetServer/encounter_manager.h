#pragma once
#include "Domain/Encounter.h"

namespace dungeon_server::domain
{
    class encounter_manager
    {
    private:
        const uint8_t max_level_ = 3;
        uint8_t level_;
        std::vector<std::shared_ptr<player>> players_;
        std::function<void(bool)> encounter_end_callback_;

        std::shared_ptr<encounter> generate_encounter() const;    
    public:
        std::shared_ptr<encounter> current_encounter;

        explicit encounter_manager(std::vector<std::shared_ptr<player>> players);
        void add_encounter_end_listener(std::function<void(bool)> callback);
        bool go_to_next_turn(action_log& action_log) const;
        void start_encounter();
        void end_encounter();
    };
}
