#include "player_class.h"

dungeon_client::domain::player_class::player_class() = default;

dungeon_client::domain::player_class::player_class(const dungeon_common::enums::player_class_type id, std::string name): id(id), name(std::move(name))
{
}
