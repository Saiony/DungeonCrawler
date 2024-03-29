﻿#pragma once

namespace dungeon_common::enums
{
    enum class creature_status_type
    {
        unknown = 0,
        stun,
        eagle_petted,
        provoking,
        concentrating,
        frozen,
        burning,
        invulnerable,
        retribution,
        attack_lowered,
        poisoned,
        stuck_in_spiders_web,
    };
}