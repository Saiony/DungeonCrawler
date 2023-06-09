﻿#pragma once
#include "../error_code_type.h"

namespace dungeon_common::model
{
    class simple_answer_model
    {
    public:
        bool ok{};
        error_code_type error_code;

        simple_answer_model();
        simple_answer_model(bool ok, error_code_type error_code);
    };
}