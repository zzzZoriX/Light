#ifndef ERRORS_H
#define ERRORS_H

enum class LightReturnCode : int {
    SUCCESS = 0,
    CMDLERR = 1,
};

#include "cmd_common.h"
#include <cstdlib>

#define LABORT(code, msg) {\
    print_in_one_color(RED, msg);\
    exit(code);\
}

#endif // ERRORS_H