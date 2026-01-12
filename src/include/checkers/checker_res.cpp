#include "checkers_res.h"

void parse_result(checker_result_t& chckr_res) {
    switch (chckr_res.res_type) {
        case CheckerResultType::CHECKOFF:
            std::cout << str_checkers[static_cast<int>(chckr_res.checker_result.checker)] << " is OFF" << std::endl;
            return;

        case CheckerResultType::LIGHTAPIERR:
            LABORT(
                static_cast<int>(chckr_res.light_api_err.second),
                convert_error_to_string(chckr_res.light_api_err.first)
            );
            return;

        case CheckerResultType::CHECKRES:
            std::cout << "result of " << str_checkers[static_cast<int>(chckr_res.checker_result.checker)] << ":" << std::endl;
            for (const auto& file : chckr_res.checker_result.file_results) {
                switch (file.flres_t) {
                    case FileResultType::FLLIGHTAPIERR:
                        std::cout << file.flname << ": " << convert_error_to_string(file.errs[0].first) << std::endl;
                        break;

                    case FileResultType::FLRES:
                        print_in_one_color(WHEEL, file.flname + ":");
                        if (!file.have_errs) {
                            print_in_one_color(GREEN, "Haven't an errors");
                            break;
                        }

                        for (const auto [err, sol] : file.errs)
                            print_in_one_color(
                                YELLOW,
                                convert_error_to_string(err) + "\npossible solution:\n" + sol
                            );
                }
            }
            return;
    }
}

void parse_result(checker_result_t&& chckr_res) {
    parse_result(chckr_res);
}