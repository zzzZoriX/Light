#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <fstream>
#include <list>

using token_t = std::list<std::string>;

token_t tokenize(std::ifstream fpt);

#endif //TOKENIZER_H
