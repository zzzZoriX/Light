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
    CANTOPENFILEERR = 7,
};

#include "cmd_common.h"
#include <cstdlib>

typedef struct err_msg {
    std::string function,
                full_line,
                err_desc;
    unsigned long line_n;

    err_msg(const std::string& f, const std::string& fl, const std::string& ed, const unsigned long ln) noexcept:
        function(f), full_line(fl), err_desc(ed), line_n(ln) {}
} error_msg_t;

using error = std::pair<error_msg_t, LightReturnCode>;

#define NOERR error(\
                    error_msg_t("", "", "", 0),\
                    LightReturnCode::SUCCESS \
                )

inline std::string convert_error_to_string(const error_msg_t& err) {
    std::string res =  "In function " + err.function + ":\n" + std::to_string(err.line_n) +
           "|  " + err.full_line + "\n" + err.err_desc;

    return res;
}

#define LABORT(code, msg) {\
    print_in_one_color(RED, msg);\
    exit(code);\
}

#endif // ERRORS_H