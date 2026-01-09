#ifndef CHECKERS_RES_H
#define CHECKERS_RES_H

#include <string>
#include <vector>
#include <optional>
#include "../errors.h"

enum class Checker {
    LEAK_CHECKER,
    ADDR_CHECKER,
    SEGSIG_CHECKER,
};

enum class CheckerResultType {
    CHECKRES,
    LIGHTAPIERR,
};

typedef struct flres {
    std::string err_data,
                solution;
} file_result_t;

typedef struct chckr {
    Checker checker;
    std::vector<file_result_t> file_results;
} checker_info_t;

typedef struct chr_res {
    CheckerResultType res_type;
    error<std::string> light_api_err;
    checker_info_t checker_result;
} checker_result_t;

#endif //CHECKERS_RES_H
