#ifndef CMDPROC_H
#define CMDPROC_H

struct FlagsState {
    bool    _cpp,
            _cpp_20_on,
            _Nleak,
            _Nsegs,
            _Naddr;
};

#define NOFLAGS (struct FlagsState){\
        ._cpp = false,\
        ._cpp_20_on = false,\
        ._Nleak = false,\
        ._Nsegs = false,\
        ._Naddr = false\
    }

enum class CallType : int{
    CHECK = 1,
    VERSION = 2,
    HELP = 3,
    UNDEF = -1,
};

#include <vector>
#include <string>
#include "errors.h"

using arguments = std::vector<std::string>;
using inputs = std::vector<std::string>;

typedef struct {
    struct FlagsState fs;
    inputs inputs_vec;
    CallType type;
} ArgsInfo;

#define VERSION_CMD     "version"
#define HELP_CMD        "help"
#define CHECK_CMD       "check"
#define NLEAK_FLAG      "-Nleak"
#define NADDR_FLAG      "-Naddr"
#define NSEGS_FLAG      "-Nsegs"
#define CPP_FLAG        "-cpp"
#define CPP20ON_FLAG    "-cpp20"

#define MULTICMDERR error( \
                        error_msg_t(\
                        "LIGHTAPI",\
                        "~~~",\
                        "Multiply command use",\
                        -1\
                        ), \
                        LightReturnCode::MULTARGERR \
                    )

#define MULTIFLAGERR error( \
                        error_msg_t(\
                        "LIGHTAPI",\
                        "~~~",\
                        "Multiply flag defention",\
                        -1\
                        ), \
                        LightReturnCode::MULTFLAGERR \
                    )

#define UNEXPINPUTS error( \
                        error_msg_t(\
                        "LIGHTAPI",\
                        "~~~",\
                        "Unexpected input file in command",\
                        -1\
                        ), \
                        LightReturnCode::UNEXPCMDLERR \
                    )

#define UNEXPFLAG   error( \
                        error_msg_t(\
                        "LIGHTAPI",\
                        "~~~",\
                        "Unexpected flag defention",\
                        -1\
                        ), \
                        LightReturnCode::UNEXPCMDLERR \
                    )

#define NOINPUTS    error( \
                        error_msg_t(\
                        "LIGHTAPI",\
                        "~~~",\
                        "Check command have not any input files",\
                        -1\
                        ), \
                        LightReturnCode::UNEXPCMDLERR \
                    )


/**
 * @brief will convert args from char** to std::vector<std::string>
 * 
 * @param cstrs 
 * @param count
 * @return std::vector<std::string> 
 */
arguments convert_c_strs_to_cpp(char** cstrs, const int count);

error process_arguments(ArgsInfo* ainf, arguments args_vec);

#endif // CMDPROC_H