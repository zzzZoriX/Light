#ifndef LCH_DATA_H
#define LCH_DATA_H

#include <string>
#include <vector>
#include "../tokenizer.h"

// helper structures
typedef enum {
	PTR_T,
	MDIM_PTR_T, // multidimention pointer like int**** and others
} obj_malloc_t;

/* 
	now will unuse because this struct is only need for a solution creating
*/
typedef struct mi_t {
	std::string full_line;
	std::size_t line_n,
		    last_use_on; // now unused but in the future it will be used in solution creating
	
	mi_t() noexcept:
		full_line(""), line_n(1), last_use_on(0) {}
} meta_info_t;


// main structures
typedef struct objd_t {
	std::string obj_name;
	obj_malloc_t alloc_type;
	bool freed;
	meta_info_t meta;

	objd_t(const std::string& name, const obj_malloc_t type, const bool&& freed, meta_info_t meta) noexcept:
		obj_name(name), alloc_type(type), freed(freed), meta(meta) {}

	bool operator==(const objd_t& other) const {
		return obj_name == other.obj_name;
	}
} obj_mdata_t;

typedef struct smd_t {
	std::string scope_name;
	std::vector<obj_mdata_t> alloc_objs_data;
	
	smd_t() = default;


	smd_t(const std::string& name) noexcept:
		scope_name(name) {}

	smd_t(const std::string&& name) noexcept:
		scope_name(name) {}
} scope_mdata_t;

#endif //LCH_DATA_H
