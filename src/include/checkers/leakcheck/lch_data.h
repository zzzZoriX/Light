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
		    last_use_on;
	
	mi_t() noexcept:
		full_line(""), line_n(1), last_use_on(0) {}
} meta_info_t;


// main structures
typedef struct {
	std::string obj_name;
	obj_malloc_t alloc_type;
	bool freed;
	meta_info_t meta;
} obj_mdata_t;

typedef struct smd_t {
	std::string scope_name;
	std::vector<obj_mdata_t> alloc_objs_data;
	smd_t head_scope,
	      global_scope;
	
	smd_t() = default;


	smd_t(const std::string& name, smd_t&& head, smd_t&& global) noexcept:
		scope_name(name), head_scope(head), global_scope(global), alloc_objs_data() {}

	smd_t(const std::string&& name, smd_t&& head, smd_t&& global) noexcept:
		scope_name(name), head_scope(head), global_scope(global), alloc_objs_data() {}

	
	smd_t(smd_t&& head, smd_t&& global) noexcept:
		scope_name(""), head_scope(head), global_scope(global), alloc_objs_data() {}


	smd_t(const std::string& name, smd_t& head, smd_t& global) noexcept:
		scope_name(name), head_scope(head), global_scope(global), alloc_objs_data() {}

	smd_t(const std::string&& name, smd_t& head, smd_t& global) noexcept:
		scope_name(name), head_scope(head), global_scope(global), alloc_objs_data() {}

	
	smd_t(smd_t& head, smd_t& global) noexcept:
		scope_name(""), head_scope(head), global_scope(global), alloc_objs_data() {}
} scope_mdata_t;

#endif //LCH_DATA_H
