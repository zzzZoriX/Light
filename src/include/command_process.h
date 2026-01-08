#ifndef CMDPROC_H
#define CMDPROC_H

struct FlagsState {
    bool    _cpp,
            _Nleak,
            _Nsegs,
            _Naddr;
};

#define NOFLAGS (struct FlagsState){\
        ._cpp = false,\
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

#define MULTICMDERR error<std::string>( \
                        std::move(std::string("Multiply command use")), \
                        LightReturnCode::MULTARGERR \
                    )

#define MULTIFLAGERR error<std::string>( \
                        std::move(std::string("Multiply flag defention")), \
                        LightReturnCode::MULTFLAGERR \
                    )

#define UNEXPINPUTS error<std::string>( \
                        std::move(std::string("Unexpected input file in command")), \
                        LightReturnCode::UNEXPCMDLERR \
                    )

#define UNEXPFLAG   error<std::string>( \
                        std::move(std::string("Unexpected flag defention")), \
                        LightReturnCode::UNEXPCMDLERR \
                    )

#define NOINPUTS    error<std::string>( \
                        std::move(std::string("Check command have not any input files")), \
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

error<std::string> process_arguments(ArgsInfo* ainf, arguments args_vec);

#endif // CMDPROC_H