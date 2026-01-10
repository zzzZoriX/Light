#include "include/errors.h"
#include "include/command_process.h"
#include "include/checkers/leakcheck/lch_main.h"

// v(a/b/_) - alpha/beta/release ; first num - global version id ; second num - patch version id
#define LIGHTAPIVERSION     "va-0.1"

int main(int count, char** args) {
    if (count < 2) 
        LABORT(
        static_cast<int>(LightReturnCode::CMDLERR),
        "Too few arguments.\n"
        "Correct example use: light check myinput.c"
        );

    arguments args_vec = convert_c_strs_to_cpp(args, count);
    ArgsInfo args_info = (ArgsInfo){
            .fs = NOFLAGS,
            .type = CallType::UNDEF
        };

    auto [msg, code] = process_arguments(&args_info, args_vec);

    if (code != LightReturnCode::SUCCESS)
        LABORT(
            static_cast<int>(code),
            msg
        );

    
    switch (args_info.type) {
        case CallType::VERSION: 
            std::cout << "Current Light API version: " << LIGHTAPIVERSION << std::endl;

            break;

        case CallType::HELP:
            std::cout << "Available commands:\n" <<
                        "  version              - show current version of Light API\n" <<
                        "  help                 - show help info(this message)\n" <<
                        "  check <input> ...    - check all files that are indicated by memory errors" <<
                        std::endl;

            break;

            case CallType::CHECK:
            leak_check(args_info);
            break;

        default:
            LABORT(
                static_cast<int>(LightReturnCode::UNDEFCOMMANDERR),
                std::string("Undefined Light API command!\nFor all available commands enter \"light help\"")
            );
    }

    return static_cast<int>(LightReturnCode::SUCCESS);
}