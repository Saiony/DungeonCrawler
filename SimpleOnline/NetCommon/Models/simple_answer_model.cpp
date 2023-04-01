#include "simple_answer_model.h"


simple_answer_model::simple_answer_model()
{
    ok = false;
    error_code = error_code_type::unknown;
}

simple_answer_model::simple_answer_model(const bool ok, const error_code_type error_code):ok(ok), error_code(error_code)
{
}
