#include<dungeon_network.h>
#include "Models/player_model.h"

enum class custom_msg_types : uint32_t
{
    server_accept,
    server_deny,
    spell_consult,
    message_all,
    server_message,
};

class client : public dungeon_common::base_client<custom_msg_types>
{
public:
    void consult_spell(const char* spell);
};

