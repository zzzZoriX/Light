#ifndef ERRORS_H
#define ERRORS_H

enum class LightReturnCode : int {
    SUCCESS         = 0,
    CMDLERR         = 1,
    MULTARGERR      = 2,
    MULTFLAGERR     = 3,
    UNEXPCMDLERR    = 4,
    NOINPUTSERR     = 5,
    UNDEFCOMMANDERR = 6,
};

#include "cmd_common.h"
#include <cstdlib>

using error = std::pair<std::string, LightReturnCode>;

#define NOERR error(\
                    std::move(std::string("")),\
                    LightReturnCode::SUCCESS \
                )

#define LABORT(code, msg) {\
    print_in_one_color(RED, msg);\
    exit(code);\
}

#endif // ERRORS_H