#include "include/errors.h"
#include "include/command_process.h"
#include <winerror.h>

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

    error process_result = process_arguments(&args_info, args_vec);

    if (process_result.second != LightReturnCode::SUCCESS)
        LABORT(
            static_cast<int>(process_result.second), 
            process_result.first
        );
    
    return static_cast<int>(LightReturnCode::SUCCESS);
}