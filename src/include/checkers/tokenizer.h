#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <fstream>
#include <string>
#include <string_view>

typedef struct tok {
    tok* next;
    std::string value;
    bool have_value;

    tok() noexcept:
        next(nullptr), value(""), have_value(false) {}

    explicit tok(std::string_view value) noexcept:
        next(nullptr), value(value), have_value(true) {}

    static void append(tok* token, const std::string& value) noexcept {
        if (!token->have_value) {
            token->value = value;
            token->have_value = true;
        }
        else {
            const struct tok* head = token;
            while (!tok::is_last(head))
                head = head->next;

            *head->next = tok(value);
        }
    }

    static void append(tok* token, const char& c) noexcept {
        tok::append(token, {c, '\0'});
    }

    static bool is_last(const tok* token) noexcept {
        return token->next == nullptr;
    }
} token_t;

token_t tokenize(std::ifstream fpt);

#endif //TOKENIZER_H
