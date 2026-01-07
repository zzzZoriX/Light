#ifndef CMD_COMMON_H
#define CMD_COMMON_H

#include <string>
#include <vector>
#include <iostream>
#include <Windows.h>

#define RED     FOREGROUND_RED | FOREGROUND_INTENSITY
#define GREEN   FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define BLUE    FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define WHEEL   FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define PURPLE  FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY
#define YELLOW  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define WHITE   FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

#define SET_CMD_TEXT_COLOR(color)           \
    SetConsoleTextAttribute(                \
        GetStdHandle(STD_OUTPUT_HANDLE),    \
        color                               \
    );                                      

using strclr = std::pair<std::string, int>;

/**
 * @brief print string in one color
 * 
 * @param color
 * @param str 
 */
void print_in_one_color(const int color, std::string& str);
void print_in_one_color(const int color, std::string&& str);

/**
 * @brief print a strings with a color assigned to it's
 * 
 * @param strs 
 */
void print_in_many_colors(std::vector<strclr> strs);

#endif // CMD_COMMON_H