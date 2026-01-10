#include "tokenizer.h"

token_t tokenize(std::ifstream fpt) {
    token_t token;
    char c;
    std::string word,
                spec_chars = ",.:[]{}()-+/*^|&%=~!? \"';><";

    while (fpt.get(c)) {
        if (spec_chars.find(c) != std::string::npos) {
            token_t::append(&token, word);
            token_t::append(&token, c);

            word.clear();
        }
        else {
            word += c;
        }
    }

    return token;
}