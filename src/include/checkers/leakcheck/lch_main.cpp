#include "lch_main.h"

checker_result_t leak_check(ArgsInfo ainf) {
    if (ainf.fs._Nleak)
        return CHECKER_SUCCESS(Checker::LEAK_CHECKER);

    checker_result_t res;
    res.checker_result.checker = Checker::LEAK_CHECKER;
    res.res_type = CheckerResultType::CHECKRES;

    for (const auto& inp : ainf.inputs_vec) {
        std::ifstream ifp(inp);
        if (!ifp.is_open()) {
            res.res_type = CheckerResultType::LIGHTAPIERR;
            res.light_api_err = {
                "Can't open an input file" + inp,
                LightReturnCode::CANTOPENFILEERR
            };

            return res;
        }

        res.checker_result.file_results.push_back(leak_check_file(
                std::move(ifp),
                ainf.fs
            ));
    }

    return res;
}