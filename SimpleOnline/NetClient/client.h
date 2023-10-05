#pragma once
#include<dungeon_network.h>
#include <functional>
#include <functional>
#include <functional>
#include <functional>

#include "Domain/bonfire_result.h"
#include "Domain/bonfire_story_telling.h"
#include "Domain/encounter.h"
#include "Domain/gameplay_state.h"
#include "Domain/lobby.h"
#include "Domain/player_class.h"
#include "Domain/player_complete.h"
#include "Domain/story.h"
#include "Domain/story_read.h"
#include "Models/action_use_model.h"
#include "Models/player_classes_model.h"
#include "Models/player_config_model.h"
#include "Models/simple_answer_model.h"

namespace dungeon_client
{
    class client : public dungeon_common::base_client<dungeon_common::custom_msg_types>
    {
    private:
        std::unique_ptr<domain::player_complete> player_ptr_;
        bool handle_messages();
    public:
        std::condition_variable condition_var;
        std::mutex mutex;

        client();
        void end() const;
        void connect(const std::string& host, uint16_t port, const std::function<void(dungeon_common::model::simple_answer_model)>& callback);
        void read_input(const std::function<void(std::string input)>& callback);
        void validate_name(const char* name, const std::function<void(dungeon_common::model::simple_answer_model)>& callback);
        void get_player_classes(const std::function<void(std::vector<domain::player_class> player_classes)>& callback);
        void create_player(const std::string& name, dungeon_common::enums::player_class_type player_class,
                           const std::function<void(domain::player_complete)>& callback);
        void set_player(domain::player_complete& player);
        void set_player_ready(bool ready, const std::function<void(domain::lobby)>& callback);
        void send_action(dungeon_common::model::action_types action_id, const std::string& target_id);
        void request_next_state(const std::function<void(domain::gameplay_state)>& callback);
        void request_match_start(const std::function<void(domain::encounter)>& callback);
        void wait_message();
        domain::player_complete get_player() const;
        void request_story(const std::function<void(domain::story)>& callback);
        void send_story_read(const std::function<void(domain::story_read)>& callback);
        void request_bonfire_story_teller(const std::function<void(domain::bonfire_story_telling)>& callback);
        void send_bonfire_story(const domain::creature_stats& stat, const std::string& story, const std::function<void(domain::bonfire_result)>& callback);
        void subscribe_bonfire_result(const std::function<void(domain::bonfire_result)>& callback);

        std::function<void(std::string input)> player_input_callback;
        std::function<void(dungeon_common::model::simple_answer_model)> connection_callback;
        std::function<void(dungeon_common::model::simple_answer_model)> validate_name_callback;
        std::function<void(std::vector<domain::player_class>)> get_player_classes_callback;
        std::function<void(domain::player_complete)> create_player_callback;
        std::function<void(domain::lobby)> set_player_ready_callback;
        std::function<void(domain::gameplay_state)> get_gameplay_state_callback;
        std::function<void(domain::encounter)> get_encounter_callback;
        std::function<void(domain::story)> get_story_callback;
        std::function<void(domain::story_read)> send_story_read_callback;        
        std::function<void(domain::bonfire_story_telling)> get_bonfire_story_teller_callback;
        std::function<void(domain::bonfire_result)> bonfire_story_result_callback;
    };
}
