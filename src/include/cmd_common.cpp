#include "cmd_common.h"

void print_in_one_color(const int color, std::string& str) {
    SET_CMD_TEXT_COLOR(color);
    std::cout << str << std::endl;
    SET_CMD_TEXT_COLOR(WHITE);
}

void print_in_one_color(const int color, std::string&& str) {
    SET_CMD_TEXT_COLOR(color);
    std::cout << str << std::endl;
    SET_CMD_TEXT_COLOR(WHITE);
}

void print_in_many_colors(std::vector<strclr> strs) {
    for (auto& str : strs) {
        SET_CMD_TEXT_COLOR(str.second);
        std::cout << str.first;
        SET_CMD_TEXT_COLOR(WHITE);
    }

    std::cout << std::endl;
}

void print_in_many_colors(std::vector<mstrclr> strs) {
    for (auto& str : strs) {
        SET_CMD_TEXT_COLOR(str.second);
        std::cout << str.first;
        SET_CMD_TEXT_COLOR(WHITE);
    }

    std::cout << std::endl;
}