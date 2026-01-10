#ifndef LCH_DATA_H
#define LCH_DATA_H

#include <string>

typedef struct lch_var {
    std::string full_line,
                var_name;
    unsigned long line_number;
    bool freed;
} lch_var_data;

#endif //LCH_DATA_H
