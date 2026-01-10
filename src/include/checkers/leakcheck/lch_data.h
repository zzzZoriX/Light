#ifndef LCH_DATA_H
#define LCH_DATA_H

#include <string>
#include <vector>
#include "../tokenizer.h"

//  took from https://en.cppreference.com/w/cpp/keywords.html
const std::vector<std::string> keywordsCPP17 = {
    "alignof", "alignas", "and", "and_eq", "asm", "atomic_cancel",
    "atomic_commit", "atomic_noexcept", "auto", "bitand", "bitor",
    "bool", "break", "case", "catch", "char", "char16_t",
    "char32_t", "class", "compl", "const", "constexpr", "const_cast",
    "continue", "decltype", "default",
    "delete", "do", "double", "dynamic_cast", "else", "enum", "explicit",
    "export", "extern", "false", "float", "for", "friend", "final", "goto", "if",
    "inline", "int", "long", "mutable", "namespace", "new", "noexcept",
    "not", "not_eq", "nullptr", "override", "operator", "or", "or_eq", "private",
    "protected", "public", "register", "reinterpret_cast", "return", "short",
    "signed", "sizeof", "static", "static_assert", "static_cast", "struct",
    "switch", "template", "this", "thread_local", "throw", "true", "try",
    "typedef", "typeid", "typename", "union", "unsigned", "using",
    "virtual", "void", "volatile", "wchat_t", "while", "xor", "xor_eq"
//  macroses
    "#define", "#include", "#pragma", "#error", "#if", "#elif", "else", "endif",
    "#ifdef", "#ifndef", "#undef", "#line", "#defined", "__has_include"
};

const std::vector<std::string> keywordsCPP20 = {
//  c++17
    "alignof", "alignas", "and", "and_eq", "asm", "atomic_cancel",
    "atomic_commit", "atomic_noexcept", "auto", "bitand", "bitor",
    "bool", "break", "case", "catch", "char", "char16_t",
    "char32_t", "class", "compl", "const", "constexpr", "const_cast",
    "continue", "decltype", "default",
    "delete", "do", "double", "dynamic_cast", "else", "enum", "explicit",
    "export", "extern", "false", "float", "for", "friend", "final", "goto", "if",
    "inline", "int", "long", "mutable", "namespace", "new", "noexcept",
    "not", "not_eq", "nullptr", "override", "operator", "or", "or_eq", "private",
    "protected", "public", "register", "reinterpret_cast", "return", "short",
    "signed", "sizeof", "static", "static_assert", "static_cast", "struct",
    "switch", "template", "this", "thread_local", "throw", "true", "try",
    "typedef", "typeid", "typename", "union", "unsigned", "using",
    "virtual", "void", "volatile", "wchat_t", "while", "xor", "xor_eq"
//  macroses c++17
    "#define", "#include", "#pragma", "#error", "#if", "#elif", "else", "endif",
    "#ifdef", "#ifndef", "#undef", "#line", "#defined", "__has_include"
//  macroses c++20
    "#export", "#import", "#module", "__has_cpp_attribute"
//  c++20
    "char8_t", "concept", "consteval", "constinit", "co_await", "co_return", "co_yield",
    "requires"
};

typedef struct lch_var {
    std::string full_line,
                var_name;
    unsigned long line_number{};
    bool freed{};

    lch_var() = default;

    lch_var(const std::string& line, const unsigned long line_n, const bool cpp20on) noexcept:
        full_line(line), var_name(lch_var::cpp_get_var_name(line, cpp20on)), line_number(line_n) {}

    static std::string cpp_get_var_name(const std::string& line, const bool cpp20on) noexcept {
        const token_t words = tokenize(line);

        for (const auto& word : words) {
            bool is_kw = false;

            for (const auto& kw : (cpp20on ? keywordsCPP20 : keywordsCPP17))
                if (kw == word)
                    is_kw = true;

            if (!is_kw)
                return word;
        }

        return "";
    }
} lch_var_data;

#endif //LCH_DATA_H
