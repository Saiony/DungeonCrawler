#pragma once
#include <memory>
#include <vector>
#include "Player.h"
#include "Enemies/base_enemy.h"

namespace dungeon_server::domain
{
    class base_creature;
    class base_enemy;

    class encounter
    {
    private:        
        std::function<void()> on_players_lost_callback_;
        
    public:
        std::vector<std::shared_ptr<base_enemy>> enemies;
        std::vector<std::shared_ptr<player>> players;
        std::vector<std::shared_ptr<base_creature>> creatures;
        std::shared_ptr<base_creature> active_creature;
        bool combat_ended = false;
        bool players_won = false;

        encounter(std::vector<std::shared_ptr<base_enemy>> enemies,
                  std::vector<std::shared_ptr<player>> players,
                  std::shared_ptr<base_creature> active_creature);
        void subscribe_players_lost(const std::function<void()>& callback);
        void go_to_next_turn();
        void set_game_over(bool players_won_encounter);
        void on_creature_died(const std::shared_ptr<base_creature>& creature);
        void check_encounter_ended();
        void add_enemy(const std::shared_ptr<base_enemy>& new_enemy);
        std::shared_ptr<base_creature> get_creature(const std::string& creature_id);
        std::shared_ptr<player> get_player(const std::string& player_id);
    };
}
