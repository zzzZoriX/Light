#include "lch_main.h"

checker_result_t leak_check(ArgsInfo ainf) {
    if (ainf.fs._Nleak)
        return CHECKER_SUCCESS(Checker::LEAK_CHECKER);

    checker_result_t res{Checker::LEAK_CHECKER};
    res.checker_result.checker = Checker::LEAK_CHECKER;
    res.res_type = CheckerResultType::CHECKRES;

    for (const auto& inp : ainf.inputs_vec) {
        std::ifstream ifp(inp);
        if (!ifp.is_open()) {
            res.res_type = CheckerResultType::LIGHTAPIERR;
            res.light_api_err = {
                error_msg_t{
                    "LIGHTAPI",
                    "~~~",
                    "Can't open an input file" + inp,
                    0
                },
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

file_result_t leak_check_file(std::ifstream ifp, struct FlagsState fs) {
    file_result_t flres;
    const token_t tokens = tokenize(std::move(ifp));
    std::map<std::string, lch_var_data> current_scope_mem_alloc;
    std::string line;
    unsigned long line_n = 1;

    flres.flres_t = FileResultType::FLRES;
    flres.have_errs = false;
/*
 * Why do I use a for instead of a for-each?
 * I'll need to navigate through the list of tokens, and it is more convenient to do this using indexes
 */
    for (std::size_t i = 0; i < tokens.size(); ++i) {
        line += tokens[i];

        if (tokens[i] == std::string{'\n'}) {
            line.clear();
            ++line_n;
            continue;
        }

        if (fs._cpp) {
            if (CPP_IS_MEM_ALLOC_WORD(tokens[i])) {
                while (tokens[++i] != ";")
                    line += tokens[i];

                current_scope_mem_alloc[lch_var_data::cpp_get_var_name(line, fs._cpp_20_on)] = lch_var_data(line, line_n, fs._cpp_20_on);
            }
            else if (CPP_IS_MEM_DEALLOC_WORD(tokens[i])) {
                while (tokens[++i] != ";")
                    line += tokens[i];

                current_scope_mem_alloc.erase(lch_var_data::cpp_get_var_name(line, fs._cpp_20_on));
            }
        }
        else {
            if (C_IS_MEM_ALLOC_WORD(tokens[i])) {
                while (tokens[++i] != ";")
                    line += tokens[i];

                current_scope_mem_alloc[lch_var_data::c_get_var_name(line)] = lch_var_data(line, line_n);
            }
            else if (C_IS_MEM_DEALLOC_WORD(tokens[i])) {
                while (tokens[++i] != ";")
                    line += tokens[i];

                current_scope_mem_alloc.erase(lch_var_data::c_get_var_name(line));
            }
        }
    }

//  TODO: do errors creating for remaining memory leaks
    if (!current_scope_mem_alloc.empty()) {
        for (const auto&[_, snd] : current_scope_mem_alloc) {
            flres.errs.push_back({
                error_msg_t(
                    "main()",
                    snd.full_line,
                    "potential memory leak",
                    snd.line_number
                ),
                std::to_string(snd.line_number + 1) + "|+ delete " + snd.var_name + ";"
            });
        }
        flres.have_errs = true;
    }

    current_scope_mem_alloc.clear();

    return flres;
}
