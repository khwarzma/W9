// engine/lexer/lexer.cpp
#include "lexer.h"
#include <cctype>

namespace w9::lexer {

Lexer::Lexer(std::string_view source) : source_(source) {
    read_char();
}

void Lexer::read_char() {
    if (read_position_ >= source_.length()) {
        ch_ = 0;
    } else {
        ch_ = source_[read_position_];
    }
    position_ = read_position_;
    read_position_++;
    column_++;
}

char Lexer::peek_char() const {
    if (read_position_ >= source_.length()) {
        return 0;
    }
    return source_[read_position_];
}

void Lexer::skip_whitespace() {
    while (ch_ == ' ' || ch_ == '\t' || ch_ == '\n' || ch_ == '\r') {
        if (ch_ == '\n') {
            line_++;
            column_ = 0;
        }
        read_char();
    }
}

Token Lexer::make_token(TokenType type, std::string_view lexeme) {
    return Token{type, lexeme, line_, column_ - lexeme.length()};
}

TokenType Lexer::lookup_keyword(std::string_view ident) const {
    if (ident == "let") return TokenType::LET;
    if (ident == "const") return TokenType::CONST;
    if (ident == "function") return TokenType::FUNCTION;
    if (ident == "class") return TokenType::CLASS;
    if (ident == "return") return TokenType::RETURN;
    if (ident == "if") return TokenType::IF;
    if (ident == "else") return TokenType::ELSE;
    return TokenType::IDENTIFIER;
}

Token Lexer::read_identifier() {
    size_t start_pos = position_;
    while (std::isalnum(ch_) || ch_ == '_') {
        read_char();
    }
    std::string_view lexeme = source_.substr(start_pos, position_ - start_pos);
    return make_token(lookup_keyword(lexeme), lexeme);
}

Token Lexer::read_number() {
    size_t start_pos = position_;
    while (std::isdigit(ch_) || ch_ == '.') { // يدعم الأرقام العشرية البسيطة مبدئياً
        read_char();
    }
    std::string_view lexeme = source_.substr(start_pos, position_ - start_pos);
    return make_token(TokenType::NUMBER, lexeme);
}

Token Lexer::read_string() {
    char quote_type = ch_; // سواء ' أو "
    read_char(); // تخطي علامة الاقتباس الفتاحة
    size_t start_pos = position_;
    
    while (ch_ != quote_type && ch_ != 0) {
        if (ch_ == '\n') {
            line_++;
            column_ = 0;
        }
        read_char();
    }
    
    std::string_view lexeme = source_.substr(start_pos, position_ - start_pos);
    
    if (ch_ == quote_type) {
        read_char(); // تخطي علامة الاقتباس المغلقة
    }
    
    return make_token(TokenType::STRING, lexeme);
}

Token Lexer::next_token() {
    skip_whitespace();

    if (ch_ == 0) {
        return Token{
            TokenType::END_OF_FILE,
            "",
            line_,
            column_
        };
    }

    Token tok;

    std::string_view current_char_view =
        source_.substr(position_, 1);

    switch (ch_) {
        case '=':
            tok = make_token(TokenType::ASSIGN, current_char_view); break;
        case '+':
            tok = make_token(TokenType::PLUS, current_char_view); break;
        case '-':
            tok = make_token(TokenType::MINUS, current_char_view); break;
        case '*':
            tok = make_token(TokenType::ASTERISK, current_char_view); break;
        case '/':
            tok = make_token(TokenType::SLASH, current_char_view); break;
        case ';':
            tok = make_token(TokenType::SEMICOLON, current_char_view); break;
        case ',':
            tok = make_token(TokenType::COMMA, current_char_view); break;
        case '(':
            tok = make_token(TokenType::LPAREN, current_char_view); break;
        case ')':
            tok = make_token(TokenType::RPAREN, current_char_view); break;
        case '{':
            tok = make_token(TokenType::LBRACE, current_char_view); break;
        case '}':
            tok = make_token(TokenType::RBRACE, current_char_view); break;

        case '"':
        case '\'':
            return read_string();

        default:
            if (std::isalpha(ch_) || ch_ == '_') {
                return read_identifier();
            }
            else if (std::isdigit(ch_)) {
                return read_number();
            }
            else {
                tok = make_token(TokenType::UNKNOWN, current_char_view);
            }
            break;
    }

    read_char();
    return tok;
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    Token tok = next_token();
    while (tok.type != TokenType::END_OF_FILE) {
        tokens.push_back(tok);
        tok = next_token();
    }
    tokens.push_back(tok); // إضافة EOF
    return tokens;
}

} // namespace w9::lexer