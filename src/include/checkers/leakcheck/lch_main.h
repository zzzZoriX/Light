#ifndef LCH_H
#define LCH_H

#include "../../command_process.h"
#include "../checkers_res.h"
#include <fstream>
#include <map>
#include "../tokenizer.h"
#include "lch_data.h"

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


/**
 * @brief check inputs for a memory leak errors
 *
 * @param ainf
 * @return checker_result_t
 */
checker_result_t leak_check(ArgsInfo ainf);

/**
 * @brief check input file for a memory leaks
 *
 * @param ifp
 * @param fs
 * @param flname
 * @return file_result_t
 */
file_result_t leak_check_file(std::ifstream ifp, FlagsState& fs, const std::string& flname);

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