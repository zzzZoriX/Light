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
    SUCCESS,
    ERR_FOUND,
    LIGHTAPIERR,
};

typedef struct flres{
    bool have_errors;
    std::string error,
                solution;

    flres(const bool have_err, const std::string& err, const std::string& sol) noexcept:
    have_errors(have_err), error(err), solution(sol) {}
} file_result;

struct chr_res {
public:
    std::vector<file_result> results;
    Checker checker;
    CheckerResultType type;
    error<std::string> light_api_res;

    chr_res() = default;
    chr_res(
        const std::vector<file_result>& res,
        const Checker chckr,
        const CheckerResultType type,
        const error<std::string>& lapir
    ) noexcept:
    results(res), checker(chckr), type(type), light_api_res(lapir) {}
};

using checker_result = std::optional<struct chr_res>;

#endif //CHECKERS_RES_H
