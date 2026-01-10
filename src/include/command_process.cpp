#include "command_process.h"

arguments convert_c_strs_to_cpp(char** cstrs, const int count) {
    arguments res;

//  starts from 1 because the first arg is path of light.exe
    for (int i = 1; i < count; ++i) 
        res.push_back(std::string(cstrs[i]));

    return res;
}

error process_arguments(ArgsInfo* ainf, arguments args_vec) {
    for (auto& arg : args_vec) {
        if (arg == VERSION_CMD) {
            if (ainf->type != CallType::UNDEF)
                return MULTICMDERR;

            ainf->type = CallType::VERSION;
            break;
        }

        if (arg == HELP_CMD) {
            if (ainf->type != CallType::UNDEF)
                return MULTICMDERR;

            ainf->type = CallType::HELP;
            break;
        }

        if (arg == CHECK_CMD) {
            if (ainf->type != CallType::UNDEF) 
                return MULTICMDERR;

            ainf->type = CallType::CHECK;
        }

        else if (arg == NLEAK_FLAG) {
            if (ainf->type != CallType::CHECK)
                return UNEXPFLAG;

            if (ainf->fs._Nleak) 
                return MULTIFLAGERR;

            ainf->fs._Nleak = true;
        }

        else if (arg == NSEGS_FLAG) {
            if (ainf->type != CallType::CHECK)
                return UNEXPFLAG;

            if (ainf->fs._Nsegs)
                return MULTIFLAGERR;

            ainf->fs._Nsegs = true;
        }

        else if (arg == NADDR_FLAG) {
            if (ainf->type != CallType::CHECK)
                return UNEXPFLAG;

            if (ainf->fs._Naddr) 
                return MULTIFLAGERR;

            ainf->fs._Naddr = true;
        }

        else if (arg == CPP_FLAG) {
            if (ainf->type != CallType::CHECK)
                return UNEXPFLAG;

            if (ainf->fs._cpp)
                return MULTIFLAGERR;

            ainf->fs._cpp = true;
        }

        else if (arg == CPP20ON_FLAG) {
            if (ainf->type != CallType::CHECK)
                return UNEXPFLAG;

            if (ainf->fs._cpp_20_on)
                return MULTIFLAGERR;

            ainf->fs._cpp_20_on = true;
        }

        else {
            if (ainf->type != CallType::CHECK)
                return UNEXPINPUTS;

            ainf->inputs_vec.push_back(arg);
        }
    }

    if (ainf->type == CallType::CHECK && ainf->inputs_vec.empty()) 
        return NOINPUTS;

    return NOERR;
}