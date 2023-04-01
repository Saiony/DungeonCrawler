#pragma once
#include<dungeon_network.h>
#include "Models/player_model.h"
#include "Models/simple_answer_model.h"

class simple_answer_model;

enum class custom_msg_types : uint32_t
{
    server_accept,
    server_deny,
    message_all,
    server_message,
    spell_consult,
    validate_name,
};

class client final : public dungeon_common::base_client<custom_msg_types>
{
public:
    //void validate_name(const char* name, auto& callback);
    void consult_spell(const char* spell);
    void validate_name(const char* name, function<void(simple_answer_model)> callback);
    
    function<void(simple_answer_model)> validate_name_callback;
};
