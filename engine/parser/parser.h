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
    
    // دالات تحليل التعبيرات (Expressions) باستخدام Pratt Parsing
    std::unique_ptr<ast::Expression> parse_expression(Precedence precedence);
    std::unique_ptr<ast::Expression> parse_identifier();
    std::unique_ptr<ast::Expression> parse_number();
    std::unique_ptr<ast::Expression> parse_infix_expression(std::unique_ptr<ast::Expression> left);
};

} // namespace w9::parser