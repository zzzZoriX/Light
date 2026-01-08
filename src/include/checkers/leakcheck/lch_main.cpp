#include "lch_main.h"

checker_result leak_check(ArgsInfo ainf) {
    if (ainf.fs._Nleak)
        return std::nullopt;

    struct chr_res res = {{}, Checker::LEAK_CHECKER, CheckerResultType::SUCCESS, NOERR};

    for (const auto& inp : ainf.inputs_vec) {
        std::ifstream ifp(inp);
        if (!ifp.is_open()) {
            res.type = CheckerResultType::LIGHTAPIERR;
            res.light_api_res.second = LightReturnCode::CANTOPENFILEERR;
            res.light_api_res.first = "Can't open an input file: " + inp;

            return res;
        }

        res.results.push_back(leak_check_file(std::move(ifp), ainf.fs));
    }

    return res;
}
