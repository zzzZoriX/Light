#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <fstream>
#include <string>

typedef struct tok {
    struct tok* first,
              * last,
              * next;
    std::string value;

    tok() noexcept:
        first(this), last(this), next(this->last), value("") {}

    explicit tok(struct tok* first) noexcept:
        first(first), last(this), next(this->last), value("") {}

    void append(const std::string& value) noexcept {
        if (this == this->last)
            this->value = value;
        else {
            *this->last->next = tok(this->first);
            this->last = this->last->next;

            this->last->value = value;
        }
    }

    void append(const char c) noexcept {
        if (this == this->last)
            this->value = {c, '\0'};
        else {
            *this->last->next = tok(this->first);
            this->last = this->last->next;

            this->last->value = {c, '\0'};
        }
    }

    bool is_last() const noexcept {
        return this == this->last;
    }

    static void rotate(const struct tok* token) noexcept {
        token = token->next;
    }
} token_t;

token_t tokenize(std::ifstream fpt);

#endif //TOKENIZER_H
