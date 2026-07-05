/*
 * Copyright 2026 Khwarzma Company
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <string_view>
#include <vector>
#include <ostream>

namespace w9::lexer {

enum class TokenType {
    // Special Tokens
    END_OF_FILE,
    UNKNOWN,

    // Identifiers & Literals
    IDENTIFIER,
    NUMBER,
    STRING,

    // Keywords
    LET,
    CONST,
    FUNCTION,
    CLASS,
    RETURN,
    IF,
    ELSE,

    // Operators
    ASSIGN,       // =
    PLUS,         // +
    MINUS,        // -
    ASTERISK,     // *
    SLASH,        // /
    
    // Delimiters
    SEMICOLON,    // ;
    COMMA,        // ,
    LPAREN,       // (
    RPAREN,       // )
    LBRACE,       // {
    RBRACE,       // }
};

struct Token {
    TokenType type;
    std::string_view lexeme; // يشير إلى النص الأصلي مباشرة دون نسخ لضمان الأداء
    size_t line;
    size_t column;
};

class Lexer {
public:
    explicit Lexer(std::string_view source);

    // دالة أساسية لاستخراج الرمز التالي (On-demand) لتقليل استهلاك الذاكرة
    Token next_token();
    
    // دالة مساعدة لتحليل النص بالكامل دفعة واحدة (مفيدة للاختبارات)
    std::vector<Token> tokenize();

private:
    std::string_view source_;
    size_t position_ = 0;
    size_t read_position_ = 0;
    char ch_ = 0;
    
    size_t line_ = 1;
    size_t column_ = 0;

    void read_char();
    char peek_char() const;
    void skip_whitespace();
    
    Token make_token(TokenType type, std::string_view lexeme);
    Token read_identifier();
    Token read_number();
    Token read_string();
    
    TokenType lookup_keyword(std::string_view ident) const;
};

// مساعدة لطباعة الرموز أثناء التطوير والتنقيح
std::ostream& operator<<(std::ostream& os, TokenType type);

} // namespace w9::lexer
