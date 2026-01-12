#include "tokenizer.h"

token_t tokenize(std::ifstream fpt) {
    token_t token;
    char c;
    std::string word,
                spec_chars = ",.:[]{}()-+/*^|&%=~!? \"';><\n";

    while (fpt.get(c)) {
        if (spec_chars.find(c) != std::string::npos) {
            if (!word.empty()) {
                token.push_back(word);
                word.clear();
            }

            token.push_back({c});
        }
        else {
            word += c;
        }
    }

    if (!word.empty()) {
        token.push_back(word);
    }

    return token;
}

token_t tokenize(const std::string& line) {
    token_t token;
    std::string word,
                spec_chars = ",.:[]{}()-+/*^|&%=~!? \"';><\n";

    for (const char c : line) {
        if (spec_chars.find(c) != std::string::npos) {
            if (!word.empty()) {
                token.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }

    if (!word.empty()) {
        token.push_back(word);
    }

    return token;
}
