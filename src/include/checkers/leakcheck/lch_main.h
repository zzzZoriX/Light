#ifndef LCH_H
#define LCH_H

#include "../../command_process.h"
#include "../checkers_res.h"
#include <fstream>

/**
 * @brief check inputs for a memory leak errors
 *
 * @param ainf
 * @return checker_result
 */
checker_result leak_check(ArgsInfo ainf);

/**
 * @brief check input file for a memory leaks
 *
 * @param ifp
 * @param fs
 * @return file_result
 */
file_result leak_check_file(std::ifstream ifp, struct FlagsState fs);

#endif // LCH_H