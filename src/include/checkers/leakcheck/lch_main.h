#ifndef LCH_H
#define LCH_H

#include "../../command_process.h"
#include "../checkers_res.h"
#include <fstream>
#include <map>
#include "../tokenizer.h"
#include "lch_data.h"
#include "lch_common.h"

const std::string C_DEF_MEM_ALLOC_METHODS[] = {
    "malloc",
    "calloc",
    "realloc"
};

const std::string C_DEF_MEM_DEALLOC_METHOD = "free";

//  C methods + "new" keyword
const std::string CPP_DEF_MEM_ALLOC_METHODS[] = {
    "malloc",
    "calloc",
    "realloc",
    "new"
};

//  C method + "delete" keyword
const std::string CPP_DEF_MEM_DEALLOC_METHODS[] = {
    "free",
    "delete"
};

/* check file for a leak errors and return result struct */
checker_result_t leak_check_file(const std::string& fname, token_t& tok_stream);

/* reqursive check the scope data */
scope_mdata_t leak_check_scope(
	token_t::iterator& beg, 
	token_t::iterator& end,
	scope_mdata_t& head,
	scope_mdata_t& global,
	const std::string& scope_name,
	const std::vector<std::string> fnames
);

static bool
CPP_IS_MEM_ALLOC_WORD(const std::string& word) {
    for (const auto& w : CPP_DEF_MEM_ALLOC_METHODS)
        if (word == w)
            return true;;

    return false;
}
static bool
C_IS_MEM_ALLOC_WORD(const std::string& word) {
    for (const auto& w : C_DEF_MEM_ALLOC_METHODS)
        if (word == w)
            return true;

    return false;
}

static bool
CPP_IS_MEM_DEALLOC_WORD(const std::string& word) {
    for (const auto& w : CPP_DEF_MEM_DEALLOC_METHODS)
        if (w == word)
            return true;

    return false;
}

#define C_IS_MEM_DEALLOC_WORD(word) (word) == C_DEF_MEM_DEALLOC_METHOD

#endif // LCH_H
