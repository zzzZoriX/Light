#ifndef CHECKERS_RES_H
#define CHECKERS_RES_H

#include <string>
#include <vector>
#include "../errors.h"

enum class Checker {
    LEAK_CHECKER = 0,
    ADDR_CHECKER = 1,
    SEGSIG_CHECKER = 2,
};

constexpr std::string str_checkers[3] = {
    "Leak checker",
    "Addressing errors checker",
    "Segmentation faults checker",
};

enum class CheckerResultType {
    CHECKOFF,
    CHECKRES,
    LIGHTAPIERR,
};

typedef struct flres {
    bool have_errs;
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

#define CHECKER_SUCCESS(chckr) (checker_result_t){\
    .res_type = CheckerResultType::CHECKOFF,\
    .light_api_err = NOERR,\
    .checker_result = {\
        chckr,\
        {}\
    }\
}

#endif //CHECKERS_RES_H
