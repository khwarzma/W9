#include "parser.h"

namespace w9::parser {

Parser::Parser(lexer::Lexer lexer) : lexer_(lexer) {
    // قراءة أول رمزين لتهيئة current_token و peek_token
    next_token();
    next_token();
}

void Parser::next_token() {
    current_token_ = peek_token_;
    peek_token_ = lexer_.next_token();
}

bool Parser::current_token_is(lexer::TokenType type) const {
    return current_token_.type == type;
}

bool Parser::peek_token_is(lexer::TokenType type) const {
    return peek_token_.type == type;
}

bool Parser::expect_peek(lexer::TokenType type) {
    if (peek_token_is(type)) {
        next_token();
        return true;
    }
    return false; // في التطوير المتقدم سنقوم برمي خطأ Syntax Error هنا
}

Precedence Parser::peek_precedence() const {
    switch (peek_token_.type) {
        case lexer::TokenType::PLUS:
        case lexer::TokenType::MINUS:
            return Precedence::SUM;
        case lexer::TokenType::ASTERISK:
        case lexer::TokenType::SLASH:
            return Precedence::PRODUCT;
        case lexer::TokenType::LPAREN:
            return Precedence::CALL;
        default:
            return Precedence::LOWEST;
    }
}

Precedence Parser::current_precedence() const {
    switch (current_token_.type) {
        case lexer::TokenType::PLUS:
        case lexer::TokenType::MINUS:
            return Precedence::SUM;
        case lexer::TokenType::ASTERISK:
        case lexer::TokenType::SLASH:
            return Precedence::PRODUCT;
        case lexer::TokenType::LPAREN:
            return Precedence::CALL;
        default:
            return Precedence::LOWEST;
    }
}

std::unique_ptr<ast::Program> Parser::parse_program() {
    auto program = std::make_unique<ast::Program>();

    while (current_token_.type != lexer::TokenType::END_OF_FILE) {
        auto stmt = parse_statement();
        if (stmt) {
            program->statements.push_back(std::move(stmt));
        }
        next_token();
    }

    return program;
}

std::unique_ptr<ast::Statement> Parser::parse_statement() {
    switch (current_token_.type) {
        case lexer::TokenType::LET:
        case lexer::TokenType::CONST:
            return parse_variable_declaration();
        case lexer::TokenType::FUNCTION:
            return parse_function_declaration();
        default:
            return nullptr; 
    }
}

std::unique_ptr<ast::VariableDeclaration> Parser::parse_variable_declaration() {
    auto stmt = std::make_unique<ast::VariableDeclaration>();
    stmt->is_const = current_token_is(lexer::TokenType::CONST);

    if (!expect_peek(lexer::TokenType::IDENTIFIER)) {
        return nullptr;
    }

    stmt->identifier = current_token_.lexeme;

    if (!expect_peek(lexer::TokenType::ASSIGN)) {
        return nullptr;
    }

    next_token(); // تخطي الـ '='

    stmt->initializer = parse_expression(Precedence::LOWEST);

    if (peek_token_is(lexer::TokenType::SEMICOLON)) {
        next_token();
    }

    return stmt;
}

std::unique_ptr<ast::Expression> Parser::parse_expression(Precedence precedence) {
    std::unique_ptr<ast::Expression> left_exp;

    // Parsing Prefix
    switch (current_token_.type) {
        case lexer::TokenType::IDENTIFIER:
            left_exp = parse_identifier();
            break;
        case lexer::TokenType::NUMBER:
            left_exp = parse_number();
            break;
        default:
            return nullptr;
    }

    // Parsing Infix (العمليات الثنائية بناءً على الأسبقية)
    while (!peek_token_is(lexer::TokenType::SEMICOLON) && precedence < peek_precedence()) {
        if (peek_token_.type != lexer::TokenType::PLUS && 
            peek_token_.type != lexer::TokenType::MINUS &&
            peek_token_.type != lexer::TokenType::ASTERISK && 
            peek_token_.type != lexer::TokenType::SLASH &&
            peek_token_.type != lexer::TokenType::LPAREN) {
            return left_exp;
        }

        next_token();
        if (current_token_is(lexer::TokenType::LPAREN)) {
            left_exp = parse_call_expression(std::move(left_exp));
        } else {
            left_exp = parse_infix_expression(std::move(left_exp));
        }
    }
    return left_exp;
}

std::unique_ptr<ast::Expression> Parser::parse_identifier() {
    auto lit = std::make_unique<ast::IdentifierLiteral>();
    lit->value = current_token_.lexeme;
    return lit;
}

std::unique_ptr<ast::Expression> Parser::parse_number() {
    auto lit = std::make_unique<ast::NumericLiteral>();
    lit->value = current_token_.lexeme;
    return lit;
}

std::unique_ptr<ast::Expression> Parser::parse_infix_expression(std::unique_ptr<ast::Expression> left) {
    auto exp = std::make_unique<ast::BinaryExpression>();
    exp->op = current_token_.lexeme;
    exp->left = std::move(left);

    Precedence precedence = current_precedence();
    next_token();
    exp->right = parse_expression(precedence);

    return exp;
}
std::unique_ptr<ast::FunctionDeclaration> Parser::parse_function_declaration() {
    auto stmt = std::make_unique<ast::FunctionDeclaration>();
    
    if (!expect_peek(lexer::TokenType::IDENTIFIER)) return nullptr;
    stmt->name = current_token_.lexeme;

    if (!expect_peek(lexer::TokenType::LPAREN)) return nullptr;
    stmt->parameters = parse_function_parameters();

    if (!expect_peek(lexer::TokenType::LBRACE)) return nullptr;
    stmt->body = parse_block_statement();

    return stmt;
}

std::vector<std::string_view> Parser::parse_function_parameters() {
    std::vector<std::string_view> params;
    if (peek_token_is(lexer::TokenType::RPAREN)) {
        next_token();
        return params;
    }
    next_token(); // الانتقال لأول باراميتر
    params.push_back(current_token_.lexeme);

    while (peek_token_is(lexer::TokenType::COMMA)) {
        next_token(); // تخطي الكوما
        next_token(); // الانتقال للباراميتر التالي
        params.push_back(current_token_.lexeme);
    }
    expect_peek(lexer::TokenType::RPAREN);
    return params;
}

std::vector<std::unique_ptr<ast::Statement>> Parser::parse_block_statement() {
    std::vector<std::unique_ptr<ast::Statement>> body;
    next_token(); // تخطي الـ '{'

    while (!current_token_is(lexer::TokenType::RBRACE) && !current_token_is(lexer::TokenType::END_OF_FILE)) {
        // دعم قراءة العبارات الشرطية أو تعريف المتغيرات let/const داخل الدالة
        if (current_token_is(lexer::TokenType::LET) || current_token_is(lexer::TokenType::CONST)) {
            auto var = parse_variable_declaration();
            if (var) body.push_back(std::move(var));
        }
        next_token();
    }
    return body;
}

std::unique_ptr<ast::Expression> Parser::parse_call_expression(std::unique_ptr<ast::Expression> callee) {
    auto expr = std::make_unique<ast::CallExpression>();
    expr->callee = std::move(callee);
    expr->arguments = parse_call_arguments();
    return expr;
}

std::vector<std::unique_ptr<ast::Expression>> Parser::parse_call_arguments() {
    std::vector<std::unique_ptr<ast::Expression>> args;
    if (peek_token_is(lexer::TokenType::RPAREN)) {
        next_token();
        return args;
    }
    next_token();
    args.push_back(parse_expression(Precedence::LOWEST));

    while (peek_token_is(lexer::TokenType::COMMA)) {
        next_token();
        next_token();
        args.push_back(parse_expression(Precedence::LOWEST));
    }
    expect_peek(lexer::TokenType::RPAREN);
    return args;
}

} // namespace w9::parser