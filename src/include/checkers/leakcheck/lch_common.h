#ifndef LCHCOM_H
#define LCHCOM_H

#include <string>
#include <cctype>
#include "lch_data.h"


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

const std::vector<std::string> keywordsC17 = {
    "auto", "break", "case", "char", "const", "continue", "calloc", "default", "do", "double", "else",
    "enum", "extern", "float", "for", "free", "goto", "if", "inline", "int", "long", "malloc", "register",
    "typedef", "union", "unsigned", "void", "volatile", "while",
    "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary", "_Noreturn", "_Static_assert",
    "_Thread_local"
};


static bool is_object_name(const std::string& name) {
	if(!std::isalpha(name[0]) && name[0] != '_')
		return false;
	
	for(const auto& ch: name)
		if(!std::isalnum(ch) && ch != '_')
			return false;
	
	return true;
}

static bool is_not_func(const std::string& name, const std::vector<std::string>& fnames){
	if(!std::isalpha(name[0]) && name[0] != '_')
		return false;
	
	for(const auto& ch: name)
		if(!std::isalnum(ch) && ch != '_')
			return false;

	for(const auto& fname: fnames)
		if(name == fname)
			return false;
	
	return true;
}

static bool inscope(const obj_mdata_t& obj, const scope_mdata_t& scope){
	for(const auto& scope_obj: scope.alloc_objs_data)
		if(obj == scope_obj)
			return true;

	return false;
}

#endif // LCHCOM_H
