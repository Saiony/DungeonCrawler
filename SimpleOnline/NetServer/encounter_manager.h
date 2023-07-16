#pragma once
#include "Domain/Encounter.h"

namespace dungeon_server::domain
{
    class encounter_manager
    {
    private:
        uint8_t level_;
        std::vector<std::shared_ptr<player>> players_;

        std::shared_ptr<encounter> generate_encounter() const;    
        void remove_dead_creatures() const;
        void go_to_next_encounter();
    public:
        std::shared_ptr<encounter> current_encounter;
        
        encounter_manager(std::vector<std::shared_ptr<player>> players);
        void go_to_next_turn();
    };
}
