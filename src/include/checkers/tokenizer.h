#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <fstream>
#include <vector>
#include <string>

using token_t = std::vector<std::string>;

token_t tokenize(std::ifstream fpt);
token_t tokenize(const std::string&);

#endif //TOKENIZER_H
