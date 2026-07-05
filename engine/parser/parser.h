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

#include "../lexer/lexer.h"
#include "../ast/ast.h"
#include <memory>
#include <stdexcept>

namespace w9::parser {

// ترتيب أسبقية العمليات الحسابية
enum class Precedence {
    LOWEST,
    SUM,     // + or -
    PRODUCT, // * or /
    CALL,    // myFunction()
};

class Parser {
public:
    explicit Parser(lexer::Lexer lexer);

    std::unique_ptr<ast::Program> parse_program();

private:
    lexer::Lexer lexer_;
    lexer::Token current_token_;
    lexer::Token peek_token_;

    void next_token();
    bool current_token_is(lexer::TokenType type) const;
    bool peek_token_is(lexer::TokenType type) const;
    bool expect_peek(lexer::TokenType type);
    
    Precedence peek_precedence() const;
    Precedence current_precedence() const;

    // دالات تحليل العبارات (Statements)
    std::unique_ptr<ast::Statement> parse_statement();
    std::unique_ptr<ast::VariableDeclaration> parse_variable_declaration();
    
    std::unique_ptr<ast::FunctionDeclaration> parse_function_declaration();
    std::vector<std::string_view> parse_function_parameters();
    std::vector<std::unique_ptr<ast::Statement>> parse_block_statement();
    std::unique_ptr<ast::Expression> parse_call_expression(std::unique_ptr<ast::Expression> callee);
    std::vector<std::unique_ptr<ast::Expression>> parse_call_arguments();
    
    // دالات تحليل التعبيرات (Expressions) باستخدام Pratt Parsing
    std::unique_ptr<ast::Expression> parse_expression(Precedence precedence);
    std::unique_ptr<ast::Expression> parse_identifier();
    std::unique_ptr<ast::Expression> parse_number();
    std::unique_ptr<ast::Expression> parse_infix_expression(std::unique_ptr<ast::Expression> left);
};

} // namespace w9::parser
