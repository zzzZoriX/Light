#include "include/errors.h"

int main(int count, char** args) {
    if (count < 2) 
        LABORT(
        static_cast<int>(LightReturnCode::CMDLERR),
        "Too few arguments.\n"
        "Correct example use: light check myinput.c"
        );
    
    return 0;
}