#include "lch_main.h"

//	scopes[0] - is always global scope
checker_result_t leak_check_file(const std::string& fname, token_t& tok_stream, const FlagsState& fs) {
        checker_result_t leak_check_result(Checker::LEAK_CHECKER);
	std::vector<scope_mdata_t> scopes{
        	scope_mdata_t(fname)
	};
	std::vector<std::string> function_names;
	auto end = tok_stream.end();
	
	for(auto it = tok_stream.begin(); it != end; ++it){
		if(is_object_name(*it)){
			const std::string name{*it};

			if(*(++it) == "("){
				function_names.push_back(name);

				while(*(++it) != "{" && *it != ";");

				if(*it == "{")
					scopes.push_back(leak_check_scope(
						it, 
						end,
						scopes[0], 
						scopes[0], 
						name, 
						function_names,
						fs
					));
			}
		}
	}
}

scope_mdata_t leak_check_scope(
	token_t::iterator& beg,
	token_t::iterator& end,
	scope_mdata_t& head,
	scope_mdata_t& global,
	const std::string& scope_name,
	const std::vector<std::string> fnames ,
	const FlagsState& fs
) {
	meta_info_t metaI;
	scope_mdata_t scope_data(scope_name);
	std::string current_line_obj_name;

	for(auto it = beg, it != end; ++it){
		if(*it == "\n"){
			metaI.full_line.clear();
			++metaI.line_n;
			
			continue;
		}

		if(fs._cpp){
			if(CPP_IS_MEM_ALLOC_WORD(*it)){
				obj_malloc_t type = PTR_T;

				while(*(++it) != ";"){
					metaI.full_line.push_back(*it);
					if(*it == "[") type = MDIM_PTR_T;
				}

				scope_data.alloc_objs_data.push_back(
					obj_mdata_t(current_line_obj_name, type, false, metaI)
				);
			}
			else if(CPP_IS_MEM_DEALLOC_WORD(*it)){
				obj_malloc_t type = PTR_T;

				while(*(++it) != ";"){
					metaI.full_line.push_back(*it);
					if(*it == "[") type = MDIM_PTR_T;
				}

				scope_data.alloc_objs_data.push_back(
					obj_mdata_t(current_line_obj_name, type, true, metaI)
				);
			}
		}
		else{
//		C-kw handler...
		}

		if(*it == "{"){
			scope_mdata_t inner_scope_data = leak_check_scope(++it, end, scope_data, global, scope_name, fnames, fs);
			std::size_t inner_scope_objs_count = inner_scope_data.alloc_objs_data.size();

			for(std::size_t i = 0; i < = inner_scope_objs_count; ++i){
				auto obj = inner_scope_data.alloc_objs_data[i];
				
				if(obj.freed){
//			now i using a very slow algorithm and in the future i'll replace it with more effectivency algorithm
					std::size_t obj_index_in_other_scopes;

					if(
						obj_index_in_other_scopes = inscope(obj, scope_data); 
						obj_index_in_other_scopes != inner_scope_objs_count
					) {
						scope_data.alloc_objs_data.erase(
							scope_data.alloc_objs_data.begin() + obj_index_in_other_scopes
						);
						
						inner_scope_data.alloc_objs_data.erase(
							inner_scope_data.alloc_objs_data.begin() + i
						);
					}
					else if(
						obj_index_in_other_scopes = inscope(obj, global); 
						obj_index_in_other_scopes != inner_scope_objs_count
					) {
						global.alloc_objs_data.erase(
							global.alloc_objs_data.begin() + obj_index_in_other_scopes
						);

						inner_scope_data.alloc_objs_data.erase(
							inner_scope_data.alloc_objs_data.begin() + i
						);
					}
				}
			}
		}
	}
}
