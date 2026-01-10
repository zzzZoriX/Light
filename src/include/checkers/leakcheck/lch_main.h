#ifndef LCH_H
#define LCH_H

#include "../../command_process.h"
#include "../checkers_res.h"
#include <fstream>
#include <vector>
#include "../tokenizer.h"

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
 * @return file_result_t
 */
file_result_t leak_check_file(std::ifstream ifp, struct FlagsState fs);

#endif // LCH_H